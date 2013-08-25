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
EXELIB=msgParse
EXEMANAGEMENT=Management
STD=-std=c++11

all: ServiceManager makeServer makeTest

$(EXELIB).o:
	$(CPP) -c $(DIRLIB)*.cpp -o $(EXELIB).o -I$(DIRLIB) $(STD)

$(EXEMANAGEMENT).o:
	$(CPP) -c $(DIRMANAGEMENT)*.cpp -o $(EXEMANAGEMENT).o -I$(DIRLIB) -I$(DIRMANAGEMENT) $(STD)

ServiceManager: $(EXELIB).o $(EXEMANAGEMENT).o
	 ${CPP} -I./ -I$(DIRSERVICE) $(DIRSERVICE)*.cpp -I$(DIRLIB) -I$(DIRMANAGEMENT)\
		 $(EXEMANAGEMENT).o $(EXELIB).o -o $(EXESERVICE) ${LIBBOOST} $(STD)

makeServer: $(EXELIB).o $(EXEMANAGEMENT).o
	 ${CPP} -I./ -I$(DIRSERVER) $(DIRSERVER)*.cpp -I$(DIRLIB) -I$(DIRMANAGEMENT)\
		 $(EXELIB).o $(EXEMANAGEMENT).o -o $(EXESERVER) ${LIBBOOST} $(STD)

makeTest:
	 ${CPP} -I$(DIRLIB) $(DIRTEST)gerenTests.cpp $(EXELIB).o -o $(EXETEST) ${LIBBOOST} -I./ $(STD)

clear:
	 rm $(EXESERVICE) -f
	 rm $(EXETEST) -f
	 rm $(EXESERVER) -f
	 rm *.o -f
