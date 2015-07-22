

#include <iostream>
#include <stdexcept>
#include <chrono>
#include <thread>

#include <sys/socket.h>
#include <arpa/inet.h>

#include <signal.h>

using namespace std;

bool quit_request=false;

void handler(int s)
{
	quit_request=true;
}

int main(int argc,char * argv[])
{

	int socket_fd;
	struct sockaddr_in server;
	
	char data[32];
	
	signal (SIGINT,handler);
	
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
	
	data[0]=0;//status request
	
	while(!quit_request)
	{
	
		if( send(socket_fd , data , 1 , 0) < 0)
		{
			throw runtime_error("Failed to send message");
		}
	
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	
	data[0]=2; //quit request
	send(socket_fd , data , 1 , 0);
	
	return 0;
}
