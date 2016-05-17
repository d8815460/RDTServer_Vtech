#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kalay_device.h"
#include "rdt_daemon.h"

char *TestMessage=\
"{\r\n\
	\"error\"   : 0,\r\n\
	\"response\":\r\n\
	{\r\n\
		\"id\"		: \"01ouo3umgui3rnouwm\",\r\n\
		\"name\"		: \"ACC - I am Getway\",\r\n\
		\"locations\"	: [\r\n\
			{\r\n\
				\"id\" 		 : \"l01\",\r\n\
			  	\"name\"  	 : \"Location 1\",\r\n\
		      	\"accessories\": [\r\n\
		    	    {\r\n\
		        		\"id\"  		: \"a01\", \r\n\
		        		\"name\"		: \"Switch 01\",\r\n\
      					\"status\"	: 0,\r\n\
      					\"accessory\" : 4,\r\n\
      					\"trigger\"	: 0\r\n\
		        	}\r\n\
		      	]\r\n\
		    },\r\n\
		    {\r\n\
		    	\"id\" 		 : \"l02\",\r\n\
		      	\"name\"		 : \"Location 2\",\r\n\
		      	\"accessories\": [\r\n\
		        	{\r\n\
		        		\"id\"		: \"a02\",\r\n\
		        		\"name\"		: \"Switch 02\",\r\n\
      					\"status\"	: 0,\r\n\
      					\"accessory\"	: 4,\r\n\
      					\"trigger\"	: 0\r\n\
			        }\r\n\
		      	],\r\n\
		      	\"groups\"	 : [\r\n\
		      		{\r\n\
		      			\"id\"	 	 : \"g01\",\r\n\
		      			\"name\"	 	 : \"Group 01\",\r\n\
      					\"status\"	: 0,\r\n\
      					\"accessory\"	: 5,\r\n\
      					\"trigger\"	: 0,\r\n\
		      					\r\n\
		      			\"accessories\": [\r\n\
		      				{\r\n\
		      					\"id\"  		: \"a03\",\r\n\
				        		\"name\"		: \"Light Bolb 01\",\r\n\
		      					\"status\"	: 0,\r\n\
		      					\"accessory\"	: 0,\r\n\
		      					\"trigger\"	: 0\r\n\
	      					},\r\n\
	      					{\r\n\
		      					\"id\"  		: \"a04\",\r\n\
		      					\"name\"		: \"Light Bolb 02\",\r\n\
		      					\"status\"	: 0,\r\n\
		      					\"accessory\"	: 0,\r\n\
		      					\"trigger\"	: 0\r\n\
	      					}\r\n\
		      			]\r\n\
		      		}\r\n\
		      	]\r\n\
		    },\r\n\
		    {\r\n\
				\"id\" 		 : \"l03\",\r\n\
			  	\"name\"  	 : \"Location 1\",\r\n\
		      	\"accessories\": [\r\n\
		    	    {\r\n\
		        		\"id\"  		: \"a01\", \r\n\
		        		\"name\"		: \"Garage Door Sensor 01\",\r\n\
      					\"status\"	: 2,\r\n\
      					\"accessory\" : 2,\r\n\
      					\"trigger\"	: 1\r\n\
		        	}\r\n\
		      	]\r\n\
		    }\r\n\
		]\r\n\
	}\r\n\
\r\n\
 }";


int kalay_device_start()
{
	start_rdt_daemon();

	return 1;
}

int kalay_device_stop()
{
	stop_rdt_daemon();
	return 1;	
}

int kalay_device_control(char *command,int lenght,char *response_buffer,int buffer_size,int wait,int timeout)
{
	

	if ( response_buffer != NULL )
	{
		strcpy(response_buffer,TestMessage);
	}


	return 0;
}




int kalay_device_message(char *buffer,int buffer_size)
{
	start_rdt_daemon();

	if ( buffer != NULL )
	{
		strcpy(buffer,TestMessage);
	}
	return 0;
}
