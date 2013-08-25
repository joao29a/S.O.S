#ifndef SERVER_H
#define SERVER_H

#include "include/Management.h"
#include <list>

class Server: public Management{
	protected:
		list<string> messageQueue;
		void listenSocket(socket_ptr);
		void execMsg(string);
	public:
		void initServer(int);
};

#endif
