
ifeq ("$(platform)","")
        platform=x86
endif

ifeq ("$(platform)","x86")
        CFLAGS=-m32
endif

all:
	@echo === Target Platform [$(platform)] ===
	gcc -s $(CFLAGS) -O2 -Wall P2PTunnelServer.c -I./ -I../../../Include -L'../../../Lib/Linux/$(platform)' -lP2PTunnelAPIs -lRDTAPIs -lIOTCAPIs -lpthread -lrt -o P2PTunnelServer
	gcc -s $(CFLAGS) -O2 -Wall P2PTunnelAgent.c -I./ -I../../../Include -L'../../../Lib/Linux/$(platform)'  -lP2PTunnelAPIs -lRDTAPIs -lIOTCAPIs -lpthread -lrt -o P2PTunnelAgent


clean:
	rm -rf *.o *~ *.bak P2PTunnelServer P2PTunnelAgent
