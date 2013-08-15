#include <boost/thread/thread.hpp>
#include <iostream>
#include "boost/shared_ptr.hpp"
#include "lib/msgParse.hpp"
#include <cstdlib>
#include <iostream>
#include <thread>
#include <utility>
#include <boost/asio.hpp>
#include <boost/ref.hpp>

using boost::asio::ip::tcp;
using namespace std;

class GerenciadorServidores{
   private:
      void clientListening(tcp::socket&);
      void serverManaging();
      void clientManaging(boost::asio::io_service& io_service, unsigned short port);
   public:
      void startService(int port);
};
