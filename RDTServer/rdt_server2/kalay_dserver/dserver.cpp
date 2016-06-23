#include <string.h>
#include <unistd.h>

#include <json/json.h>

#include <string>
#include <iostream>


#include "dserver.h"
#include "rdtcnnt.h"
#include "device_parser.h"
#include "fw_api.h"

//for schedule
#include "dtable.h"
#include "device_api.h"
#include <time.h>

using std::string;

int sendto_rdt_client (int session,unsigned int rdt_ticket,Json::Value& responseRoot);
int sendto_all_client (Json::Value& responseRoot);
int sendto_other_client (int session,Json::Value& responseRoot);


static int __agent_start = 0;

char *__myUID[20];


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

void *_thread_schedule(void *arg)
{
	CLightBulb *plight;
	time_t rawtime;
	struct tm * timeinfo;


 	time (&rawtime);
  	timeinfo = localtime (&rawtime);
  	printf ("Current local time and date: %s", asctime(timeinfo));


	while(__agent_start == 1)
	{

		Json::Value responseRoot;
		Json::Value response;
		Json::Value objects;
		Json::Value location;
		int rc;
		int err = 1;
		string err_str;		

		//Json::Value object;
		list<CMyObject*>::iterator iter;

		std::map<unsigned int, CMyObject *>::iterator p;
		list<CMyObject*>::iterator j;
		//int nAccessoryCnt = 0;

			time (&rawtime);
  			timeinfo = localtime (&rawtime);


			for(p = __allObjects.m_mapAllObjects.begin(); p!=__allObjects.m_mapAllObjects.end(); ++p)
			{
				
				plight = (CLightBulb*) p->second;

				if ( plight->m_listObject.size() >0 && plight->m_attr_num["type"] == 0x0109 ) 
				{
					for(iter = plight->m_listObject.begin(); iter!=plight->m_listObject.end(); ++iter) //find schedule
					{
						CMyObject *pSubObject;
						pSubObject = *iter;
						int nowtime;
						int time_to_stop;
						int time_to_start;
						int time_of_week;
						if(pSubObject->m_attr_num["pow_on_on"])
						{		
							//printf("power on [%d] \n",pSubObject->m_attr_num["pow_on_on"]);
							nowtime = ((timeinfo->tm_min) + ((timeinfo->tm_hour)*60) );
							time_to_start = pSubObject->m_attr_num["pow_on_time"];
							time_to_stop = pSubObject->m_attr_num["pow_on_time"] + pSubObject->m_attr_num["pow_on_duration"];
							time_of_week = 1 << (timeinfo->tm_wday - 1 );
							time_of_week = time_of_week&pSubObject->m_attr_num["repeat"];
							//printf("time_of_week [%d]",time_of_week);
							//printf("time of week after and [%d]",(time_of_week&pSubObject->m_attr_num["repeat"]));

							if(time_to_stop>1440){
								time_to_stop = time_to_stop - 1440; //over day
							}
							//printf("nowtime[%d],time_to_stop[%d],time_to_start[%d],time_of_week[%d]\n",nowtime,time_to_stop,time_to_start,time_of_week);
							if( nowtime >= time_to_start && nowtime <= time_to_stop && time_of_week) 
							{
								//"notify"
								//printf ("Current local time and date: [%d] [%d]\n",timeinfo->tm_wday,nowtime);
								plight->m_attr_num["status"] = 1;

									//printf("notify found object %s \n",pObject->m_attr_str["name"].c_str());


									response["uid"] = (char*) __myUID;
									response["api"] = "notify";

									//rdt_ticket = 0;

									try {
		
											if ( plight->m_pLocation != NULL ) 
											{
												location["id"] = plight->m_pLocation->m_id;
												location["name"] = plight->m_pLocation->m_attr_str["name"];

												objects[0]["location"] = location;
											}
											objects[0]["status"] = plight->m_attr_num["status"];
											plight->getAttr(objects[0]);			
											response["objects"] = objects;

											err = 0;

								    } catch (const libsocket::socket_exception& exc)
								    {
										std::cerr << exc.mesg;
										err_str = exc.mesg;
								    }


									responseRoot["error"] = err;
									if ( err_str.length() != 0 )
										responseRoot["error_str"] = err_str;
									responseRoot["response"] = response;


									printf("notify_detail:\n%s\n-------------------\n",(char*)responseRoot.toStyledString().c_str());
									rc = sendto_all_client(responseRoot);
									if(rc<0){

									}

							}
							//printf ("Current local time and date: [%d] [%d]\n",timeinfo->tm_wday,nowtime);
						}

						sleep(1);

						if(pSubObject->m_attr_num["pow_off_on"])
						{
							//printf("power off [%d] \n",pSubObject->m_attr_num["pow_off_on"]);
														//printf("power on [%d] \n",pSubObject->m_attr_num["pow_on_on"]);
							nowtime = ((timeinfo->tm_min) + ((timeinfo->tm_hour)*60) );
							time_to_start = pSubObject->m_attr_num["pow_off_time"];
							time_to_stop = pSubObject->m_attr_num["pow_off_time"] + pSubObject->m_attr_num["pow_off_duration"];
							time_of_week = 1 << (timeinfo->tm_wday - 1 );
							time_of_week = time_of_week&pSubObject->m_attr_num["repeat"];
							//printf("time_of_week [%d]",time_of_week);
							//printf("time of week after and [%d]",(time_of_week&pSubObject->m_attr_num["repeat"]));

							if(time_to_stop>1440){
								time_to_stop = time_to_stop - 1440; //over day
							}
							//printf("nowtime[%d],time_to_stop[%d],time_to_start[%d],time_of_week[%d]\n",nowtime,time_to_stop,time_to_start,time_of_week);
							if( nowtime >= time_to_start && nowtime <= time_to_stop && time_of_week) 
							{
								//"notify"
								//printf ("Current local time and date: [%d] [%d]\n",timeinfo->tm_wday,nowtime);
								plight->m_attr_num["status"] = 0;

									//printf("notify found object %s \n",pObject->m_attr_str["name"].c_str());

									response["uid"] = (char*) __myUID;
									response["api"] = "notify";

									//rdt_ticket = 0;

									try {
		
											if ( plight->m_pLocation != NULL ) 
											{
												location["id"] = plight->m_pLocation->m_id;
												location["name"] = plight->m_pLocation->m_attr_str["name"];

												objects[0]["location"] = location;
											}
											objects[0]["status"] = plight->m_attr_num["status"];
											plight->getAttr(objects[0]);			
											response["objects"] = objects;

											err = 0;

								    } catch (const libsocket::socket_exception& exc)
								    {
										std::cerr << exc.mesg;
										err_str = exc.mesg;
								    }


									responseRoot["error"] = err;
									if ( err_str.length() != 0 )
										responseRoot["error_str"] = err_str;
									responseRoot["response"] = response;


									printf("notify_detail:\n%s\n-------------------\n",(char*)responseRoot.toStyledString().c_str());
									rc = sendto_all_client(responseRoot);
									if(rc<0){
										
									}

							}
							//printf ("Current local time and date: [%d] [%d]\n",timeinfo->tm_wday,nowtime);
						}

					}
					
				}

			}


			sleep(10);

	}

	pthread_exit(0);
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




int kalay_device_server_agent_start(char *UID,char *unixsocket_path)
{
	pthread_t thread_id_Login;
	pthread_t thread_id_Listen;
	pthread_t thread_schedule;
	
    int ret;
    int rdtCh;

    //int action;
    
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

	
	pthread_create(&thread_schedule, NULL, &_thread_schedule, (void *)__myUID);	
	pthread_detach(thread_schedule);
	
    




    //keep communicating with server
    while(__agent_start == 1)
    {
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


