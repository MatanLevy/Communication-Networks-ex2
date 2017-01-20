#ifndef AUX_CLIENT
#define AUX_CLIENT

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
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

/*
handilg user command .for more details see readme.pdf
*/
void handleClientCommand(int socket,string msg);
/*
geeting from the user username and password and checks with the server if
correct.if not,exit.
*/
void loginSessionClient(int clientSocket);

#endif
