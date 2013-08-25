#include "include/msgParse.h"

message_ptr messageParse(string msg){
	Message* msgStruct = new Message;

	/* Parse the reason */
	vector<string> strs;
	boost::split(strs,msg,boost::is_any_of("?"));
	msgStruct->reason = strs[0];

	/* Parse the rest, puting the attrs and vals in the hash*/
	vector<string> strs2;
	boost::split(strs2,strs[1],boost::is_any_of("&"));

	BOOST_FOREACH(string attrAndVal,strs2){
		vector<string> strs3;
		boost::split(strs3,attrAndVal,boost::is_any_of("="));
		msgStruct->atributes[strs3[0]] = strs3[1];
	}
	return message_ptr(msgStruct);
}
