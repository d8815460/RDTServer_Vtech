#ifndef __FWAPI_H__
#define __FWAPI_H__

	#include "../headers/unixclientstream.hpp"

	#include <json/json.h>
	#include <pthread.h>

	#include <map>


	using libsocket::unix_stream_client;

	class CTXRecord
	{
	public:
		int seq;
		int session;
		Json::Value request;
		time_t sendTime;
	};


	class CVtechIPHub
	{
	public:
		CVtechIPHub(const char *unixsocket_path);
		~CVtechIPHub();

	protected:
		pthread_mutex_t mutex_seq;
		unsigned int seq;
		char  _unixsocket_path[512];
		pthread_t thread_id_unixsocket_read;
		int getAllDone;

		int statusSock;
		int runThread;

		unix_stream_client sock;	

	public:
		std::map<unsigned int, CTXRecord *> m_txQueue;	

	protected:
		unsigned int getSeq();

		int connectToGateway();
		int sendToGateway(Json::Value& payload);

		int parser(Json::Value& root);


	friend void *thread_unixsocket_read(void *arg);

	public:

		//static void *_thread_unixsocket_read(void *arg);

		
		int fwapi_cnnt_get_status(); // query status only

		int fwapi_getall();
		int fwapi_set(Json::Value &objects,CTXRecord *txRecord);
		int fwapi_get(Json::Value &objects);		
	};


	extern CVtechIPHub __ipHub;

#endif