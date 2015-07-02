

#include "Server.hpp"
#include <iostream>
#include <signal.h>


using namespace std;
using namespace com::toxiclabs::peterquad;

Server server;

void handler(int s)
{
	server.Quit();
}


int main(int argc,char * argv[])
{
	signal (SIGINT,handler);

	cout<<"*** peterquad mk-II  ***"<<endl;
	
	
	server.Run();
	
	return 0;
}
