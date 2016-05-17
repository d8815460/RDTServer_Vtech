
ifeq ("$(platform)","")
        platform=x86
endif

ifeq ("$(platform)","x86")
        CFLAGS=-m32
endif

all:
	@echo === Target Platform [$(platform)] ===  	
	g++ --std=c++0x $(CFLAGS) -O2 -Wall unix_client_stream.cpp -lsocket++ -o unix_client

clean:
	rm -rf *.o *~ *.bak unix_client
