#include "../headers/unixclientstream.hpp"
#include "../headers/exception.hpp"
#include <string>
#include <iostream>
#include <string.h>
#include <unistd.h>

#include <iomanip> 
#include <json/json.h>


#include "kalay_dserver.h"
#include "dserver.h"
#include "device_parser.h"
#include "device_api.h"

using namespace std;


pthread_mutex_t mutex_rdt_cnnt_array;

struct stRDTcnnt __rdt_cnnt[MAX_RDT_CONNECTION];
int __cnt_rdt_cnnt = 0;


int rdtcnnt_init()
{
	int i;
	__cnt_rdt_cnnt = 0;

	pthread_mutex_init(&mutex_rdt_cnnt_array, NULL);

	pthread_mutex_lock(&mutex_rdt_cnnt_array);

	for(i=0;i<MAX_RDT_CONNECTION;i++)
		memset(&__rdt_cnnt[i],0,sizeof(struct stRDTcnnt));

	pthread_mutex_unlock(&mutex_rdt_cnnt_array);

	return 0;
}

int rdtcnnt_destroy()
{
	int i;
		
	pthread_mutex_lock(&mutex_rdt_cnnt_array);

	for(i=0;i<MAX_RDT_CONNECTION;i++)
	{
		if ( __rdt_cnnt[i].action  > 0 )
		{
			if ( __rdt_cnnt[i].rdt_id >= 0 )
			{
				RDT_Destroy(__rdt_cnnt[i].rdt_id);
				__rdt_cnnt[i].rdt_id = -1;
			}


			if ( __rdt_cnnt[i].iotc_sid >= 0 )
			{
				IOTC_Session_Close( __rdt_cnnt[i].iotc_sid);		
				__rdt_cnnt[i].iotc_sid = -1;		
			}
		}

		memset(&__rdt_cnnt[i],0,sizeof(struct stRDTcnnt));

	}

	pthread_mutex_unlock(&mutex_rdt_cnnt_array);

	pthread_mutex_destroy(&mutex_rdt_cnnt_array);


	return 0;	
}


int rdtcnnt_new_iotc_conntected(int iotc_sid)
{
	int i;
	int ret = -1;

	pthread_mutex_lock(&mutex_rdt_cnnt_array);

	for(i=0;i<MAX_RDT_CONNECTION;i++)
	{
		if ( __rdt_cnnt[i].action == 0 )
		{
			__rdt_cnnt[i].action = RDTCNNT_IOTC_CONNECTED;
			__rdt_cnnt[i].iotc_sid = iotc_sid;
			__rdt_cnnt[i].rdt_id = -1;

			__cnt_rdt_cnnt++;
			ret = i;
			break;
		}
	}

	pthread_mutex_unlock(&mutex_rdt_cnnt_array);	

	
	return ret;
}

int rdtcnnt_check_packet(int session)
{
	unsigned char szBuff[1024*16];
	int rc;
	

	switch(__rdt_cnnt[session].rdtread_state)
	{
		case RDTREAD_PACKET_H:
			rc = RDT_Read(__rdt_cnnt[session].rdt_id, (char*)szBuff, 1, 0);			
			if ( rc == 1 )
			{
				if ( szBuff[0] == 0xfe )
					__rdt_cnnt[session].rdtread_state = RDTREAD_PACKET_L;
			};
			break;

		case  RDTREAD_PACKET_L:
			rc = RDT_Read(__rdt_cnnt[session].rdt_id, (char*)szBuff, 1, 0);			
			if ( rc == 1 )
			{
				if ( szBuff[0] == 0xef )
					__rdt_cnnt[session].rdtread_state = RDTREAD_OPTION_LENGTH_H;
				else
					__rdt_cnnt[session].rdtread_state = RDTREAD_PACKET_H;
			}
			break;

		case  RDTREAD_OPTION_LENGTH_H:
			rc = RDT_Read(__rdt_cnnt[session].rdt_id, (char*)szBuff, 1, 0);			
			if ( rc == 1 )
			{
				__rdt_cnnt[session].rdtread_option_length = ((unsigned int)szBuff[0]) << 8;
				__rdt_cnnt[session].rdtread_state = RDTREAD_OPTION_LENGTH_L;
			}
			break;

		case  RDTREAD_OPTION_LENGTH_L:
			rc = RDT_Read(__rdt_cnnt[session].rdt_id, (char*)szBuff, 1, 0);			
			if ( rc == 1 )
			{
						
				__rdt_cnnt[session].rdtread_option_length |= ((unsigned int)szBuff[0]);


				__rdt_cnnt[session].retread_option_readpos = 0;

				if ( __rdt_cnnt[session].rdtread_option_length  > 0  )
				{
					__rdt_cnnt[session].rdt_recv_option = (unsigned char*)malloc(__rdt_cnnt[session].rdtread_option_length);

					__rdt_cnnt[session].rdtread_state = RDTREAD_OPTION;
				}
				else
				{
					__rdt_cnnt[session].rdtread_state = RDTREAD_DATA_LENGTH_H;	
				}
			}
			break;

		case RDTREAD_OPTION:

			if ( __rdt_cnnt[session].rdt_recv_option != NULL )
			{
				rc = RDT_Read(__rdt_cnnt[session].rdt_id
								,(char*) &__rdt_cnnt[session].rdt_recv_option[__rdt_cnnt[session].retread_option_readpos]
								,__rdt_cnnt[session].rdtread_option_length-__rdt_cnnt[session].retread_option_readpos
								, 0);
			}
			else
			{
				unsigned int read_length;
				read_length = __rdt_cnnt[session].rdtread_option_length-__rdt_cnnt[session].retread_option_readpos;

				if ( read_length > sizeof(szBuff) )
					read_length = sizeof(szBuff);

				rc = RDT_Read(__rdt_cnnt[session].rdt_id
								,(char*) szBuff
								,read_length
								, 0);
			}

			if ( rc > 0  )
			{
				__rdt_cnnt[session].retread_option_readpos += rc;

				if (  __rdt_cnnt[session].retread_option_readpos == __rdt_cnnt[session].rdtread_option_length )
					__rdt_cnnt[session].rdtread_state = RDTREAD_DATA_LENGTH_H;
			}
			break;


		case  RDTREAD_DATA_LENGTH_H:
			rc = RDT_Read(__rdt_cnnt[session].rdt_id, (char*)szBuff, 1, 0);			
			if ( rc == 1 )
			{
				__rdt_cnnt[session].rdtread_data_length = ((unsigned int)szBuff[0]) << 8;
				__rdt_cnnt[session].rdtread_state = RDTREAD_DATA_LENGTH_L;
			}
			break;

		case  RDTREAD_DATA_LENGTH_L:
			rc = RDT_Read(__rdt_cnnt[session].rdt_id, (char*) szBuff, 1, 0);			
			if ( rc == 1 )
			{
				__rdt_cnnt[session].rdtread_data_length |= ((unsigned int)szBuff[0]);

				__rdt_cnnt[session].rdtread_state = RDTREAD_DATA;

				__rdt_cnnt[session].retread_data_readpos = 0;

				__rdt_cnnt[session].rdt_recv_data = (unsigned char*)malloc(__rdt_cnnt[session].rdtread_data_length+1); // for string terminal charactor
			}
			break;			


		case RDTREAD_DATA:
			if ( __rdt_cnnt[session].rdt_recv_data != NULL )
			{
				rc = RDT_Read(__rdt_cnnt[session].rdt_id
								,(char*) &__rdt_cnnt[session].rdt_recv_data[__rdt_cnnt[session].retread_data_readpos]
								,__rdt_cnnt[session].rdtread_data_length-__rdt_cnnt[session].retread_data_readpos
								, 0);
			}
			else
			{
				unsigned int read_length;
				read_length = __rdt_cnnt[session].rdtread_data_length-__rdt_cnnt[session].retread_data_readpos;
				if ( read_length > sizeof(szBuff) )
					read_length = sizeof(szBuff);

				rc = RDT_Read(__rdt_cnnt[session].rdt_id
									,(char*) szBuff
									,read_length
									, 0);
			}

			if ( rc > 0  )
			{
				__rdt_cnnt[session].retread_data_readpos += rc;

				if (  __rdt_cnnt[session].retread_data_readpos == __rdt_cnnt[session].rdtread_data_length )
				{
					__rdt_cnnt[session].rdt_recv_data[__rdt_cnnt[session].rdtread_data_length] = 0;


printf("eddy test \n option:%s \n data:%s \n",__rdt_cnnt[session].rdt_recv_option,__rdt_cnnt[session].rdt_recv_data);							

					
					device_parser(session,__rdt_cnnt[session].rdt_recv_option,__rdt_cnnt[session].rdt_recv_data);

					if ( __rdt_cnnt[session].rdt_recv_option != NULL )
					{
						free(__rdt_cnnt[session].rdt_recv_option);
						__rdt_cnnt[session].rdt_recv_option = NULL;
					}
					if ( __rdt_cnnt[session].rdt_recv_data != NULL )
					{
						free(__rdt_cnnt[session].rdt_recv_data);
						__rdt_cnnt[session].rdt_recv_data = NULL;
					}

					__rdt_cnnt[session].rdtread_state = RDTREAD_PACKET_H;
				}
					
			}
			break;		

	}



	return 0;
}

int rdtcnnt_check_status()
{
	int i;
	
	pthread_mutex_lock(&mutex_rdt_cnnt_array);

	for(i=0;i<MAX_RDT_CONNECTION;i++)
	{
		if ( __rdt_cnnt[i].action == RDTCNNT_IOTC_CONNECTED )
		{
			int rdt_id;

			__rdt_cnnt[i].action = RDTCNNT_RDT_CONNECTING;
			
			rdt_id = RDT_Create(__rdt_cnnt[i].iotc_sid, RDT_WAIT_TIMEMS, 0);
			if ( rdt_id < 0 )
			{
				printf("RDT create fail:%d \n",rdt_id);

				IOTC_Session_Close(__rdt_cnnt[i].iotc_sid);

				memset(&__rdt_cnnt[i],0,sizeof(struct stRDTcnnt)); // Clean session info
				__cnt_rdt_cnnt--;
			}
			else
			{
				printf("RDT create OK:%d \n",rdt_id);

				__rdt_cnnt[i].action = RDTCNNT_RDT_CONNECTED;
				__rdt_cnnt[i].rdt_id = rdt_id;
				__rdt_cnnt[i].tx_counter = 0;
			}
		}




		if ( __rdt_cnnt[i].action >= RDTCNNT_IOTC_CONNECTED )
		{
			__rdt_cnnt[i].cnnt_state = IOTC_Session_Check(__rdt_cnnt[i].iotc_sid, &__rdt_cnnt[i].Sinfo);
			if ( __rdt_cnnt[i].cnnt_state < 0 )
			{
				printf("RDT Cnnt err:%d \n",__rdt_cnnt[i].cnnt_state);
				if ( 	__rdt_cnnt[i].cnnt_state == IOTC_ER_REMOTE_TIMEOUT_DISCONNECT 
					|| __rdt_cnnt[i].cnnt_state == IOTC_ER_SESSION_CLOSE_BY_REMOTE  	)
				{
				}

				if ( __rdt_cnnt[i].rdt_id >= 0  )
				{
					RDT_Destroy(__rdt_cnnt[i].rdt_id);
					__rdt_cnnt[i].rdt_id = -1;
				}


				IOTC_Session_Close(__rdt_cnnt[i].iotc_sid);

				memset(&__rdt_cnnt[i],0,sizeof(struct stRDTcnnt)); // Clean session info					
				__cnt_rdt_cnnt--;

				printf("free session %d \n",i);
			}
		}

		if ( __rdt_cnnt[i].action == RDTCNNT_RDT_CONNECTED	)
		{
			rdtcnnt_check_packet(i);
		}		
	}
		

	pthread_mutex_unlock(&mutex_rdt_cnnt_array);


	return 0;
}
