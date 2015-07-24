

#include "Client.hpp"

#include <iostream>

using namespace std;
using namespace com::toxiclabs::peterquad;

Client::Client(int argc,char * argv[])
{
	app = Gtk::Application::create(argc,argv,"com.toxiclabs.peterquad");
	winMain = new Gtk::Window();
}

Client::~Client()
{

}

void Client::Run()
{
	app->run(*winMain);
}

void Client::Quit()
{

}
