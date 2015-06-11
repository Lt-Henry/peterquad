


#include <iostream>


using namespace std;

int main(int argc,char * argv[])
{
	int socket_desc;
	struct sockaddr_in server;
	
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	
	if(socket_desc==-1)throw runtime_error("Could not create socket");
	
	cout<<"Socket created"<<endl;
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(7070);
	
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
		throw runtime_error("Bind failed");
		
	cout<<"Bind done"<<endl;
	
	listen(socket_desc , 1);
	
	cout<<"Wait for client..."<<endl;
	
	return 0;
}
