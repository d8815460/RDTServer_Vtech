#ifndef __RDTCNNT_H__
#define __RDTCNNT_H__


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

	#define RDT_WAIT_TIMEMS 3000

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
		
		unsigned char *rdt_recv_option;
		unsigned char *rdt_recv_data;


	};

	#define MAX_RDT_CONNECTION 32

	extern struct stRDTcnnt __rdt_cnnt[MAX_RDT_CONNECTION]; // define in dserver.cpp


	int rdtcnnt_init();
	int rdtcnnt_destroy();

	int rdtcnnt_new_iotc_conntected(int iotc_sid);

	int rdtcnnt_check_status();

#endif