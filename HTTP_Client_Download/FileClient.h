#ifndef FILE_CLIENT_H
#define FILE_CLIENT_H
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <string>
#include <fstream>
#include <WinSock2.h>
#define BUFFER_LEN 4096
using namespace std;

class FileClient
{
public:
	FileClient(string url, string httptype, string filename, string pathSave, bool isShow = true);
	FileClient(string url, string httptype, string preName = "");
	~FileClient();
	int download();
protected:
	void renderFile(string header);
	size_t FindAndReplace(string &strContent, string findCh, string replaceCh);
private:
	string m_url;
	string m_hostname;
	string m_pathServer;
	string m_pathSave;
	string m_filename;
	string m_tempFile;

	string m_httptype;
	string m_request;
	string m_response;
	bool m_isShow;

	SOCKET sClient;
	hostent *host;
	sockaddr_in servAdd;
	char *recvBuffer;
};
#endif