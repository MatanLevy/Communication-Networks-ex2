$(TARGET)
TARGET := client
CFLAGS := -std=c++11 -Wall -g -pthread
O_FILES:= Clientmain.o AuxiliaryClient.o Auxiliary.o


$(TARGET): $(O_FILES)
	g++ -o $(TARGET) $(O_FILES) -std=c++11 -pthread -O2 

Clientmain.o: Clientmain.cpp Auxiliary.h AuxiliaryClient.h
	g++ -c $(CFLAGS) $*.cpp 
	
AuxiliaryClient.o: AuxiliaryClient.cpp AuxiliaryClient.h
	g++ -c $(CFLAGS) $*.cpp

Auxiliary.o: Auxiliary.cpp Auxiliary.h
	g++ -c $(CFLAGS) $*.cpp 

clean:
	-rm $(TARGET) $(O_FILES)
