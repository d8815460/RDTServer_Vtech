all: 	
	gcc -O2 -Wall AVAPIs_Server.c -I./ -I../../../Include ../../../Lib/MAC/libIOTCAPIs_ALL.a   -lpthread -o AVAPIs_Server_x64
	gcc -O2 -Wall AVAPIs_Client.c -I./ -I../../../Include ../../../Lib/MAC/libIOTCAPIs_ALL.a   -lpthread -o AVAPIs_Client_x64
	gcc -O2 -m32 -Wall AVAPIs_Server.c -I./ -I../../../Include ../../../Lib/MAC/libIOTCAPIs_ALL.a   -lpthread -o AVAPIs_Server_x86
	gcc -O2 -m32 -Wall AVAPIs_Client.c -I./ -I../../../Include ../../../Lib/MAC/libIOTCAPIs_ALL.a   -lpthread -o AVAPIs_Client_x86
clean:
	rm -rf *.o *~ *.bak AVAPIs_Server_x86 AVAPIs_Client_x86 AVAPIs_Server_x64 AVAPIs_Client_x64