


#include <iostream>
#include <stdexcept>

#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;

int main(int argc,char * argv[])
{
	int socket_fd, client_fd;
	socklen_t cli_len;
	struct sockaddr_in server, client;
	char data[32];
	int data_len;
	
	socket_fd = socket(AF_INET , SOCK_STREAM , 0);
	
	if(socket_fd==-1)throw runtime_error("Could not create socket");
	
	cout<<"Socket created"<<endl;
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(7070);
	
	if( bind(socket_fd,(struct sockaddr *)&server , sizeof(server)) < 0)
		throw runtime_error("Bind failed");
		
	cout<<"Bind done"<<endl;
	
	listen(socket_fd , 1);
	
	cout<<"Wait for client..."<<endl;
	
	cli_len=sizeof(client);
	
	client_fd=accept(socket_fd,(struct sockaddr *) &client,&cli_len);
	
	if(client_fd<0)
	{
		throw runtime_error("Accept failed");
	}
	
	
	while(true)
	{
		data_len=recv(client_fd,data,32,0);
		
		if(data_len<=0)
			throw runtime_error("Connection lost");
		
		cout<<" Data: "<<endl;
		for(int n=0;n<data_len;n++)
		{
			cout<<hex<<(int)data[n]<<endl;
		}
		cout<<endl;
	}
	
	return 0;
}
