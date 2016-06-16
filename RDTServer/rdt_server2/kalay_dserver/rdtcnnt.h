#ifndef __RDTCNNT_H__
#define __RDTCNNT_H__

	#include <pthread.h>

	#include "IOTCAPIs.h"
	#include "RDTAPIs.h"

	#define RDTCNNT_NEW 				1
	#define RDTCNNT_IOTC_CONNECTING 	2
	#define RDTCNNT_IOTC_CONNECTED 		3
	#define RDTCNNT_RDT_CONNECTING 		4
	#define RDTCNNT_RDT_CONNECTED 		5

	#define RDTREAD_PACKET_H		0	
	#define RDTREAD_PACKET_L		1	
	#define RDTREAD_OPTION_LENGTH_H 2	
	#define RDTREAD_OPTION_LENGTH_L	3
	#define RDTREAD_OPTION			4	
	#define RDTREAD_DATA_LENGTH_H	5	
	#define RDTREAD_DATA_LENGTH_L	6	
	#define RDTREAD_DATA			7	
	#define RDTREAD_DATA_READY		8



	#define RDT_WAIT_TIMEMS 3000

	struct stRDT_DATA
	{
		unsigned char *data;
		int data_len;
		struct stRDT_DATA *next;
	};


	struct stRDTcnnt
	{
		char target_uid[20];
		int  action;
		int  iotc_sid;
		int  rdt_id;
		int  tx_counter;
		int  cnnt_state;
		struct st_SInfo Sinfo;

		int rdtread_state;
		unsigned int rdtread_option_length;
		unsigned int retread_option_readpos;

		unsigned int rdtread_data_length;
		unsigned int retread_data_readpos;
		
		unsigned char *rdtread_option;
		unsigned char *rdtread_data;


		pthread_mutex_t mutex_datalink;
		struct stRDT_DATA *data_link;	
		struct stRDT_DATA *data_link_last;		
	};

	#define MAX_RDT_CONNECTION 32

	extern pthread_mutex_t mutex_rdt_cnnt_array;

	extern struct stRDTcnnt __rdt_cnnt[MAX_RDT_CONNECTION]; // define in dserver.cpp
	extern int __cnt_rdt_cnnt;

	int rdtcnnt_init();
	int rdtcnnt_destroy();

	int rdtcnnt_new_iotc_conntected(int iotc_sid);


	int rdtcnnt_reset_packet(int session);
	int rdtcnnt_check_packet(int session);


	int rdtcnnt_get_session_by_uid(char* UID);
	int rdtcnnt_new_iotc_request(char *UID);

	int rdtcnnt_check_new_iotc_request();

	int rdtcnnt_send_data_to_all_client(char *send_data,int send_len);
	int rdtcnnt_send_data_to_other_client(int session,char *send_data,int send_len);


#endif