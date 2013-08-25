#ifndef MESSAGEPARSE_H
#define MESSAGEPARSE_H

#include "boost/shared_ptr.hpp"
#include <unordered_map>
#include <iostream>
#include <unordered_map>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;

struct Message{
	string reason;
	unordered_map<string,string> atributes;
};

typedef boost::shared_ptr<Message> message_ptr;

/* msg will be something like: 'reason?attr1=val1&attr2=val2'*/
message_ptr messageParse(string);

#endif
