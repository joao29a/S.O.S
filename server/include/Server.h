#ifndef SERVER_H
#define SERVER_H

#include "include/Management.h"
#include "includes/interpretarMsg.h"
#include <boost/interprocess/anonymous_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <mutex>
#include <unistd.h>
#include <fcntl.h>

#define MEMORY_SIZE 240000
using namespace boost::interprocess;

struct shared_messages{
	shared_messages() : mutexProcess(0), mutexAnswer(0), mutexSend(0){}
	interprocess_semaphore mutexProcess, mutexAnswer, mutexSend;
	mutex mutexThread;
};


class Server: public Management{
	private:
		mapped_region* memoryRegion;
		shared_messages* shm;
		void* getMemoryAddr();
		void createMessageQueue();
		void createSharedMemory();
		void consumeData();

	protected:
		void manipulateData(string,socket_ptr);
		void execMsg(string);

	public:
		void initServer(int);
};

#endif
