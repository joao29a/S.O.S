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

        /* Send data from client to fork by PIPE */
        char* msg = (char*) malloc(data.size());
        strcpy(msg,data.c_str());
        write(pipefd[1], msg, strlen(msg));

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

                /* Receve data from parent by PIPE */
                char buf;
                string data("");
                while (read(pipefd[0], &buf, 1) > 0){
                   data.push_back(buf);
                }

                /* Execute the data */
		execMsg(data);

		shm->mutexSend.post();
		shm->mutexAnswer.wait();
		shm->mutexThread.unlock();
	}
}

void Server::execMsg(string msg){
   strcat(shm->message,"Ok.");
}

void Server::initServer(int port){
	createSharedMemory();
	int id = fork();
        pipe(pipefd);
	if(id > 0){
		initSocket(port);
	}
	else if (id == 0){
                fcntl(pipefd[0], F_SETFL, O_NONBLOCK);
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
