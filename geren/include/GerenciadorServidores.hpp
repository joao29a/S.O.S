#include <boost/thread/thread.hpp>
#include <iostream>
#include "boost/shared_ptr.hpp"
#include "lib/msgParse.hpp"

using namespace std;

class GerenciadorServidores{
   private:
      void clientListening();
      void serverManaging();
};
