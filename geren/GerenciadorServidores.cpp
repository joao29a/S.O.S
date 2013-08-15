#include "include/GerenciadorServidores.hpp"

void GerenciadorServidores::clientListening(tcp::socket& sock){
   try{
      while(true){
         char data[10000];

         boost::system::error_code error;
         size_t length = sock.read_some(boost::asio::buffer(data), error);

         if (error == boost::asio::error::eof)
            break;
         else if (error)
            throw boost::system::system_error(error);

         shared_ptr<Message> msg_ptr = messageParse(string(data));
         //TODO!
      }
   }catch (std::exception& e){
      std::cerr << "Exception in thread: " << e.what() << "\n";
   }
}

void GerenciadorServidores::clientManaging(boost::asio::io_service& io_service
      ,unsigned short port){

   tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
   while(true){
      tcp::socket sock(io_service);
      cout << "Esperando conexão..." << endl;
      a.accept(sock);
      std::thread(boost::bind(&GerenciadorServidores::clientListening,
                  this,boost::ref(sock))).detach();
      cout << "Conexão iniciada!" << endl;
   }

}

void GerenciadorServidores::serverManaging(){

}

void GerenciadorServidores::startService(int port){
   try{
      boost::asio::io_service io_service;
      clientManaging(io_service, port);
   }catch (std::exception& e){
      std::cerr << "Exception: " << e.what() << "\n";
   }
}

int main(){
   cout << "Iniciando servidor na porta 8888" << endl;
   GerenciadorServidores geren;
   geren.startService(8888);
   return 0;
}
