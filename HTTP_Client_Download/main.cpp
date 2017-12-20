#include "HttpClient.h"


void proccess(char *argv1, char *argv2, string &url, string &httptype);

int main(int argc, char** argv)
{
	string url, httptype;
	string preName = "1512001_";

	// kiểm tra tham số đầu vào
	if (argc != 3)
	{
		cout << "Usage: <MSSV> <URL> --<HTTP_Type>" << endl;
		cout << "    or <MSSV> --<HTTP_Type> <URL>" << endl;
		cout << "Example: 1512174 http://www.ietf.org/rfc/rfc2183.txt --http1.0" << endl;
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

	system("pause");
	return 0;
}

/*--------------------------- VINH ---------------------------*/
// lấy dữ liệu URL và HTTP-TYPE từ tham số dòng lệnh của chương trình.
// dữ liệu được trả về 2 biến tương ứng
// cú pháp:	<MSSV> <URL> --<HTTP-TYPE>
// hoặc		<MSSV> <URL> --<HTTP-TYPE>
// ví dụ:		1512001 http://www.ietf.org/rfc/rfc2183.txt --http1.0
void proccess(char *argv1, char *argv2, string &url, string &httptype)
{
	
}

/*--------------------------- VINH ---------------------------*/