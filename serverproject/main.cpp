#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <thread>
#include "Auxiliary.h"
#include "AuxiliaryServer.h"
using namespace std;

int handleClient(int client,Server& server,char* client_message) {
	if (client <= 0) {
				cout  << strerror(errno) << endl;
				return 1;
			}
			else {
				sendAllData(client,WELCOME_MESSAGE);
				 }
			string user;
			if (!CheckUser(client,client_message,server,user)) {
				sendAllData(client,WRONG_LOGIN);
				return 1;
			}
			else {
				server.addSocketIdOfUser(client,user);
				sendAllData(client,CONNECTED_AUTHORIZE);
			}

			while(true) {
				recvAllData(client,client_message);
				if (string(client_message) == QUIT_COMMAND) {
					server.removeSocketIdOfUser(user);
					break;
				}
				handleCommand(client,client_message,server,user);
				}

			return 0;
}

int main(int argc, const char** argv) {
	int portNumber = PORT_NUMBER;
	char client_message[SIZE];
	socklen_t sin_size = sizeof(struct sockaddr_in);
	struct sockaddr_in client_addr;
	int client;
	int serverSocket;

	if (argc > 3 || argc < 2) {
		cout << BAD_ARGUMENTS << endl;
		return 1;
	}
	if (argc == 3) {
		portNumber = atoi(argv[2]);
	}
	Server server(portNumber);
	server.UpdateUsers(argv[1]);
	vector<thread> threadList;

	connectToClient(serverSocket,portNumber);
    while (true) {
		client = accept(serverSocket,(struct sockaddr*)&client_addr,&sin_size);
		threadList.push_back(thread(handleClient,client,std::ref(server),client_message));
    }
		close(serverSocket);
}
