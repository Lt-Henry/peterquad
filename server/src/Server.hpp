

#ifndef _PETERQUAD_SERVER_
#define _PETERQUAD_SERVER_

#include <sys/socket.h>
#include <arpa/inet.h>

#include <vector>
#include <mutex>

#define CMD_STATUS_REQUEST	0
#define CMD_STATUS	1
#define CMD_QUIT_REQUEST	2

namespace com
{
	namespace toxiclabs
	{
		namespace peterquad
		{
		
			struct Command
			{
				union
				{
					char data[32];
					struct
					{
						char type;
						
					};
				};
			};
			
			class Server
			{
				public:
				
				std::mutex cmdMutex;
				std::vector<Command> incomingCommands;
				
				/*! request for exit */
				bool quit_request;
				/*! client connection status */
				bool connected;
				
				/*! tcp port */
				static int port;
				
				Server();
				~Server();
				
				void ProcessCommand(char * data,int len);
				
				/*!
				 Network management thread
				*/
				void NetworkThread();
				
				/*!
				 Pilot main thread
				*/
				void Run();
				
				/*!
				 Quit
				*/
				void Quit();
			};
		}
	}
}

#endif
