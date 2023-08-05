GPP=g++
SFLAGS=-ljsoncpp -pthread
SERVEREXE=server
SERVER=./server.cpp
CLIENTEXE=client
CLIENT=./client.cpp
TEST=./testcases.cpp
TESTEXE=test

install:
	sudo apt-get install libjsoncpp-dev

runserver:
	$(GPP) $(SERVER) $(SFLAGS) -o $(SERVEREXE) && ./$(SERVEREXE)

runclient:
	$(GPP) $(CLIENT)  -o $(CLIENTEXE) && ./$(CLIENTEXE)

tests:
	$(GPP) $(TEST)  -o $(TESTEXE) && ./$(TESTEXE)

clean:
	rm ./$(CLIENTEXE) ./$(SERVEREXE) ./$(TESTEXE)