#include "include/Server.h"

void* Server::getMemoryAddr(){
	return memoryRegion->get_address();
}

void Server::createMessageQueue(){
	shm = new (getMemoryAddr()) shared_messages;
}

void Server::createSharedMemory(){
	try{
		memoryRegion = new mapped_region(anonymous_shared_memory(MEMORY_SIZE));
		memset(memoryRegion->get_address(),0,memoryRegion->get_size());
		createMessageQueue();
	} catch (exception& e){
		cerr << "Exception: sharedMemory: " << e.what() << endl;
	}
}

void Server::manipulateData(string data, socket_ptr sock){
	shm->mutexThread.lock();
	strcpy(shm->message,data.c_str());
	shm->mutexProcess.post();
	shm->mutexSend.wait();
	boost::system::error_code error;
	boost::asio::write(*sock, boost::asio::buffer(string(shm->message)), error);
	cout << "Message answered!" << endl;
	shm->mutexAnswer.post();
}

void Server::consumeData(){
	while(true){
		shm->mutexProcess.wait();
		strcat(shm->message," ANSWERED QUESTION!");
		shm->mutexSend.post();
		shm->mutexAnswer.wait();
		shm->mutexThread.unlock();	
	}
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
		consumeData();
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
