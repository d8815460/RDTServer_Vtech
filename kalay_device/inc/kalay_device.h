#ifndef __KALAY_DEVCIE_H
#define __KALAY_DEVCIE_H

	int kalay_device_start();
	int kalay_device_stop();


	int kalay_device_control(char *command,int lenght,char *response_buffer,int buffer_size,int wait,int timeout);
	int kalay_device_message(char *buffer,int buffer_size);

#endif