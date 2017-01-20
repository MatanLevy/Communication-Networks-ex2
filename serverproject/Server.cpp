#include "Server.h"
#include<vector>



vector<string> Server :: getOnlineUsers() {
	vector<string> names;
	for (int i = 0 ; i < users.size(); i++) {
		if (socketIds[i] > 0) {
			names.push_back(users[i].getUserName());
		}
	}
	return names;
}

bool Server :: UpdateUsers(const char* fileName) {
	ifstream myfile;
	string userName, password;
	myfile.open(fileName);
	if (!myfile) {
		return false;
	}
	while (true) {
		getline(myfile, userName, '\t');
		getline(myfile, password);
		users.push_back(User(userName, password));
		if (myfile.eof())
			break;
	}
	socketIds = vector<int>(users.size(),-1);
	return true;
}
int Server :: userExist(string user) {
	for (size_t i = 0; i < users.size(); i++){
		if (users[i].getUserName() == user) {
			return i;
		}
	}
	return -1;
}

User* Server :: findUser(string userName) {
	int exist = userExist(userName);
	if (exist < 0 ) {
		return nullptr;
	}
	return &users[exist];
}

void Server :: compose(string from,vector<string> to,string subject,string text) {
	for (size_t i=0; i < to.size(); i++) {
		if (userExist(to[i]) >= 0) {
			findUser(to[i])->addMail(from,to,subject,text);
		}
	}
}
