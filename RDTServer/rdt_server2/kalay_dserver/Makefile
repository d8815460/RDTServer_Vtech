ifdef IPHUB
	platform=arm
else
	platform=x86
endif

ifeq ("$(platform)","x86")
        CFLAGS=-m32
endif

CLIB= -lsocket++ -lpthread -ljsoncpp -lIOTCAPIs -lRDTAPIs

all:
	@echo === Target Platform [$(platform)] ===  	

ifeq ("$(platform)","x86")
	g++ --std=c++0x $(CFLAGS) -O2 -Wall kalay_dserver.cpp dserver.cpp   -L../lib  -L../iotc/Lib/Linux/x86 $(CLIB) -o kalay_dserver
else ifeq ("$(platform)","arm")
	arm-dspg-linux-gnueabi-g++ --std=c++0x $(CFLAGS) -O2 -fpermissive -Wall kalay_dserver.cpp dserver.cpp   -L../lib/arm  -L../iotc/Lib/Linux/arm $(CLIB) -o kalay_dserver
endif

clean:
	rm -rf *.o *~ *.bak kalay_dserver