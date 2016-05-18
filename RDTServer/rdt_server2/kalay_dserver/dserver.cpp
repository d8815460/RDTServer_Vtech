#include "../headers/unixclientstream.hpp"
#include "../headers/exception.hpp"
#include <string>
#include <iostream>
#include <string.h>
#include <unistd.h>

#include <iomanip> 



#include "kalay_dserver.h"
#include "dserver.h"
#include "../iotc/Include/IOTCAPIs.h"
#include "../iotc/Include/RDTAPIs.h"
#include "jsmn.h"

using namespace std;

#define RDT_WAIT_TIMEMS 3000

static int __agent_start = 0;

static char *__myUID[20];


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

using libsocket::unix_stream_client;
using std::string;

unix_stream_client sock;

void *_thread_Login(void *arg)
{
	int ret;
	char *UID = (char *)arg;


	while(__agent_start == 1)
	{
		ret = IOTC_Device_Login(UID, "", "");

		printf("     Calling IOTC_Device_Login() ret = %d\n", ret);
		if(ret == IOTC_ER_NoERROR)
			break;
		else
			sleep(60);
	}

	pthread_exit(0);
}

int connect_fw_socket(char *path)
{
;
	int ret = 0;
 
	try {
		sock.connect(path);

 		ret = 1;
    } catch (const libsocket::socket_exception& exc)
    {
	std::cerr << exc.mesg;
		ret = -1;
    }

	return ret;
}


void *_thread_Listen(void *arg)
{
	int iotc_sid;
	int i;

	while(__agent_start == 1)
    {
		iotc_sid = IOTC_Listen(300000);

		if(iotc_sid > -1)
		{
			const char *mode[3] = {"P2P", "RLY", "LAN"};
			struct st_SInfo Sinfo;

			IOTC_Session_Check(iotc_sid, &Sinfo);
			printf("Client from %s:%d Mode=%s\n",Sinfo.RemoteIP, Sinfo.RemotePort, mode[(int)Sinfo.Mode]);


			pthread_mutex_lock(&mutex_rdt_cnnt_array);

			for(i=0;i<MAX_RDT_CONNECTION;i++)
			{
				if ( __rdt_cnnt[i].action == 0 )
				{
					__rdt_cnnt[i].action = RDTCNNT_IOTC_CONNECTED;
					__rdt_cnnt[i].iotc_sid = iotc_sid;
					__rdt_cnnt[i].rdt_id = -1;
					break;
				}
			}

			pthread_mutex_unlock(&mutex_rdt_cnnt_array);	
		}


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
				}
				else
				{
					printf("RDT create OK:%d \n",rdt_id);

					__rdt_cnnt[i].action = RDTCNNT_RDT_CONNECTED;
					__rdt_cnnt[i].rdt_id = rdt_id;
					__rdt_cnnt[i].tx_counter = 0;
				}
			}
		}

		pthread_mutex_unlock(&mutex_rdt_cnnt_array);




			/*{
				struct st_SInfo info;
				if( IOTC_Session_Check(SID, &info) < 0)
				{
					
					break;
				}			
			} */
	}

	pthread_exit(0);
}


int init_dserver_env()
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


int release_dserver_env()
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



int kalay_device_server_agent_start(char *UID,char *unixsocket_path)
{
	char szBuff[4096];

	pthread_t threadID_Login;
	pthread_t threadID_Listen;
    int ret;
    int rdtCh;
    int fw_sock_status = -1;
    int i, action;


    __agent_start = 1;


    init_dserver_env();

    // init IOTC 
	ret = IOTC_Initialize2(0);
	if(ret != IOTC_ER_NoERROR)
	{
		printf("IOTC_Initialize error!!\n");
		return 0;
	}

	rdtCh = RDT_Initialize();
	if(rdtCh <= 0)
	{
		printf("RDT_Initialize error!!\n");
		return 0;
	}

	strncpy((char*)__myUID,UID,20);


	pthread_create(&threadID_Login, NULL, &_thread_Login, (void *)__myUID);	
	pthread_detach(threadID_Login);

	pthread_create(&threadID_Listen, NULL, &_thread_Listen, (void *)__myUID);	
	pthread_detach(threadID_Listen);
    

    i = 0;

	action = 0;

    //keep communicating with server
    while(__agent_start == 1)
    {
    	if ( fw_sock_status == -1 )
    	{
    		fw_sock_status = connect_fw_socket(unixsocket_path);

    		if ( fw_sock_status > 0 )
    		{
				printf("fw socket connected\n");
    		}
    	}

    	if ( fw_sock_status > 0 )
    	{
    		//unsigned char payload[] = {0x74,0x65,0x73,0x74};


std::string payload1 (\
"{\r\n\
   \"functionName\" : \"toggle\",");

std::string payload2 (\
"\r\n\
   \"functionState\" : true,");

std::string payload2a (\
"\r\n\
   \"functionState\" : ");

std::string payload2b (",");

std::string payload3 (\
"\r\n\
   \"id\" : \"0035482900123\"\r\n\
}");

std::string total_payload;

action = !action;
string arg = std::to_string(action);

total_payload = payload1 + payload2a + arg + payload2b + payload3;

#if 0
unsigned char payload[]=\
"{\r\n\
   \"functionName\" : \"toggle\",\r\n\
   \"functionState\" : 1,\r\n\
   \"id\" : \"0035482900\"\r\n\
}";
#endif
			sock.snd(total_payload.c_str(),total_payload.length()); // for JSON to parse properly on server side
//     		sock.snd(payload,sizeof(payload)-1); // for JSON to parse properly on server side
    	}




		pthread_mutex_lock(&mutex_rdt_cnnt_array);

		for(i=0;i<MAX_RDT_CONNECTION;i++)
		{
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

					printf("free session %d \n",i);
				}
			}

			if ( __rdt_cnnt[i].action == RDTCNNT_RDT_CONNECTED	)
			{
				ret = RDT_Read(__rdt_cnnt[i].rdt_id, szBuff, 1024, RDT_WAIT_TIMEMS);			

				if ( ret > 0 )
				{
					szBuff[ret] = 0;
					printf("redt recv rdt_array[%d] [%d]:\n%s\n",i,ret,szBuff);


					sprintf(szBuff,"test response.json[%d]\r\n",__rdt_cnnt[i].tx_counter);


					ret =  RDT_Write(__rdt_cnnt[i].rdt_id, szBuff, strlen(szBuff));    		
					__rdt_cnnt[i].tx_counter++;	
				}			
			}		
		}
			

		pthread_mutex_unlock(&mutex_rdt_cnnt_array);


        usleep(1000000);
    }



	RDT_DeInitialize();
	//printf("RDT_DeInitialize OK\n");
	IOTC_DeInitialize();    
     

	return 1;
}


int kalay_device_server_agent_stop()
{
	__agent_start = 0;

	return 1;
}


