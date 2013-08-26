#include "include/Management.h"

/* For each client to conect create a Thread to do what was ask by the
 * client */

void Management::listenSocket(socket_ptr sock){
	try{
		while(true){
			string data = getData(sock);
			manipulateData(data,sock);
		}
	}catch (std::exception& e){
		std::cerr << "Exception: listenSocket: " << e.what() << "\n";
	}
}

string Management::getData(socket_ptr sock){
	char data[10000];

	boost::system::error_code error;
	size_t length = sock->read_some(boost::asio::buffer(data), error);

	if (error == boost::asio::error::eof)
		throw runtime_error("Empty string");
	else if (error)
		throw boost::system::system_error(error);

	cout << "Question: " << data << endl;

	return string(data);
}

void Management::connect(boost::asio::io_service& io_service,
		unsigned short port){

	tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
	while(true){
		socket_ptr sock(new tcp::socket(io_service));
		cout << "Waiting connection..." << endl;
		a.accept(*sock);
		std::thread(boost::bind(&Management::listenSocket,
					this,sock)).detach();
		cout << "Connection initialized!" << endl;
	}
}

void Management::initSocket(int port){
	try{
		boost::asio::io_service io_service;
		connect(io_service, port);
	}catch (std::exception& e){
		std::cerr << "Exception: initSocket: " << e.what() << "\n";
	}
}
