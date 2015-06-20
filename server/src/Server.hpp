

#ifndef _PETERQUAD_SERVER_
#define _PETERQUAD_SERVER_

#include <sys/socket.h>
#include <arpa/inet.h>

namespace com
{
	namespace toxiclabs
	{
		namespace peterquad
		{
			class Server
			{
				public:
				
				/*! request for exit */
				bool quit_request;
				/*! client connection status */
				bool connected;
				
				/*! tcp port */
				static int port;
				
				Server();
				~Server();
				
				/*!
				 Network management thread
				*/
				void NetworkThread();
				
				/*!
				 Pilot main thread
				*/
				void Run();
			};
		}
	}
}

#endif
