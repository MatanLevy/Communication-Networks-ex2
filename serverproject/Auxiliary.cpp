#include "Auxiliary.h"
#include <iostream>
using namespace std;
int sendall(int socket, const char * buf, int& len){
    int total = 0;        // how many bytes we've sent
    int bytesleft = len; // how many we have left to send
    int n;

    while(total < len) {
        n = send(socket, buf + total, bytesleft, 0);
        if (n == -1) { break; }
        total += n;
        bytesleft -= n;
    }

    len = total; // return number actually sent here

    return n==-1?-1:0; // return -1 on failure, 0 on success
}

int recvall(int socket, char * buf, int& len){
    int total = 0;        // how many bytes we've sent
    int bytesleft = len; // how many we have left to send
    int n;

    while(total < len) {
        n = recv(socket, buf + total, bytesleft, 0);
        if (n == -1) { break; }
        total += n;
        bytesleft -= n;
    }

    len = total; // return number actually sent here
    buf[total] = '\0';

    return n==-1?-1:0; // return -1 on failure, 0 on success
}

void split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

string getAfterSperator(char separtor,string input) {
	int index = input.find(separtor)+1;
	string s = input.substr(index);
  s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

void recvAllData(int client,char* client_message) {
	int length = 5;
  int result;
	result = recvall(client,client_message,length);
  if (result < 0) {
    cout << "Coudlnt recive all data.exit now" << endl;
    exit(1);
  }
	length = std :: stoi(client_message);
	result = recvall(client,client_message,length);
  if (result < 0) {
    cout << "Coudlnt recive all data.exit now" << endl;
    exit(1);
  }

}

void sendAllData(int client,string sendmsg) {
  int length = sendmsg.size();
  int result;
  string lenmsg = convertNumToString(length);
  // if (lenmsg.size() == 1) {
  //   lenmsg = "0" + lenmsg;
  // }
  int length1 = lenmsg.size();
  result = sendall(client,lenmsg.data(),length1);
  if (result < 0) {
    cout << "Coudlnt recive all data.exit now" << endl;
    exit(1);
  }
  result = sendall(client,sendmsg.data(),length);
  if (result < 0) {
    cout << "Coudlnt recive all data.exit now" << endl;
    exit(1);
  }
}

string convertNumToString(int num) {
  stringstream ss;
  ss << setw(5) << setfill('0') << num;
  return ss.str();
}
string converVectorToString(const vector<string>& vec) {
  if (vec.size() == 0) {
    return "";
  }
  string result = vec[0];
  for (size_t i = 1 ; i < vec.size(); i++) {
    result+=',';
    result+=vec[i];
  }
  return result;
}
