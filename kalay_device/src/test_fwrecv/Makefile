
ifeq ("$(platform)","")
        platform=x86
endif

ifeq ("$(platform)","x86")
        CFLAGS=-m32
endif

all:
	@echo === Target Platform [$(platform)] ===  	
	gcc $(CFLAGS) -O2 -Wall test_fwrecv.c -I./ -I../../inc -I../../iotc/Include -L'../../iotc/Lib/Linux/$(platform)' -lpthread -o test_fwrecv

clean:
	rm -rf *.o *~ *.bak dserver 
