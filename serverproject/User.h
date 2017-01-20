#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <iostream>
#include "Email.h"
using namespace std;
class User
{
	int maxId = 0;
	string userName;
	string password;
	vector<Email> emails;
public:
	User(string userName, string password) : userName(userName), password(password) {};
 /*
 getter for username
 */
	string getUserName();
	/*
	return true iff username and password correct
	*/
	bool authorize(string user,string pa);
	/*
	add new mail to mail vector of the user
	*/
  void addMail(string from,vector<string> to,string subject,string text);
	/*
	if exist,return the index in the vector else return -1
	*/
	int findMail(int id);
	/*
	return ptr to mail if exist,else nullptr
	*/
	Email* getMail(int id);
	/*
	delete the mail according to id
	*/
	void deleteMail(int id);
	// void showInbox();
	/*
	getter for vector of emails
	*/
	vector<Email> getMailsList();
	~User();
};

#endif
