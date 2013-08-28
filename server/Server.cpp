#include "include/Server.h"

#define buffsize 1000
#define FIFO_NAME "parent"

/* Read characters from the pipe and return it. */
string read_from_pipe (){
   int fd = open(FIFO_NAME, O_RDONLY);
   if(fd < 0)
      perror("child - abertura");

   int num;
   char buf[buffsize];
      num = read(fd, buf, sizeof(buf));
      if( num < 0)
         perror("parent - leitura");
      else
      {
         buf[num] = '\0';
         printf("%d - leu %d bytes: \"%s\"\n",getpid(), num, buf);
      }

   return string(buf);
}


/* Write msg text to the pipe. */
void write_to_pipe (string msg){

   int fd = open(FIFO_NAME, O_RDWR);
   if(fd < 0)
      perror("child - abertura");

   int num = write(fd, msg.c_str(), strlen(msg.c_str()));
   if( num < 0)
      perror("child - escrita");
   else
      printf("%d - escreveu %d bytes em %s\n",getpid(), num,FIFO_NAME);

}

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
   write_to_pipe(data);

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
      string data = read_from_pipe();
      /* Execute the data */
      execMsg(data);

      shm->mutexSend.post();
      shm->mutexAnswer.wait();
      shm->mutexThread.unlock();
   }
}

void Server::execMsg(string msg){
   cout << "msg: " << msg << endl;
   strcat(shm->message,msg.c_str());
}

void Server::initServer(int port){
   createSharedMemory();
   int id = fork();

   struct stat st;
   if (stat(FIFO_NAME, &st) != 0)
      mkfifo(FIFO_NAME, 0666);

   if(id > 0){
      initSocket(port);
      wait();
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
