#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include <boost/thread/thread.hpp>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <utility>
#include <boost/asio.hpp>
#include <boost/ref.hpp>
#include "include/msgParse.h"

using boost::asio::ip::tcp;
using namespace std;
typedef boost::shared_ptr<tcp::socket> socket_ptr;
typedef boost::shared_ptr<Message> message_ptr;

class Management{
	protected:
		virtual void listenSocket(socket_ptr){}
		string getData(socket_ptr);
		void connect(boost::asio::io_service&, unsigned short);

	public:
		void initSocket(int);
};

#endif
