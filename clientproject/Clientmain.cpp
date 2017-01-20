#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <thread>
#include "Auxiliary.h"
#include "AuxiliaryClient.h"
using namespace std;

#define STDIN 0

char message1[SIZE];

void waitForMessage(int socket) {
	recvAllData(socket, message1);
	cout << message1 << endl;
}

int main(int argc, char** argv) {
	fd_set readfds;
	string sendmsg;
	int portNumber = PORT_NUMBER;
	string host = LOCAL_HOST;
	if (argc > 1) {
		host = argv[1];
		if (argc == 3) {
			portNumber = atoi(argv[2]);
		}
	}
	int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket < 0)
		exit(1);
	struct sockaddr_in myaddr;
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(portNumber);
	myaddr.sin_addr.s_addr = inet_addr(host.c_str());
	if (connect(clientSocket, (struct sockaddr*) &myaddr,
			sizeof(struct sockaddr)) < 0) {
		cout << strerror(errno) << endl;
		exit(1);
	}
	int fdmax = std::max(STDIN, clientSocket);
	recvAllData(clientSocket, message1);
	cout << message1 << endl;
	loginSessionClient(clientSocket);
	while (1) {
		FD_ZERO(&readfds);
		FD_SET(STDIN,&readfds);
		FD_SET(clientSocket,&readfds);
		select(fdmax + 1, &readfds, NULL, NULL, NULL);
		if (FD_ISSET(STDIN,&readfds)) {
			getline(cin, sendmsg);
			handleClientCommand(clientSocket, sendmsg);
		}
		if (FD_ISSET(clientSocket,&readfds)) {
			waitForMessage(clientSocket);
		}
	}
	//t1.join();
}
