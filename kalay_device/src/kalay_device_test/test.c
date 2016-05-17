#include <stdio.h>

#include <kalay_device.h>

char __response_buffer[1024*16];

int main(int argc,char *argv[])
{
	int ret;

	kalay_device_start();
	
	ret = kalay_device_control("",0,__response_buffer,sizeof(__response_buffer),1,1000);
	if ( ret < 0 )
	{
		
	}


	printf("eddy test response:\n%s\n\n",__response_buffer);

	kalay_device_stop();

	return 0;
}