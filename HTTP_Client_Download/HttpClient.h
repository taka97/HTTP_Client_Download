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
	string m_url;
	string m_httptype;
	string m_hostName;
	string m_pathserver;
protected:
	void createFolder(string path, vector<string> dsFolder);
	void downloadFile(string preName);
	void downloadFolder(string preName);
	size_t numPoint(string str);
public:
	HttpClient(string url, string httptype);
	~HttpClient();
	void download(string preName);
};
#endif
