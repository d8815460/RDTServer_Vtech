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

#include "fw_api.h"
#include "fw_parser.h"

using namespace std;
using libsocket::unix_stream_client;
using std::string;

unix_stream_client sock;


static int __fwapi_inited = 0;

static unsigned int __seq = 0;

static int  __fw_sock_status = -1;
static char __unixsocket_path[512] = { 0 };


pthread_mutex_t mutex_seq;

unsigned int getSeq()
{
	int ret = -1;

	pthread_mutex_lock(&mutex_seq);


	__seq++;
	if ( (__seq & 0x80000000) ) // Control seq in "1-0x7fffffff"
		__seq = 1;

	ret = __seq;


	pthread_mutex_unlock(&mutex_seq);

	return ret;
}


void *_thread_unixsocket_read(void *arg)
{
	char *fw_recv_buff = NULL;
	unsigned int recv_buff_size = 4;
	int rc;
	int state = 0;
	unsigned int json_len = 0;
	unsigned int readpos = 0;

	fw_recv_buff = (char*)malloc(recv_buff_size);

	if ( fw_recv_buff == NULL )
	{
		printf("Error: unixsocket receive buffer malloc(%d) fail \n",recv_buff_size);

		pthread_exit(0);  // FixMe: TBD error handle
	}

	while(1)
	{
		if ( fwapi_cnnt_get_status() > 0 )
		{
			try {
				if ( state == -1 ) // Ignore this packet
				{
					unsigned int recv_size = json_len - readpos;


					if ( recv_size >  recv_buff_size  )
						recv_size = recv_buff_size;

					rc = sock.rcv(fw_recv_buff,recv_size); // pass

					if ( rc > 0 )
					{
						readpos += rc;
							
						if ( readpos == json_len )
						{
							printf("Error: unixsocket ignore a json because no enought receive buffer(size:%d)\n",json_len);

							state = 0;
							readpos = 0;
						}
					}
				}
				else if ( state < 4)
				{
					rc = sock.rcv(fw_recv_buff,1);
					if ( rc == 1 )
					{
						json_len <<= 8;
						json_len |= ((unsigned char) fw_recv_buff[0]);
						
						state++;
					}

					if ( state == 4 )
					{
						if ( recv_buff_size < (json_len+1) ) // will add string terminal character to make sure json parser works.
						{
							int new_recv_buff_size;

							if ( fw_recv_buff != NULL )
							{
								free(fw_recv_buff);
								fw_recv_buff = NULL;
							}

							new_recv_buff_size = (json_len+1+1023)/1024*1024; // increment by K avoid busy for malloc 


							// FixMe: consider reduce size if new buffer size is too huge and just for once

							fw_recv_buff = (char*)malloc(new_recv_buff_size);

							if ( fw_recv_buff == NULL ) 
							{
								
								printf("Error: unixsocket receive buffer malloc(%d) fail \n",new_recv_buff_size);
								state = -1; // Ignore this packet FixMe: TBD error handle 

								// try to recovery size to orginal
								fw_recv_buff = (char*)malloc(recv_buff_size);

								if ( fw_recv_buff == NULL )
								{
									printf("Error: unixsocket receive buffer malloc(%d) fail(receovery) \n",recv_buff_size);

									break; // FixMe : TBD error handle
								}
							}
							else
							{
								recv_buff_size = new_recv_buff_size;
								printf("unixsocket receive buffer resize to %d \n",new_recv_buff_size);
							}							
						}
					}
				}
				else 
				{
					unsigned int recv_size = json_len - readpos;

					if ( recv_size >  (recv_buff_size-1)  ) // it should not happen 
						recv_size = recv_buff_size-1;


					rc = sock.rcv(&fw_recv_buff[readpos],recv_size);

					if ( rc > 0 )
					{
						Json::Reader reader;
						Json::Value value;						
						


						readpos += rc;
							
						if ( readpos == json_len )
						{
							fw_recv_buff[json_len] = 0;

							if ( reader.parse((char*) fw_recv_buff, value) )
							{
								fw_parser(value);
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


	if ( fw_recv_buff != NULL )
	{
		free(fw_recv_buff);
		fw_recv_buff = NULL;
		recv_buff_size = 0;
	}


	pthread_exit(0);
}

int fwapi_init()
{
	if ( __fwapi_inited != 0  )
		return 0;

	__fwapi_inited = 1;
	pthread_mutex_init(&mutex_rdt_cnnt_array, NULL);

	return 1;
}


int fwapi_destroy()
{
	pthread_mutex_destroy(&mutex_rdt_cnnt_array);
	__fwapi_inited = 0;

	return 0;
}

int fwapi_connect(char *path)
{
	pthread_t thread_id_unixsocket_read;

	if ( path != NULL )
		strcpy(__unixsocket_path,path);
 
	try {
		sock.connect(__unixsocket_path);

		__fw_sock_status = 1;


		pthread_create(&thread_id_unixsocket_read, NULL, &_thread_unixsocket_read, NULL);	
		pthread_detach(thread_id_unixsocket_read);


    } catch (const libsocket::socket_exception& exc)
    {
	std::cerr << exc.mesg;
		__fw_sock_status = -1;

		usleep(1000000);
    }

	return __fw_sock_status;
}


int fwapi_cnnt_check_status()
{
	if ( __fw_sock_status == -1 )
	{
		__fw_sock_status = fwapi_connect(NULL);

		if ( __fw_sock_status > 0 )
		{
			printf("fw socket connected\n");
		}
	}

	return __fw_sock_status;
}


int fwapi_cnnt_get_status()
{
	return __fw_sock_status;
}


int fwapi_getall()
{

//unsigned char payload[] = {0x74,0x65,0x73,0x74};
	unsigned char payload_length_buffer[4+2048];
	unsigned long payload_length;
	int rc;


// 			action = !action;



// 			if (action == 20)
// 				action = 80;
// 			else
// 				action = 20;


	string arg = std::to_string(getSeq());	


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


	rc = sock.snd(total_payload.c_str(),payload_length); // for JSON to parse properly on server side
	printf("Test send len %d - ret :%d\n",(int) payload_length,rc);

	return 0;
}



int fwapi_set(Json::Value &objects)
{

//unsigned char payload[] = {0x74,0x65,0x73,0x74};
	unsigned char payload_length_buffer[4+2048];
	unsigned long payload_length;
	int rc;





	string arg = std::to_string(getSeq());	


	Json::Value root;
	std::string total_payload;

    root["func"] = "set";

	root["seq"] = arg.c_str();

	root["objects"] = objects;

	total_payload = root.toStyledString().c_str();

	printf("payload\n%s\n",total_payload.c_str());


	payload_length = total_payload.length();

	payload_length_buffer[0] = (((unsigned long)payload_length) &0xff000000)>>24;
	payload_length_buffer[1] = (((unsigned long)payload_length) &0x00ff0000)>>16;
	payload_length_buffer[2] = (((unsigned long)payload_length) &0x0000ff00)>>8;
	payload_length_buffer[3] = (((unsigned long)payload_length) &0x000000ff);


	rc = sock.snd(payload_length_buffer,4); // send json length

	if ( rc < 0 )
	{

	}

	rc = sock.snd(total_payload.c_str(),payload_length); // for JSON to parse properly on server side

	if ( rc < 0 )
	{
		
	}

	return 0;
}


int fwapi_get(Json::Value &objects)
{

//unsigned char payload[] = {0x74,0x65,0x73,0x74};
	unsigned char payload_length_buffer[4+2048];
	unsigned long payload_length;
	int rc;



	string arg = std::to_string(getSeq());	


	Json::Value root;
	std::string total_payload;

    root["func"] = "get";

	root["seq"] = arg.c_str();
	root["objects"] = objects;

	total_payload = root.toStyledString().c_str();

	payload_length = total_payload.length();

	payload_length_buffer[0] = (((unsigned long)payload_length) &0xff000000)>>24;
	payload_length_buffer[1] = (((unsigned long)payload_length) &0x00ff0000)>>16;
	payload_length_buffer[2] = (((unsigned long)payload_length) &0x0000ff00)>>8;
	payload_length_buffer[3] = (((unsigned long)payload_length) &0x000000ff);


	rc = sock.snd(payload_length_buffer,4); // send json length
	printf("Test send len 4 %x %x %x %x - ret :%d\n",payload_length_buffer[0],payload_length_buffer[1],payload_length_buffer[2],payload_length_buffer[3],rc);


	rc = sock.snd(total_payload.c_str(),payload_length); // for JSON to parse properly on server side
	printf("Test send len %d - ret :%d\n",(int) payload_length,rc);

	return 0;
}


