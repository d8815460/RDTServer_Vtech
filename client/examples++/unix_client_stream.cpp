# include "../headers/unixclientstream.hpp"
# include "../headers/exception.hpp"
# include <string>
# include <iostream>
# include <string.h>

#include <iomanip> 

using namespace std;

// Builds a connection to /tmp/unixsocket and sends/receives data using it.

int main(void)
{

	using libsocket::unix_stream_client;
    using std::string;

    string path = "/tmp/unixsocket";

	unsigned char payload[] = {0x74,0x65,0x73,0x74};

	try {
	unix_stream_client sock(path);
	sock.snd(payload,sizeof(payload));

 
    } catch (const libsocket::socket_exception& exc)
    {
	std::cerr << exc.mesg;
    }



    return 0;
}
