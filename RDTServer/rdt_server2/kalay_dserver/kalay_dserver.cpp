#include <stdio.h>

#include "dserver.h"
#include "dtable.h"

// char *__testUID="DRFTBHN6XXUUVM6KWTE1";
const char *__emualtorVer="0.1.1";

int main(int argc,char *argv[])
{
	//__allObjects.dump();
	//__allObjects.dumpByLocation();

	if ( argc != 2 )
	{
		printf("miss UID\n");
		printf("usage './kalay_dserver UID'\n");
		exit(0);
	}

	printf("UID:%s\n",argv[1]);

	kalay_device_server_agent_start((char*)argv[1],(char*) "/tmp/unixsocket");

	return 0;
}