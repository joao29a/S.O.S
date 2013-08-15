CPP=clang++
LIBBOOST=-lboost_system -lboost_thread -lboost_unit_test_framework -I/usr/include/ -lpthread
gerenInclude=-I./geren/

all: gerenServidor makeTest

gerenServidor:
	 ${CPP} -I./ -Igeren/ geren/GerenciadorServidores.cpp -o Geren ${LIBBOOST} -std=c++11

makeTest:
	${CPP} tests/gerenTests.cpp -o testGeren ${LIBBOOST} -I./ -std=c++11

clear:
	 rm Geren
	 rm testGeren


