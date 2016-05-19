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
else ifeq ("$(platform)","arm")
endif

clean:
	rm -rf *.o *~ *.bak kalay_dserver