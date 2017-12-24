#include <iostream>
#include <WinSock2.h>
#include <string>
#include "HttpClient.h"
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

void proccess(char *argv1, char *argv2, string &url, string &httptype);

int main(int argc, char** argv)
{
	string url, httptype;
	string preName = "1512174_1512177_1512675_";

	// kiểm tra tham số đầu vào
	if (argc != 3)
	{
		cout << "Usage: <MSSV> <URL> --<HTTP_Type>" << endl;
		cout << "    or <MSSV> --<HTTP_Type> <URL>" << endl;
		cout << "Example: 1512174_1512177_1512675.exe http://www.ietf.org/rfc/rfc2183.txt --http1.0" << endl;
		return -1;
	}
	// xử lý tham số đầu vào
	proccess(argv[1], argv[2], url, httptype);

	/*------------------------------------------------------------------------------------*/

	WSADATA wsaData;

	// Initialize Winsock
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		cout << "Error initializing Winsock 2.2" << endl;
		return -1;
	}

	// Check if winsock version is 2.2?
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		cout << "Winsock 2.2 not available" << endl;
		WSACleanup();
		return -1;
	}

	// check condition
	HttpClient client(url, httptype);
	client.download(preName);

	return 0;
}

void proccess(char *argv1, char *argv2, string &url, string &httptype)
{
	string temp_1(argv1);
	string temp_2(argv2);

	// argv[1] = url
	// argv[2] = http_type
	if (temp_1.find("--") == -1)
	{
		url = temp_1;
		httptype = "HTTP/" + temp_2.substr(6, 3);
	}
	else
	{
		url = temp_2;
		httptype = "HTTP/" + temp_1.substr(6, 3);
	}
}