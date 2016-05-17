
ifeq ("$(platform)","")
        platform=x86
endif

ifeq ("$(platform)","x86")
        CFLAGS=-m32
endif

all:
	@echo === Target Platform [$(platform)] ===  	
	gcc $(CFLAGS) -O2 -Wall kalay_dserver.c dserver.c  jsmn.c -I./ -I../../inc -I../../iotc/Include -L'../../iotc/Lib/Linux/$(platform)' -lpthread -lIOTCAPIs -lRDTAPIs -o kalay_dserver

clean:
	rm -rf *.o *~ *.bak dserver 
