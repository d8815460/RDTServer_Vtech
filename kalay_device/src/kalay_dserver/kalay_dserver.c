#include <stdio.h>
#include <kalay_dserver.h>
#include "dserver.h"


int main(int argc,char *argv[])
{

	kalay_device_server_agent_start("DRFTBHN6XXUUVM6KWTE1","127.0.0.1",4663);

	return 0;
}