#ifndef EMAIL_H
#define EMAIL_H
#include <string>
#include <vector>
#include <iostream>
using namespace std;
class Email
{
	int id;
	string from;
	string subject;
	string text;
	vector<string> to;
public:
	Email(int id, string from, string subject, string text,vector<string> to) :
			id(id), from(from), subject(subject), text(text), to(to) {};

 /*
 return mail as a string,accoridng to the exersice demands
 */
	string printMail() const;

	int getId() const{
		return id;
	}
	string getFrom() const{
		return from;
	}
	string getSubject() const{
		return subject;
	}
	string getText() {
		return text;
	}
	vector<string> getTo() const{
		return to;
	}


	~Email();
};

#endif
