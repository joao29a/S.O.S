#ifndef SERVICEMANAGER_H
#define SERVICEMANAGER_H

#include "include/Management.h"

class ServiceManager: public Management{
	private:
		string sendServer(string,int);
		string askToServers(string);

	protected:
		void manipulateData(string,socket_ptr);
};

#endif
