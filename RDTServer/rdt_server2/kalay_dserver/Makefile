ifdef IPHUB
	platform=arm
else
	platform=x86
endif

ifeq ("$(platform)","x86")
        CFLAGS=-m32
endif

all:
	@echo === Target Platform [$(platform)] ===  	
ifeq ("$(platform)","x86")
	g++ --std=c++0x $(CFLAGS) -O2 -Wall kalay_dserver.cpp dserver.cpp  jsmn.c -L../lib  -L../iotc/Lib/Linux/x86 -lsocket++ -lpthread -lIOTCAPIs -lRDTAPIs  -o kalay_dserver
else ifeq ("$(platform)","arm")
	arm-dspg-linux-gnueabi-g++ --std=c++0x $(CFLAGS) -O2 -fpermissive -Wall kalay_dserver.cpp dserver.cpp  jsmn.c -L../lib/arm  -L../iotc/Lib/Linux/arm -lsocket++ -lpthread -lIOTCAPIs -lRDTAPIs  -o kalay_dserver
endif

clean:
	rm -rf *.o *~ *.bak kalay_dserver
