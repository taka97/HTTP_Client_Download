#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <string>
#include <vector>
#include <iostream>
#include <WinSock2.h>
using namespace std;

class HttpClient
{
protected:
	const vector<string> ext = { ".jpg", ".png", ".gif", ".svg", ".ico",
		".pdf", ".doc", ".docx", ".xls", ".xlsx", ".ppt", ".pptx",
		".htm", ".html", ".xlm", ".txt",
		".mp3", ".mp4", ".css",
		".c", ".cpp", ".h",
		".rar", ".zip" };

private:
	string m_url;
	string m_httptype;
	string m_hostName;
	string m_pathserver;
protected:
	bool isFile(string url);
	string folderName(string url);
	void extractLinkFromFile(string fileName, string url, vector<string> &fileURL, vector<string> &folderURL);
	void extractLinkFromFile(string fileName, string url, vector<string>& fileURL);
	bool createFolder(string folderName, string path = "");
	bool createFolder(vector<string> dsFolder, string path = "");
	void downloadFile(string preName);
	void downloadFolder(string preName, bool DownloadSubFolder = true);
public:
	HttpClient(string url, string httptype);
	~HttpClient();
	void download(string preName);
};
#endif
