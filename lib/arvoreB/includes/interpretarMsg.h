#ifndef INTERPRETARMSG_H
#define INTERPRETARMSG_H
#include <unordered_map>

typedef unordered_map<string,string> map_atributes;

void initEspecies();
void interpretarMsg(string, map_atributes);

#endif
