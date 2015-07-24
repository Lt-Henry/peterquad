#ifndef _PETERQUAD_CLIENT_
#define _PETERQUAD_CLIENT_

#include <gtkmm.h>
#include <glibmm.h>
#include <giomm.h>

namespace com
{
	namespace toxiclabs
	{
		namespace peterquad
		{
			class Client
			{
			
				private:
				
				Glib::RefPtr<Gtk::Application> app;
				Gtk::Window * winMain;
				
				public:
				
				Client(int argc,char * argv []);
				~Client();
				
				void Run();
				void Quit();
			};
		}
	}
}

#endif
