
ifeq ("$(platform)","")
        platform=x86
endif

ifeq ("$(platform)","x86")
        CFLAGS=-m32
endif

all:
	@echo === Target Platform [$(platform)] ===  	
	g++ --std=c++0x $(CFLAGS) -O2 -Wall kalay_dserver.cpp dserver.cpp  jsmn.c -L../lib  -L../iotc/Lib/Linux/x86 -lsocket++ -lpthread -lIOTCAPIs -lRDTAPIs  -o kalay_dserver

clean:
	rm -rf *.o *~ *.bak unix_client
