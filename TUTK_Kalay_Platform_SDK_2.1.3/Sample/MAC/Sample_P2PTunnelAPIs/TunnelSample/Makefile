all: 	
	gcc -O2 -Wall P2PTunnelServer.c -I./ -I./include -I../../../../Include -lpthread -L../../../../Lib/MAC -lIOTCAPIs_P2PTunnel -o P2PTunnelServer_x64
	gcc -O2 -Wall P2PTunnelAgent.c -I./ -I./include -I../../../../Include -lpthread -L../../../../Lib/MAC -lIOTCAPIs_P2PTunnel -o P2PTunnelAgent_x64
	gcc -m32 -O2 -Wall P2PTunnelServer.c -I./ -I./include -I../../../../Include -lpthread -L../../../../Lib/MAC -lIOTCAPIs_P2PTunnel -o P2PTunnelServer_x86
	gcc -m32 -O2 -Wall P2PTunnelAgent.c -I./ -I./include -I../../../../Include -lpthread -L../../../../Lib/MAC -lIOTCAPIs_P2PTunnel -o P2PTunnelAgent_x86	
clean:
	rm -rf *.o *~ *.bak P2PTunnelServer_x86 P2PTunnelAgent_x86 P2PTunnelServer_x64 P2PTunnelAgent_x64