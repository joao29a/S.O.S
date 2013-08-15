#include "boost/shared_ptr.hpp"
#include <unordered_map>
#include <iostream>
#include <unordered_map>

using namespace std;

struct Message{
      string reason;
      unordered_map<string,string> atributes;
};

shared_ptr<Message> messageParse(string);

shared_ptr<Message> messageParse(string msg){
     shared_ptr<Message> msg_ptr(new Message);
     return msg_ptr;
}
