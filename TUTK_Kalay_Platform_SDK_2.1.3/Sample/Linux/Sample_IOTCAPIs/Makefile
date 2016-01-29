
ifeq ("$(platform)","")
        platform=x86
endif

ifeq ("$(platform)","x86")
        CFLAGS=-m32
endif


all:
	@echo === Target Platform [$(platform)] === 
	gcc $(CFLAGS) -O2 -Wall IOTCAPIs_Client.c -I./ -I../../../Include -L'../../../Lib/Linux/$(platform)' -lIOTCAPIs -lpthread -o IOTCAPIs_Client
	gcc $(CFLAGS) -O2 -Wall IOTCAPIs_Device.c -I./ -I../../../Include -L'../../../Lib/Linux/$(platform)' -lIOTCAPIs -lpthread -o IOTCAPIs_Device

clean:
	rm -rf *.o *~ *.bak IOTCAPIs_Client IOTCAPIs_Device