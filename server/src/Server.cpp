

#include "Server.hpp"

#include <iostream>
#include <stdexcept>
#include <thread>
#include <chrono>



using namespace std;
using namespace com::toxiclabs::peterquad;


int Server::port=7070;

Server::Server()
{
	quit_request=false;
	connected=false;
}

Server::~Server()
{
	cout<<"* bye"<<endl;
}

void Server::NetworkThread()
{
	int socket_fd, client_fd;
	socklen_t cli_len;
	struct sockaddr_in server, client;
	char data[512];
	int data_len;
	
	socket_fd = socket(AF_INET , SOCK_STREAM , 0);
	
	if(socket_fd==-1)throw runtime_error("Could not create socket");
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(Server::port);
	
	if( bind(socket_fd,(struct sockaddr *)&server , sizeof(server)) < 0)
		throw runtime_error("Bind failed");
		
	listen(socket_fd , 1);
	
	cli_len=sizeof(client);
	
	client_fd=accept(socket_fd,(struct sockaddr *) &client,&cli_len);
	
	if(client_fd<0)
	{
		throw runtime_error("Accept failed");
	}
	
	connected=true;
	
	while(!quit_request)
	{
		data_len=recv(client_fd,data,32,0);
		
		if(data_len<=0)
			throw runtime_error("Connection lost");
	}
	
	close(socket_fd);
	
	connected=false;
}

void Server::Run()
{
	thread tnetwork;
	
	cout<<"* spawning network thread"<<endl;
	tnetwork = thread(&Server::NetworkThread,this);
	
	cout<<"* server ready"<<endl;
	
	while(!quit_request)
	{
		
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	
	cout<<"* closing server"<<endl;
	
	tnetwork.join();
	
	
}
