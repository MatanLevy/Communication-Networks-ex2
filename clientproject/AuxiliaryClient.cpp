#include "AuxiliaryClient.h"
using namespace std;

char message[SIZE];


void loginSessionClient(int clientSocket) {
	string sendmsg;
	getline(cin, sendmsg);
	sendAllData(clientSocket, getAfterSperator(':', sendmsg));
	getline(cin, sendmsg);
	sendAllData(clientSocket, getAfterSperator(':', sendmsg));
	recvAllData(clientSocket, message);

	if ((string) message != CONNECTED_AUTHORIZE) {
		cout << message << endl;
		exit(1);
	} else {
		cout << message << endl;
	}
}

void handleClientCommand(int socket, string msg) {

	sendAllData(socket, msg);
	if (msg == QUIT_COMMAND) {
		cout << "Closing Connection..." << endl;
		close(socket);
		cout << "Connection Closed!" << endl;
		exit(1);
	}
	if (msg == SHOW_ALL_ONLINE) {
		recvAllData(socket, message);
		cout << message << endl;
	}
	if (msg == COMPOSE_NEW_MESSAGE) {
		for (int i = 1; i <= 3; i++) {
			getline(cin, msg);
			sendAllData(socket, msg);
		}
		recvAllData(socket, message);
		cout << message << endl;

	} else if (msg == SHOW_INBOX_COMMAND) {
		recvAllData(socket, message);
		int numberOfMessages = std::stoi(message);
		for (int i = 0; i < numberOfMessages; i++) {
			recvAllData(socket, message);
			cout << message << endl;
		}
	} else {
		vector<string> command = split(msg, ' ');
		if (command[0] == GET_MAIL_COMMAND) {
			recvAllData(socket, message);
			if ((string) message == "false") {
				cout << "mail ID not exist!" << endl;
				return;
			} else {
				for (int i = 0; i < 4; i++) {
					recvAllData(socket, message);
					cout << message << endl;
				}
			}
		}
	}
}
