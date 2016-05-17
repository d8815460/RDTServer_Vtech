#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include "IOTCAPIs.h"
#include "RDTAPIs.h"

char *test_UID = "DRFTBHN6XXUUVM6KWTE1";

#define RDT_WAIT_TIMEMS 3000
static int __start_rdt_daemon = 0;

#define RDTCNNT_NEW 1
#define RDTCNNT_IOTC_CONNECTING 2
#define RDTCNNT_IOTC_CONNECTED 3
#define RDTCNNT_RDT_CONNECTING 4
#define RDTCNNT_RDT_CONNECTED 4

struct stRDTcnnt
{
	char target_uid[20];
	int  action;
	int  iotc_sid;
	int  rdt_id;
	int  tx_counter;
	int  cnnt_state;
	struct st_SInfo Sinfo;
};

#define MAX_RDT_CONNECTION 32

pthread_mutex_t mutex_rdt_cnnt_array;

struct stRDTcnnt __rdt_cnnt[MAX_RDT_CONNECTION];
int __cnt_rdt_cnnt = 0;

int init_rdt_deamon_env()
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


int release_rdt_deamon_env()
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

int check_new_rdtcnnt_request()
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

printf("Eddy test sid:%d \n",__rdt_cnnt[i].iotc_sid);

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

int start_rdt_daemon()
{
	int i;
	int ret;
	char szBuff[4096];

	if ( __start_rdt_daemon != 0 )
		return 1;


	__start_rdt_daemon = 1;
	init_rdt_deamon_env();
	

	printf("RDT Version[%X]\n", RDT_GetRDTApiVer());

	ret = IOTC_Initialize2(0);
	if(ret != IOTC_ER_NoERROR)
	{
		printf("IOTC_Initialize error!!\n");
		return 0;
	}

	int rdtCh = RDT_Initialize();
	if(rdtCh <= 0)
	{
		printf("RDT_Initialize error!!\n");
		return 0;
	}


// New RDT connection
	pthread_mutex_lock(&mutex_rdt_cnnt_array);
	memcpy(__rdt_cnnt[0].target_uid,test_UID,20);
	__rdt_cnnt[0].action = RDTCNNT_NEW;
	__rdt_cnnt[0].cnnt_state = 0;
	__rdt_cnnt[0].iotc_sid = -1;
	__rdt_cnnt[0].rdt_id = -1;
	pthread_mutex_unlock(&mutex_rdt_cnnt_array);
	

	i = 0;
	while(1)
	{
		check_new_rdtcnnt_request();


		// send test data
		pthread_mutex_lock(&mutex_rdt_cnnt_array);
		for(i=0;i<MAX_RDT_CONNECTION;i++)
		{
			if ( __rdt_cnnt[i].action == RDTCNNT_RDT_CONNECTED	)
			{
printf("eddy test rdt connected : [%d]:%d \n",i,__rdt_cnnt[i].rdt_id);

				sprintf(szBuff,"test.json[%d]\r\n",__rdt_cnnt[i].tx_counter);

				ret = RDT_Write(__rdt_cnnt[i].rdt_id, szBuff,(int) strlen(szBuff));
				__rdt_cnnt[i].tx_counter++;
			}
		}
			

		 pthread_mutex_unlock(&mutex_rdt_cnnt_array);



		 // polling data
		pthread_mutex_lock(&mutex_rdt_cnnt_array);
		for(i=0;i<MAX_RDT_CONNECTION;i++)
		{
			if ( __rdt_cnnt[i].action >= RDTCNNT_IOTC_CONNECTED )
			{
				__rdt_cnnt[i].cnnt_state = IOTC_Session_Check(__rdt_cnnt[i].iotc_sid, &__rdt_cnnt[i].Sinfo);

				if ( __rdt_cnnt[i].cnnt_state < 0 )
				{
					printf("RDTcnnt[%d] err:%d \n",i,__rdt_cnnt[i].cnnt_state);


					if ( __rdt_cnnt[i].rdt_id >= 0  )
					{
						RDT_Destroy(__rdt_cnnt[i].rdt_id);
						__rdt_cnnt[i].rdt_id = -1;
					}


					IOTC_Session_Close(__rdt_cnnt[i].iotc_sid);

					__rdt_cnnt[i].iotc_sid = -1;
					__rdt_cnnt[i].action = RDTCNNT_NEW; // Try to recovery cnnt
					__rdt_cnnt[i].cnnt_state = 0;
					__rdt_cnnt[i].iotc_sid = -1;
					__rdt_cnnt[i].rdt_id = -1;					
				}
			}
			
			if ( __rdt_cnnt[i].action == RDTCNNT_RDT_CONNECTED	)
			{
printf("eddy test rdt polling  : [%d]:%d \n",i,__rdt_cnnt[i].rdt_id);

				ret = RDT_Read(__rdt_cnnt[i].rdt_id, szBuff, 1024, RDT_WAIT_TIMEMS);			

				if ( ret > 0 )
				{
					szBuff[ret] = 0;
					printf("eddy test recv[%d]:\n%s\n",ret,szBuff);
				}			
			}
		}
			

		 pthread_mutex_unlock(&mutex_rdt_cnnt_array);






		usleep(1000000);
	}


	release_rdt_deamon_env();


	RDT_DeInitialize();
	IOTC_DeInitialize();

	return 0;
}



int stop_rdt_daemon()
{
	return 1;
}