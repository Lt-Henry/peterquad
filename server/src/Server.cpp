

#include "Server.hpp"

#include <iostream>
#include <stdexcept>
#include <thread>
#include <chrono>

#include <fcntl.h>
#include <unistd.h>


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
	char data[32];
	int data_len;
	int watchdog=0;
	
	try
	{
		cout<<"stage 1"<<endl;
		socket_fd = socket(AF_INET , SOCK_STREAM , 0);
		if(socket_fd==-1)throw runtime_error("Could not create socket");

		server.sin_family = AF_INET;
		server.sin_addr.s_addr = INADDR_ANY;
		server.sin_port = htons(Server::port);

		cout<<"stage 2"<<endl;
		if(bind(socket_fd,(struct sockaddr *)&server,sizeof(server)) < 0)
			throw runtime_error("Bind failed");

		cout<<"stage 3"<<endl;
		listen(socket_fd , 1);

		cli_len=sizeof(client);

		fcntl(socket_fd, F_SETFL, fcntl(socket_fd, F_GETFL, 0) | O_NONBLOCK);
		cout<<"stage 4"<<endl;
	}
	catch(runtime_error & e)
	{
		close(socket_fd);
		cerr<<e.what()<<endl;
		cerr<<"errno:"<<errno<<endl;
		cerr<<"Failed to create a socket"<<endl;
		return;
	}

	while(!quit_request)
	{
		try
		{
			
			//wait-loop for an incoming connection
			while(true)
			{
				client_fd=accept(socket_fd,(struct sockaddr *) &client,&cli_len);


				if(client_fd>0)
					break;
				else
				{
					//non blocking accept, wait 100ms and try again
					if(errno==EWOULDBLOCK)
					{
						std::this_thread::sleep_for(std::chrono::milliseconds(100));
						cout<<"waiting..."<<endl;
					}
					else
						throw runtime_error("Accept failed");
				}

				if(quit_request)
					throw runtime_error("Quit requested");
			}


			fcntl(client_fd, F_SETFL, fcntl(client_fd, F_GETFL, 0) | O_NONBLOCK);
			connected=true;

			while(!quit_request)
			{
				data_len=recv(client_fd,data,32,0);
				if(data_len>0)
				{
					watchdog=0;
					ProcessCommand(data,data_len);
				}
				else
				{
					if(errno==EWOULDBLOCK)
					{
						watchdog+=10;
						std::this_thread::sleep_for(std::chrono::milliseconds(10));
					}
					else
						throw runtime_error("Connection lost");
				}
				
				if(watchdog>10000)
				{
					throw runtime_error("Connection timeout");
				}
					
			}

			connected=false;

		}
		catch(runtime_error & e)
		{
			connected=false;
			close(client_fd);
			cerr<<e.what()<<endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
	}


	close(socket_fd);
}


void Server::ProcessCommand(char * data,int len)
{
	Command c;
	
	for(int n=0;n<len;n++)
	{
		c.data[n]=data[n];
	}
	
	cmdMutex.lock();
	if(incomingCommands.size()<1024)
	{
		incomingCommands.push_back(c);
	}
	else
	{
		cerr<<"Command stack is full!"<<endl;
	}
	cmdMutex.unlock();
}



void Server::Run()
{
	thread tnetwork;
	bool incmd;
	Command cmd;

	cout<<"* spawning network threads"<<endl;
	tnetwork = thread(&Server::NetworkThread,this);

	cout<<"* server ready"<<endl;

	while(!quit_request)
	{
		incmd=false;
		cmdMutex.lock();
		if(!incomingCommands.empty())
		{
			incmd=true;
			cmd=incomingCommands.back();
			incomingCommands.pop_back();
		}
		cmdMutex.unlock();
		
		if(incmd)
		{
			switch(cmd.type)
			{
				case CMD_STATUS_REQUEST:
					cout<<"status command"<<endl;
				break;
				
				case CMD_QUIT_REQUEST:
					Quit();
				break;
			}
		}
		
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	cout<<"* closing server"<<endl;

	tnetwork.join();


}

void Server::Quit()
{
	quit_request=true;
}
