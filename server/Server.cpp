#include "include/Server.h"

void Server::createSharedMemory(){
	try{
		memoryRegion = new mapped_region(anonymous_shared_memory(MEMORY_SIZE));
		memset(memoryRegion->get_address(),0,memoryRegion->get_size());
	} catch (exception& e){
		cerr << "Exception: sharedMemory: " << e.what() << endl;
	}
}

void Server::manipulateData(string data, socket_ptr sock){
	messageQueue.push_back(data);
}

void Server::execMsg(string msg){
}

void Server::initServer(int port){
	createSharedMemory();
	int id = fork();
	if(id > 0){
		initSocket(port);
	}
	else if (id == 0){
	}
}

int main(int argc, char *argv[]){
	int port = 0;
	if(argc > 1){
		port = atoi(argv[1]);
	}
	Server server;
	server.initServer(port);
	return 0;
}
