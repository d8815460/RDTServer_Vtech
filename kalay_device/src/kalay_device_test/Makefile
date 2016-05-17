
ifeq ("$(platform)","")
        platform=x86
endif

ifeq ("$(platform)","x86")
        CFLAGS=-m32
endif

all:
	@echo === Target Platform [$(platform)] ===  	
	gcc $(CFLAGS) -O2 -Wall test.c -I./ -I../../inc -I../../iotc/Include -L'../../lib/linux/$(platform)' -L'../../iotc/Lib/Linux/$(platform)' -L'../../iotc/Lib/Linux/$(platform)' -lpthread -lkalay_device -lIOTCAPIs -lRDTAPIs -o test

  
clean:
	rm -rf *.o *~ *.bak dserver 
