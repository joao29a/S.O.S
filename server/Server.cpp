#include "include/Server.h"

//!TODO
/*
 * Aqui tem que ter o sistema de comunicação entre os dois
 * forks!
 */

/* TODO depois de receber uma mensagem tem que colocar na fila
 * para que o outro fork fique consumindo.*/
 
void Server::listenSocket(socket_ptr sock){}

void Server::execMsg(string msg){
   /*!TODO
    * Executa a mensagem e envia o resultado.
    */
}

void Server::initServer(int port){
   int id = fork();
   if(id == 0){
      initSocket(port);
   }else{
      /* TODO segundo fork tem que ficar consumindo a fila! */
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
