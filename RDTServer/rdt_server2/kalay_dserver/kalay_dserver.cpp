#include <stdio.h>
#include "kalay_dserver.h"
#include "dserver.h"

#include "dtable.h"

int main(int argc,char *argv[])
{
	//__allObjects.dump();

	__allObjects.dumpByLocation();

	kalay_device_server_agent_start((char*)"DRFTBHN6XXUUVM6KWTE1",(char*) "/tmp/unixsocket");

	return 0;
}