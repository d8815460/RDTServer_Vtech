
ifeq ("$(platform)","")
        platform=x86
endif

ifeq ("$(platform)","x86")
        CFLAGS=-m32
endif

all:
	@echo === Target Platform [$(platform)] ===  	
	gcc  -O2 -Wall RDTServer.c -I./ -I../../../Include -L'../../../Lib/MAC' -lpthread -lIOTCAPIs_ALL  -o RDTServer
	#gcc $(CFLAGS) -O2 -Wall RDTClient.c -I./ -I../../../Include -L'../../../Lib/MAC' -lpthread -lIOTCAPIs_ALL  -o RDTClient

clean:
	rm -rf *.o *~ *.bak RDTServer RDTClient
