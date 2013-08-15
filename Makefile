CPP=clang++
LIBBOOST=-lboost_system -lboost_thread -lboost_unit_test_framework -I/usr/include/
gerenInclude=-I./geren/

all: gerenServidor

gerenServidor:
	 ${CPP} -Igeren/ geren/GerenciadorServidores.cpp -o Geren ${LIBBOOST} --std=c++11

clear:
	 rm Geren


