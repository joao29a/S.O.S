#include <boost/thread/thread.hpp>
#include <iostream>
#include <unordered_map>
#include "boost/shared_ptr.hpp"


using namespace std;

struct Mensage{
   string reason;
   unordered_map<string,string> atributes;
};


class GerenciadorServidores{
   private:
      shared_ptr<Mensage> mensageParse(string);
      void clientListening();
      void serverManaging();
};
