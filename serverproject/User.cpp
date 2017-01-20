#include "User.h"


string User :: getUserName() {
	return userName;
}

bool User :: authorize(string user,string pa) {
		return (userName == user && pa == password);
}

void User :: addMail(string from,vector<string> to,string subject,string text) {
  emails.push_back(Email(++maxId,from,subject,text,to));
}

int User ::  findMail(int id) {
  for (size_t i = 0 ; i < emails.size(); i++) {
    if (emails[i].getId() == id) {
      return i;
    }
  }
  return -1;
}

Email* User :: getMail(int id) {
  int mailId = findMail(id);
  return (mailId < 0) ? nullptr : &emails[mailId];
}
void User :: deleteMail(int id) {
  int index = findMail(id);
  if (index >= 0 ) {
    emails.erase(emails.begin()+index);
  }
}
// void User :: showInbox() {
//   for (size_t i = 0 ; i < emails.size(); i++) {
//     // emails[i].printMail();
//   }
// }

vector<Email> User :: getMailsList() {
  return emails;
}

User::~User() {}
