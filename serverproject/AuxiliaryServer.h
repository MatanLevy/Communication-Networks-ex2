#ifndef AUX_SERVER
#define AUX_SERVER


#include "Server.h"
#include "Auxiliary.h"
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
/*
handling command from the client,see more details in readme.pdf
*/
void handleCommand(int socket,char* message,Server& server,string userName);
/*
create socket,bind and listen.if one of those system calls fail we exit.
*/
void connectToClient(int& serverSocket,int portNumber);
/*
updating dest param to be destinations of the message according to
param msg(the message from the client)
*/
bool createDest(string msg,vector<string> & dest);
/*
recive from client username and password,if incorrect return false else
return true
*/
bool CheckUser(int socket,char* message,Server server,string& user);

#endif
