#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <string>
#include <vector>
#include <iostream>
#include <WinSock2.h>
using namespace std;

class HttpClient
{
private:
	string hostName;
	string url;
	string httptype;
	string request;
	string response;
	WSADATA wsaData;
	SOCKET sClient;
	hostent* host;
	sockaddr_in servAdd;
	char* recvBuffer;
protected:
	void createFolder(std::vector<vector<string>> dsFolder);

public:
	HttpClient(string url, string httptype);
	void download();
	void download(string folderName);
};
#endif
