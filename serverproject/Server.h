#pragma once
#include <vector>
#include "User.h"
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

class Server
{
	int portNumber;
	vector<User> users; // vector of users in the mail system
	vector<int> socketIds;
public:
	Server(int portNumber) : portNumber(portNumber) {};
	size_t getNUmberOfUsers() {
		return users.size();
	}
	void addSocketIdOfUser(int socketId,string userName) {
		for (size_t i = 0 ; i < users.size() ; i++) {
			if (users[i].getUserName() == userName) {
				socketIds[i] = socketId;
			}
		}
	}
	void removeSocketIdOfUser(string userName) {
			for (size_t i = 0 ; i < users.size() ; i++) {
				if (users[i].getUserName() == userName) {
					socketIds[i] = -1;
				}
			}
		}

	int findSocketID(string user) {
		for (size_t i = 0 ; i < users.size() ; i++) {
			if (users[i].getUserName() == user)
				return socketIds[i];
		}
		return -1;
	}

	/*
	Update User list from input file,return true if successfull
	*/
	bool UpdateUsers(const char* fileName);
	/*
	return list of all online users right now
	 */
	vector<string> getOnlineUsers();
	/*
	if user exist,return ptr to the user,else return nullptr
	*/
	User* findUser(string userName);
	/*
	if exist return index of the user in the vector,else return -1
	*/
	int  userExist(string userName);
	/*
	compose mail and updating rellavnt users about the mail
	*/
	void compose(string from,vector<string> to,string subject,string text);

};
