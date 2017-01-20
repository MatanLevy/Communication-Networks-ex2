#include "AuxiliaryServer.h"

using namespace std;

void connectToClient(int& serverSocket, int portNumber) {
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket < 0) {
		cout << strerror(errno) << endl;
		exit(1);
	}
	struct sockaddr_in myaddr;
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(portNumber);
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(serverSocket, (struct sockaddr*) &myaddr, sizeof(myaddr)) < 0) {
		cout << strerror(errno) << endl;
		exit(1);
	}
	if (listen(serverSocket, 5) < 0) {
		cout << strerror(errno) << endl;
		exit(1);
	}
}

void handleCommand(int socket, char* message, Server& server, string userName) {
	vector<string> dest;
	string subject, text;
	if ((string) message == "QUIT") {
		return;
	} else if ((string) message == SHOW_ALL_ONLINE) {
		string onlineUsers = "Online Users : " + converVectorToString(
				server.getOnlineUsers());
		sendAllData(socket, onlineUsers);
	} else if ((string) message == COMPOSE_NEW_MESSAGE) {
		recvAllData(socket, message);
		createDest(message, dest);
		recvAllData(socket, message);
		subject = getAfterSperator(':', message);
		recvAllData(socket, message);
		text = getAfterSperator(':', message);
		server.compose(userName, dest, subject, text);
		string mailSent = "Mail Sent";
		sendAllData(socket, mailSent);
	} else if ((string) message == SHOW_INBOX_COMMAND) {
		User* user = server.findUser(userName);
		vector<Email> mailList = user->getMailsList();
		sendAllData(socket, convertNumToString(mailList.size()));
		for (size_t i = 0; i < mailList.size(); i++) {
			string mail = mailList[i].printMail();
			sendAllData(socket, mail);
		}
	} else {
		vector<string> command = split((string) message, ' ');
		if (command[0] == GET_MAIL_COMMAND) {
			int id = std::stoi(command[1]);
			Email* mail = server.findUser(userName)->getMail(id);
			if (mail == nullptr) {
				sendAllData(socket, "false");
				return;
			}
			sendAllData(socket, "true");
			string from = "From: " + mail->getFrom();
			string to = "To: " + converVectorToString(mail->getTo());
			string subject = "Subject: " + mail->getSubject();
			string text = "Text: " + mail->getText();
			sendAllData(socket, from);
			sendAllData(socket, to);
			sendAllData(socket, subject);
			sendAllData(socket, text);
		} else if (command[0] == DELETE_MAIL_COMMAND) {
			int id = std::stoi(command[1]);
			server.findUser(userName)->deleteMail(id);
		} else if (command[0] == "MSG") {
			string destName = command[1];
			if (destName[destName.length() - 1] == ':') {
				destName.pop_back();
			}
			string msgstr = (string) message;
			string text = msgstr.substr(msgstr.find(":")+1);
			//string text = split((string) message, ':')[1];
			vector<string> onlineUsers = server.getOnlineUsers();
			if (std::find(onlineUsers.begin(), onlineUsers.end(), destName)
					!= onlineUsers.end()) {
				string msg = "New message from " + userName + " : " + text;
				int socketToSend = server.findSocketID(destName);
				sendAllData(socketToSend, msg);
			} else {
				server.compose(userName, vector<string> (1, destName),
						"Message received offline", text);
			}
		}
	}
}

bool createDest(string msg, vector<string> & dest) {
	size_t index = msg.find(':') + 1;
	if (index == string::npos)
		return false;
	string newDest = msg.substr(index);
	std::stringstream ss;
	ss.str(newDest);
	string item;
	while (getline(ss, item, ',')) {
		dest.push_back(item);
	}
	return true;
}

bool CheckUser(int socket, char* message, Server server, string& user) {
	recvAllData(socket, message);
	string userName(message);
	recvAllData(socket, message);
	string password(message);
	user = userName;

	if (server.userExist(userName) < 0) {
		return false;
	}
	if (!(server.findUser(userName)->authorize(userName, password))) {
		return false;
	}

	return true;

}
