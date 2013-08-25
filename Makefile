CPP=g++
LIBBOOST=-lboost_system -lboost_thread -lboost_unit_test_framework -I/usr/include/ -lpthread
DIRMANAGEMENT=management/
DIRSERVICE=service/
DIRSERVER=server/
DIRTEST=tests/
DIRLIB=lib/
EXESERVICE=Service
EXESERVER=Server
EXETEST=test$(EXESERVICE)
STD=-std=c++11

all: ServiceManager makeServer makeTest

ServiceManager:
	 ${CPP} -I./ -I$(DIRSERVICE) -I$(DIRLIB) -I$(DIRMANAGEMENT)\
		 $(DIRSERVICE)*.cpp $(DIRMANAGEMENT)*.cpp $(DIRLIB)*.cpp -o $(EXESERVICE) ${LIBBOOST} $(STD)

makeServer:
	 ${CPP} -I./ -I$(DIRSERVER) $(INCMANAGEMENT) $(DIRSERVER)*.cpp $(MANAGEMENT) -o $(EXESERVER) ${LIBBOOST} $(STD)

makeTest:
	 ${CPP} $(DIRTEST)gerenTests.cpp -o $(EXETEST) ${LIBBOOST} -I./ $(STD)

clear:
	 rm $(EXESERVICE) -f
	 rm $(EXETEST) -f
	 rm $(EXESERVICE) -f
