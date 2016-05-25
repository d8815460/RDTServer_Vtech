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
#include "rdtcnnt.h"
#include "device_parser.h"

using namespace std;


static int __agent_start = 0;

char *__myUID[20];



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

		usleep(1000000);
    }

	return ret;
}


void *_thread_Listen(void *arg)
{
	int iotc_sid;

	while(__agent_start == 1)
    {
		iotc_sid = IOTC_Listen(300000);

		if(iotc_sid > -1)
		{
			const char *mode[3] = {"P2P", "RLY", "LAN"};
			struct st_SInfo Sinfo;
			int rc;

			IOTC_Session_Check(iotc_sid, &Sinfo);
			printf("Client from %s:%d Mode=%s\n",Sinfo.RemoteIP, Sinfo.RemotePort, mode[(int)Sinfo.Mode]);


			rc = rdtcnnt_new_iotc_conntected(iotc_sid);

			if ( rc < 0 )
			{
				printf("Error:No available session.\n");
			}
			
		}
	}

	pthread_exit(0);
}


int init_dserver_env()
{	

	rdtcnnt_init();

	
	return 0;
}


int release_dserver_env()
{	
	rdtcnnt_destroy();



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
				__rdt_cnnt[i].iotc_sid = -1;

				pthread_mutex_destroy(&__rdt_cnnt[i].mutex_datalink);

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
				__rdt_cnnt[i].iotc_sid = -1;

				pthread_mutex_destroy(&__rdt_cnnt[i].mutex_datalink);

				memset(&__rdt_cnnt[i],0,sizeof(struct stRDTcnnt)); // Clean session info					
				__cnt_rdt_cnnt--;

				printf("free session %d \n",i);
			}
		}

		if ( __rdt_cnnt[i].action == RDTCNNT_RDT_CONNECTED	)
		{
			int rc;
			rc  = rdtcnnt_check_packet(i);

			if ( rc == 1 )
			{
				device_parser(i
					,__rdt_cnnt[i].rdtread_option
					,__rdt_cnnt[i].rdtread_option_length
					,__rdt_cnnt[i].rdtread_data
					,__rdt_cnnt[i].rdtread_data_length);


				rdtcnnt_reset_packet(i);
			}
		}		
	}
		

	pthread_mutex_unlock(&mutex_rdt_cnnt_array);


	return 0;
}


int fw_sock_status = -1;

void *_thread_unixsocket_read(void *arg)
{
	char fw_recv_buff[1024*16];
	int rc;
	int state = 0;
	unsigned long json_len = 0;
	unsigned long readpos = 0;




	while(1)
	{
//printf("eddy tetst fw_sockt_status %d \n",fw_sock_status);
		if ( fw_sock_status > 0 )
		{
			try {
//printf("eddy test state:%d \n",state);

				if ( state < 4)
				{
					rc = sock.rcv(fw_recv_buff,1);
					if ( rc == 1 )
					{
						json_len <<= 8;
						json_len = fw_recv_buff[0];
						
						state++;
					}
					
				}
				else 
				{
					int recv_size = json_len - readpos;

//printf("eddy test recv_len:%d \n",(int) json_len);					

					if ( recv_size > (int) sizeof(fw_recv_buff)  )
						recv_size = sizeof(fw_recv_buff);




					rc = sock.rcv(&fw_recv_buff[readpos],recv_size);

					if ( rc > 0 )
					{
						Json::Reader reader;
						Json::Value value;						
						std::string recv_json;


						readpos += rc;
							
						if ( readpos == json_len )
						{
							fw_recv_buff[json_len] = 0;

							if ( reader.parse((char*) fw_recv_buff, value) )
							{
								recv_json = value.toStyledString().c_str();

								printf("unixsocket receive len:%d :\n data-len : %d\n %s\n---------------\n"
									,(int)json_len
									,recv_json.length()
									,recv_json.c_str() );

							}
							else
							{
								printf("unixsocket receive a non-json format string\n");
							}

							state = 0;
							readpos = 0;
						}
					}
				}
		    } catch (const libsocket::socket_exception& exc)
		    {
				std::cerr << exc.mesg;

				//break;
		    }
		}
		else
		{
			usleep(500000);
		}
	}

	pthread_exit(0);
}




int kalay_device_server_agent_start(char *UID,char *unixsocket_path)
{
	pthread_t thread_id_Login;
	pthread_t thread_id_Listen;
	pthread_t thread_id_unixsocket_read;
    int ret;
    int rdtCh;

    int action,seq;
    int timer_counter = 0;
    string test = "";	


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


	pthread_create(&thread_id_Login, NULL, &_thread_Login, (void *)__myUID);	
	pthread_detach(thread_id_Login);

	pthread_create(&thread_id_Listen, NULL, &_thread_Listen, (void *)__myUID);	
	pthread_detach(thread_id_Listen);
    
	pthread_create(&thread_id_unixsocket_read, NULL, &_thread_unixsocket_read, NULL);	
	pthread_detach(thread_id_unixsocket_read);


	action = 20;

	seq = 0;



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

    	if ( fw_sock_status > 0 && (timer_counter % 1000) == 0 )
    	{
    		//unsigned char payload[] = {0x74,0x65,0x73,0x74};
    		unsigned char payload_length_buffer[4+2048];
    		unsigned long payload_length;
    		int rc;


// 			action = !action;

			seq++;

// 			if (action == 20)
// 				action = 80;
// 			else
// 				action = 20;

	
			string arg = std::to_string(seq);	


			Json::Value root;
			std::string total_payload;

// 		    root["id"] = "0298ed5e25";
		    //root["no"] = test.c_str();  test += "0";


// 			root["functionName"] = "toggle";
		    root["func"] = "getAll";
// 			root["functionState"] = arg.c_str();

			root["seq"] = arg.c_str();

			total_payload = root.toStyledString().c_str();

			payload_length = total_payload.length();

			payload_length_buffer[0] = (((unsigned long)payload_length) &0xff000000)>>24;
			payload_length_buffer[1] = (((unsigned long)payload_length) &0x00ff0000)>>16;
			payload_length_buffer[2] = (((unsigned long)payload_length) &0x0000ff00)>>8;
			payload_length_buffer[3] = (((unsigned long)payload_length) &0x000000ff);


			//strcpy((char*)&payload_length_buffer[4],(char*)total_payload.c_str());

//rc = sock.snd(payload_length_buffer,4+payload_length); // send json length
//printf("Test send len 4 %x %x %x %x - ret :%d\n",payload_length_buffer[0],payload_length_buffer[1],payload_length_buffer[2],payload_length_buffer[3],rc);



			rc = sock.snd(payload_length_buffer,4); // send json length
			printf("Test send len 4 %x %x %x %x - ret :%d\n",payload_length_buffer[0],payload_length_buffer[1],payload_length_buffer[2],payload_length_buffer[3],rc);

usleep(3000); // for debug only
			rc = sock.snd(total_payload.c_str(),payload_length); // for JSON to parse properly on server side
			printf("Test send len %d - ret :%d\n",(int) payload_length,rc);
    	}



    	rdtcnnt_check_status();

		

        usleep(1000);
        timer_counter+=1;
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


