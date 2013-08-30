#ifndef INTERPRETARMSG_H
#define INTERPRETARMSG_H
#include <unordered_map>
#include <string>

typedef unordered_map<string,string> map_atributes;

void initEspecies();
string interpretarMsg(string, map_atributes);

#endif
