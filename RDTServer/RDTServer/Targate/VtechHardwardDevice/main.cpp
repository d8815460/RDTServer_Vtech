#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <errno.h>
#include <limits.h>
#include <iostream>

#include "VtechIPHubGatewayHardwardDeviceImpl.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    LOGD("uid = %s", argv[1]);
    
    VtechIPHubGatewayHardwardDeviceImpl device;
    device.run(argv[1]);
    
	return 0;
}
