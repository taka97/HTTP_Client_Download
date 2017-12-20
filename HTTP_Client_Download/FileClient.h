#ifndef FILE_CLIENT_H
#define FILE_CLIENT_H

#include <iostream>
#include <string>
#include <fstream>
#include <WinSock2.h>
#define BUFFER_LEN 4096
using namespace std;

class FileClient
{
public:
	FileClient(string url, string httptype, string preName = "", string pathSave = ".");
	~FileClient();
	int download();
protected:
	void renderFile(string header);
	size_t FindAndReplace(string &strContent, string findCh, string replaceCh);
private:
	string m_url;			// URL
	string m_hostname;		// tên của máy chủ
	string m_pathServer;	// đường dẫn chứa tài nguyên trên hệ thống
	string m_pathSave;		// đường dẫn lưu file. Nếu lưu ở thư mục cùng cấp thì là dấu "."
	string m_filename;		// tên file chính thức
	string m_tempFile;		// tên file chứa dữ liệu tạm thời

	string m_httptype;
	string m_request;		// thông điệp gửi tới server
	string m_response;		// thông điệp từ server gửi về

	SOCKET sClient;			// Socket để kết nối đến server
	hostent *host;			// chứa địa chỉ IP của server
	sockaddr_in servAdd;	// chứa thông tin kết nối tới server
	char *recvBuffer;		// bộ nhớ đệm để chứa dữ liệu từ về từ server
};
#endif