
#ifndef AUX_H
#define AUX_H



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
#include <iomanip>

using namespace std;

#define SIZE 2016
#define PORT_NUMBER 6423
#define LOCAL_HOST "127.0.0.1"
#define SHOW_ALL_ONLINE "SHOW_ONLINE_USERS"
#define COMPOSE_NEW_MESSAGE "COMPOSE"
#define SHOW_INBOX_COMMAND "SHOW_INBOX"
#define GET_MAIL_COMMAND "GET_MAIL"
#define DELETE_MAIL_COMMAND "DELETE_MAIL"
#define QUIT_COMMAND "QUIT"
#define CONNECTED_AUTHORIZE "Connected to server"
#define WELCOME_MESSAGE "Welcome!I am a simple-mail-server"
#define WRONG_LOGIN "wrong username or password.exit now..."
#define BAD_ARGUMENTS "Bad Arguments"




int sendall(int socket, const char * buf, int& len);
int recvall(int socket, char * buf, int& len);
string convertNumToString(int num);
string converVectorToString(const vector<string>& vec);
std::vector<std::string> split(const std::string &s, char delim);
string getAfterSperator(char separtor,string input);
void recvAllData(int client,char* client_message);
void sendAllData(int client,string sendmsg);


#endif
