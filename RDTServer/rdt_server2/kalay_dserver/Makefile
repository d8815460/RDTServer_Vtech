ifdef IPHUB
	platform=arm
else
	platform=x86
endif

ifeq ("$(platform)","x86")
        CFLAGS=-m32
endif

SRC=kalay_dserver.cpp dserver.cpp device_parser.cpp device_api.cpp rdtcnnt.c
LIB= -lsocket++ -lpthread -ljsoncpp -lIOTCAPIs -lRDTAPIs

all:
	@echo === Target Platform [$(platform)] ===  	

ifeq ("$(platform)","x86")
	g++ --std=c++0x $(CFLAGS) -O2 -Wall $(SRC) -I../headers -I../iotc/Include -L../lib  -L../iotc/Lib/Linux/x86 $(LIB) -o kalay_dserver
else ifeq ("$(platform)","arm")
	arm-dspg-linux-gnueabi-g++ --std=c++0x $(CFLAGS) -O2 -fpermissive -Wall $(SRC) -I../headers -I../iotc/Include -L../lib/arm  -L../iotc/Lib/Linux/arm $(LIB) -o kalay_dserver
endif

clean:
	rm -rf *.o *~ *.bak kalay_dserver
