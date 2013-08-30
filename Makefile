CPP=g++
LIBBOOST=-lrt -lboost_system -lboost_thread -lboost_unit_test_framework -I/usr/include/ -lpthread
DIRMANAGEMENT=management/
DIRSERVICE=service/
DIRSERVER=server/
DIRTEST=tests/
DIRLIB=lib/
DIRTREE=$(DIRLIB)arvoreB/
SRC_SERVER=$(wildcard $(DIRSERVER)*.cpp)
SRC_SERVICE=$(wildcard $(DIRSERVICE)*.cpp)
SRC_LIB_MANAG=$(wildcard $(DIRMANAGEMENT)*.cpp $(DIRLIB)*.cpp)
SRC_LIB_TREE=$(wildcard $(DIRTREE)*.cpp)
SRC_TEST=$(DIRTEST)gerenTests.cpp
OBJ_SERVER=$(SRC_SERVER:.cpp=.o)
OBJ_SERVICE=$(SRC_SERVICE:.cpp=.o)
OBJ_LIB_MANAG=$(SRC_LIB_MANAG:.cpp=.o)
OBJ_LIB_TREE=$(SRC_LIB_TREE:.cpp=.o)
OBJ_TEST=$(SRC_TEST:.cpp=.o)
INCLUDE=-g -O0 -I$(DIRMANAGEMENT) -I$(DIRSERVICE) -I$(DIRSERVER) -I$(DIRLIB) -I$(DIRTREE) -std=c++11

all: ServiceManager Server Test

.cpp.o:
	$(CPP) -c $< $(INCLUDE) -o $@

Server: $(OBJ_LIB_MANAG) $(OBJ_LIB_TREE) $(OBJ_SERVER) 
	 $(CPP) $(INCLUDE) $^ -o $@ $(LIBBOOST)

ServiceManager: $(OBJ_LIB_MANAG) $(OBJ_SERVICE)
	 $(CPP) $(INCLUDE) $^ -o $@ $(LIBBOOST)

Test: $(OBJ_LIB_MANAG) $(OBJ_TEST)
	 $(CPP) $(INCLUDE) $^ -o $@ $(LIBBOOST)

clear:
	 rm $(OBJ_SERVER) $(OBJ_SERVICE) $(OBJ_LIB_MANAG) $(OBJ_TEST) $(OBJ_LIB_TREE) -f
	 rm Server -f
	 rm ServiceManager -f
	 rm Test -f
