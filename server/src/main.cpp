

#include "Server.hpp"
#include <iostream>


using namespace std;
using namespace com::toxiclabs::peterquad;


int main(int argc,char * argv[])
{

	cout<<"*** peterquad mk-II  ***"<<endl;
	Server server;
	
	server.Run();
	
	return 0;
}
