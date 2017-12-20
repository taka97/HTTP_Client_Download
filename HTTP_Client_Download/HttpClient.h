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
	string m_url;			// URL
	string m_httptype;		// HTTP-TYPE
	string m_hostName;		// tên máy chủ
	string m_pathserver;	// đường dẫn đến server
protected:
	void createFolder(vector<vector<string>> dsFolder);
	void downloadFile(string preName);
	void downloadFolder(string preName);
public:
	HttpClient(string url, string httptype);
	~HttpClient();
	void download(string preName);
};
#endif
