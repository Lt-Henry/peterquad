

#include <iostream>
#include <stdexcept>
#include <chrono>
#include <thread>

#include <sys/socket.h>
#include <arpa/inet.h>



using namespace std;


int main(int argc,char * argv[])
{

	int socket_fd;
	struct sockaddr_in server;
	
	char data[32];
	
	socket_fd = socket(AF_INET , SOCK_STREAM , 0);
	
	if(socket_fd==-1)
	{
		throw runtime_error("Cannot create socket");
	}
	
	cout<<"Connecting...";
	
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(7070);
	
	if(connect(socket_fd ,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		throw runtime_error("Failed to connect to server");
	}
	
	cout<<" done"<<endl;
	
	for(int n=0;n<32;n++)
	{
		data[n]=n<<2;
	}
	
	while(true)
	{
	
		if( send(socket_fd , data , 32 , 0) < 0)
		{
			throw runtime_error("Failed to send message");
		}
	
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	return 0;
}
