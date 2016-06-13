#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "IOTCAPIs.h"
#include "RDTAPIs.h"

#include "rdtcnnt.h"



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
	{
		memset(&__rdt_cnnt[i],0,sizeof(struct stRDTcnnt));
		
	}


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

			pthread_mutex_destroy(&__rdt_cnnt[i].mutex_datalink);
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

			pthread_mutex_init(&__rdt_cnnt[i].mutex_datalink, NULL);

			__cnt_rdt_cnnt++;
			ret = i;
			break;
		}
	}

	pthread_mutex_unlock(&mutex_rdt_cnnt_array);	

	
	return ret;
}

int rdtcnnt_reset_packet(int session)
{
	if ( __rdt_cnnt[session].rdtread_option != NULL )
	{
		free(__rdt_cnnt[session].rdtread_option);
		__rdt_cnnt[session].rdtread_option = NULL;
	}
	if ( __rdt_cnnt[session].rdtread_data != NULL )
	{
		free(__rdt_cnnt[session].rdtread_data);
		__rdt_cnnt[session].rdtread_data = NULL;
	}

	__rdt_cnnt[session].rdtread_state = RDTREAD_PACKET_H;

	return 0;
}

int rdtcnnt_check_packet(int session)
{
	unsigned char szBuff[1024*16];
	int rc;
	int ret = 0;;
	

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
					__rdt_cnnt[session].rdtread_state = RDTREAD_PACKET_H; // reset read state
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
					__rdt_cnnt[session].rdtread_option = (unsigned char*)malloc(__rdt_cnnt[session].rdtread_option_length);

					__rdt_cnnt[session].rdtread_state = RDTREAD_OPTION;
				}
				else
				{
					__rdt_cnnt[session].rdtread_state = RDTREAD_DATA_LENGTH_H;	
				}
			}
			break;

		case RDTREAD_OPTION:

			if ( __rdt_cnnt[session].rdtread_option != NULL )
			{
				rc = RDT_Read(__rdt_cnnt[session].rdt_id
								,(char*) &__rdt_cnnt[session].rdtread_option[__rdt_cnnt[session].retread_option_readpos]
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

				__rdt_cnnt[session].rdtread_data = (unsigned char*)malloc(__rdt_cnnt[session].rdtread_data_length+1); // for string terminal charactor
			}
			break;			


		case RDTREAD_DATA:
			if ( __rdt_cnnt[session].rdtread_data != NULL )
			{
				rc = RDT_Read(__rdt_cnnt[session].rdt_id
								,(char*) &__rdt_cnnt[session].rdtread_data[__rdt_cnnt[session].retread_data_readpos]
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
					__rdt_cnnt[session].rdtread_data[__rdt_cnnt[session].rdtread_data_length] = 0;


					__rdt_cnnt[session].rdtread_state = RDTREAD_DATA_READY;
					ret = 1;
				}
					
			}
			break;		

	}

	return ret;
}



int rdtcnnt_get_session_by_uid(char* UID)
{
	int i;
	int ret = -1;

	pthread_mutex_lock(&mutex_rdt_cnnt_array);

	for(i=0;i<MAX_RDT_CONNECTION;i++)
	{
		if ( memcpy(__rdt_cnnt[i].target_uid,UID,20) == 0 )
		{
			ret = i;
			break;
		}
	}

	pthread_mutex_unlock(&mutex_rdt_cnnt_array);	

	return ret;	
}


int rdtcnnt_new_iotc_request(char *UID)
{
	int i;
	int ret = -1;


	pthread_mutex_lock(&mutex_rdt_cnnt_array);

	for(i=0;i<MAX_RDT_CONNECTION;i++)
	{
		if ( __rdt_cnnt[i].action == 0 )
		{
			memcpy(__rdt_cnnt[i].target_uid,UID,20);
			__rdt_cnnt[i].action = RDTCNNT_NEW;
			__rdt_cnnt[i].cnnt_state = 0;
			__rdt_cnnt[i].iotc_sid = -1;
			__rdt_cnnt[i].rdt_id = -1;

			pthread_mutex_init(&__rdt_cnnt[i].mutex_datalink, NULL);

			ret = i;
			break;
		}
	}

	pthread_mutex_unlock(&mutex_rdt_cnnt_array);	

	return ret;
}


int rdtcnnt_check_new_iotc_request()
{
	int i;
	int ret;
	
	pthread_mutex_lock(&mutex_rdt_cnnt_array);
	for(i=0;i<MAX_RDT_CONNECTION;i++)
	{
		if ( __rdt_cnnt[i].action == RDTCNNT_NEW	)
		{
			__rdt_cnnt[i].action = RDTCNNT_IOTC_CONNECTING;

			__rdt_cnnt[i].iotc_sid = IOTC_Get_SessionID();
			if(__rdt_cnnt[i].iotc_sid == IOTC_ER_NOT_INITIALIZED)
			{
				printf("Not Initialize!!!\n");
			}
			else if (__rdt_cnnt[i].iotc_sid == IOTC_ER_EXCEED_MAX_SESSION)
			{
				printf("EXCEED MAX SESSION!!!\n");
			}
				
			ret = IOTC_Connect_ByUID_Parallel(__rdt_cnnt[0].target_uid, __rdt_cnnt[i].iotc_sid);
			if(ret < 0)
			{
				printf("p2pAPIs_Client connect failed...!!\n");
			}
			else 
			{
				__rdt_cnnt[i].action = RDTCNNT_IOTC_CONNECTED;
			}
		}
		else if ( __rdt_cnnt[i].action == RDTCNNT_IOTC_CONNECTED	)
		{
			__rdt_cnnt[i].action = RDTCNNT_RDT_CONNECTING;



			__rdt_cnnt[i].rdt_id = RDT_Create(__rdt_cnnt[i].iotc_sid, RDT_WAIT_TIMEMS, 0);
			if( __rdt_cnnt[i].rdt_id < 0)
			{
				printf("RDT_Create failed[%d]!!\n", __rdt_cnnt[i].rdt_id);
				IOTC_Session_Close(__rdt_cnnt[i].iotc_sid);
				__rdt_cnnt[i].iotc_sid = -1;

				 __rdt_cnnt[i].action = RDTCNNT_NEW; // re-connect IOTC
			}
			else
			{
				__rdt_cnnt[i].action = RDTCNNT_RDT_CONNECTED;
				__rdt_cnnt[i].tx_counter = 0;
				printf("RDT_Create OK[%d]\n", __rdt_cnnt[i].rdt_id);			
			}
		}
	}
		

	 pthread_mutex_unlock(&mutex_rdt_cnnt_array);

	 return 0;
}


int rdtcnnt_send_data_to_all_client(char *send_data,int send_len)
{
	int i;
	int ret = 0;


	pthread_mutex_lock(&mutex_rdt_cnnt_array);
	for(i=0;i<MAX_RDT_CONNECTION;i++)
	{
		if ( __rdt_cnnt[i].action == RDTCNNT_RDT_CONNECTED	)
		{
			 RDT_Write(__rdt_cnnt[i].rdt_id,(char*)send_data,send_len); 

			 ret ++;
		}
	}
		

	 pthread_mutex_unlock(&mutex_rdt_cnnt_array);

	 return ret;
}

