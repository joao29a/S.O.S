#include "include/ServiceManager.h"

/* For each connection wait for a msg. When it receve a mensage
 * call askToServer and write the result for the client */
void ServiceManager::manipulateData(string data, socket_ptr sock){
	string reply = askToServers(data) + "\n";
	boost::asio::write(*sock, boost::asio::buffer(
				reply, reply.size()));
}

/* Send msg to server and return the result msg */
string ServiceManager::sendServer(string msg,int port){
	try{
		boost::asio::io_service io_service;

		tcp::socket s(io_service);
		tcp::resolver resolver(io_service);
		boost::asio::connect(s, resolver.resolve({"127.0.0.1",
					to_string(port).c_str()}));

		size_t request_length = std::strlen(msg.c_str());
		boost::asio::write(s, boost::asio::buffer(msg.c_str(),
					request_length));

		char reply[10000];
		size_t reply_length = boost::asio::read(s,
				boost::asio::buffer(reply, request_length));

		return string(reply);
	}catch (std::exception& e){
		std::cerr << "Exception: askToServers: " << e.what() << "\n";
	}
	return string("null");
}

/* Ask for all server if they have some thing asked by the msg
 * and return the result from the first server to have*/
string ServiceManager::askToServers(string msg){

	int size = 3;
	int serverChecked[3] = {1,1,1};
	int serverId;
	for (serverId = 0; serverId < size; serverId++){
		if(serverChecked[serverId] == 1){
			string res = sendServer(msg,8870+serverId);
			if(res != "null"){
				return res;
			}
			serverChecked[serverId] = 0;
		}

	}
	return string("null");
}

int main(){
	cout << "Initializing service on port 8888" << endl;
	ServiceManager service;
	service.initSocket(8888);
	return 0;
}