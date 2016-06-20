#include "../headers/exception.hpp"
#include <string.h>
#include <unistd.h>

#include <json/json.h>

#include <string>
#include <iostream>


#include "dserver.h"

#include "fw_api.h"


using namespace std;



void *thread_unixsocket_read(void *arg);


CVtechIPHub __ipHub("/tmp/unixsocket");


CVtechIPHub::CVtechIPHub(const char *unixsocket_path)
{
	pthread_mutex_init(&mutex_seq, NULL);

	statusSock = -1;
	seq = 0;
	getAllDone = 0;

	if ( unixsocket_path != NULL )
		strcpy(_unixsocket_path,unixsocket_path);
	else
		strcpy(_unixsocket_path,"");

	runThread = 1;


	pthread_create(&thread_id_unixsocket_read, NULL, &thread_unixsocket_read, this);	
	pthread_detach(thread_id_unixsocket_read); 
}

CVtechIPHub::~CVtechIPHub()
{
	runThread = 0;

	pthread_mutex_destroy(&mutex_seq);
}



unsigned int CVtechIPHub::getSeq()
{
	int ret = -1;

	pthread_mutex_lock(&mutex_seq);


	seq++;
	if ( (seq & 0x80000000) ) // Control seq in "1-0x7fffffff"
		seq = 1;

	ret = seq;


	pthread_mutex_unlock(&mutex_seq);

	return ret;
}


void *thread_unixsocket_read(void *arg)
{
	CVtechIPHub *ipHub;
	char *fw_recv_buff = NULL;
	unsigned int recv_buff_size = 4;
	int rc;
	int state = 0;
	unsigned int json_len = 0;
	unsigned int readpos = 0;

	ipHub = (CVtechIPHub*) arg;

	fw_recv_buff = (char*)malloc(recv_buff_size);

	if ( fw_recv_buff == NULL )
	{
		printf("Error: unixsocket receive buffer malloc(%d) fail \n",recv_buff_size);

		pthread_exit(0);  // FixMe: TBD error handle
	}

	while(ipHub->runThread)
	{

		if ( ipHub->statusSock == -1 )
		{
			ipHub->connectToGateway();
		}
		else if ( ipHub->fwapi_cnnt_get_status() > 0 )
		{
			try {
				if ( state == -1 ) // Ignore this packet
				{
					unsigned int recv_size = json_len - readpos;


					if ( recv_size >  recv_buff_size  )
						recv_size = recv_buff_size;


					rc = ipHub->sock.rcv(fw_recv_buff,recv_size); // pass
				

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
					rc = ipHub->sock.rcv(fw_recv_buff,1);
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


					rc = ipHub->sock.rcv(&fw_recv_buff[readpos],recv_size);

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
								ipHub->parser(value);
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



int CVtechIPHub::connectToGateway()
{
	try {
		sock.connect(_unixsocket_path);

		getAllDone = 0;
		sleep(1);
		fwapi_getall();

		statusSock = 1;

    } catch (const libsocket::socket_exception& exc)
    {
		std::cerr << exc.mesg;

		statusSock = -1;

		usleep(1000000);
    }

	return statusSock;
}




int CVtechIPHub::fwapi_cnnt_get_status()
{
	return statusSock;
}


int CVtechIPHub::sendToGateway(Json::Value& payload)
{
	int ret = 0;
	unsigned char buffLength[4];
	int rc;

	Json::FastWriter fastWriter;
	std::string strSendOut;

	unsigned int strSendOutLength;



	strSendOut = fastWriter.write(payload);


	strSendOutLength  = strSendOut.length();




	buffLength[0] = (((unsigned long)strSendOutLength) &0xff000000)>>24;
	buffLength[1] = (((unsigned long)strSendOutLength) &0x00ff0000)>>16;
	buffLength[2] = (((unsigned long)strSendOutLength) &0x0000ff00)>>8;
	buffLength[3] = (((unsigned long)strSendOutLength) &0x000000ff);


	//strcpy((char*)&payload_length_buffer[4],(char*)total_payload.c_str());

//rc = sock.snd(payload_length_buffer,4+payload_length); // send json length
//printf("Test send len 4 %x %x %x %x - ret :%d\n",payload_length_buffer[0],payload_length_buffer[1],payload_length_buffer[2],payload_length_buffer[3],rc);



	rc = sock.snd(buffLength,4); // send json length

	if ( rc < 0 )
	{ // ## FixMe  - no error Handle

	}


	rc = sock.snd(strSendOut.c_str(),strSendOutLength); // for JSON to parse properly on server side

	if ( rc < 0 )
	{ // ## FixMe  - no error Handle

	}

	return ret;
}


int CVtechIPHub::fwapi_getall()
{

//unsigned char payload[] = {0x74,0x65,0x73,0x74};
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
	root["ver"] = __emualtorVer;

	total_payload = root.toStyledString().c_str();

	sendToGateway(root);

	return 0;
}



int CVtechIPHub::fwapi_set(Json::Value &objects,CTXRecord *txRecord)
{

//unsigned char payload[] = {0x74,0x65,0x73,0x74};
	int seq = getSeq();
	string arg = std::to_string(seq);	


	Json::Value root;
	std::string total_payload;

    root["func"] = "set";

	root["seq"] = arg.c_str();

	root["objects"] = objects;

	total_payload = root.toStyledString().c_str();

	printf("fwapi_set:sendToGateway\n%s\n",total_payload.c_str());

	txRecord->seq = seq;
	m_txQueue[seq] = txRecord;

	sendToGateway(root);

	return seq;
}


int CVtechIPHub::fwapi_get(Json::Value &objects)
{


	string arg = std::to_string(getSeq());	


	Json::Value root;
	std::string total_payload;

    root["func"] = "get";

	root["seq"] = arg.c_str();
	root["objects"] = objects;

	total_payload = root.toStyledString().c_str();



	sendToGateway(root);

	return 0;
}


