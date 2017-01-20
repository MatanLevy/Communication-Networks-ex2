$(TARGET)
TARGET := server
CFLAGS := -std=c++11 -Wall -pthread -g
O_FILES:= main.o AuxiliaryServer.o Auxiliary.o Email.o User.o Server.o


$(TARGET): $(O_FILES)
	g++ -o $(TARGET) $(O_FILES) -std=c++11 -pthread -O2 

main.o: main.cpp Auxiliary.h AuxiliaryServer.h
	g++ -c $(CFLAGS) $*.cpp 
	
AuxiliaryServer.o: AuxiliaryServer.cpp AuxiliaryServer.h
	g++ -c $(CFLAGS) $*.cpp

Auxiliary.o: Auxiliary.cpp Auxiliary.h
	g++ -c $(CFLAGS) $*.cpp 

Email.o: Email.cpp Email.h
	g++ -c $(CFLAGS) $*.cpp 

User.o: User.cpp User.h
	g++ -c $(CFLAGS) $*.cpp 

Server.o: Server.cpp Server.h
	g++ -c $(CFLAGS) $*.cpp 


clean:
	-rm $(TARGET) $(O_FILES)
