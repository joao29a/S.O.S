#ifndef SERVER_H
#define SERVER_H

#include "include/Management.h"
#include <list>
#include <boost/interprocess/anonymous_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>

#define MEMORY_SIZE 10000

using namespace boost::interprocess;

class Server: public Management{
	private:
		mapped_region* memoryRegion;
		void createSharedMemory();

	protected:
		list<string> messageQueue;
		void manipulateData(string,socket_ptr);
		void execMsg(string);
	public:
		void initServer(int);
};

#endif
