#include "HttpClient.h"
#include "FileClient.h"

/*--------------------------- HUY HOÀNG ---------------------------*/

// khởi tạo với tham số cho trước
// dữ liệu cần khởi tạo
// m_url = ?
// m_httptype = ?
// m_hostName = ?
// m_pathserver = ?
HttpClient::HttpClient(string url, string httptype)
{

}

// hủy đổi tượng
HttpClient::~HttpClient()
{
}

// hàm tải file
void HttpClient::downloadFile(string preName)
{
	FileClient client(m_url, m_httptype, preName);
	client.download();
}

// hàm tải dữ liệu trong folder
void HttpClient::downloadFolder(string preName)
{

}

// hàm sẽ tiến hành download dữ liệu từ URL và HTTP đã chọn
void HttpClient::download(string preName)
{
	// kiểm tra xem URL nhập vào là link file hay link folder?
	// nếu là link file thì gọi phương thức download file
	// nếu là link folder thì gọi phương thức download folder tương ứng
}

// tạo danh sách thư mục từ mẩng các phần tử tương ứng.
// dsFolder[0]: 
//	dsFolder[0][0]: tên thư mục gốc
//	dsFolder[0][1]: tên thư mục còn của thư mục gốc
// dsFolder[1]
//	dsFolder[1][0]: tên thư mục gốc
//	dsFolder[1][1]: tên thư mục con của thư mục gốc
// ......
void HttpClient::createFolder(vector<vector<string>> dsFolder)
{
	
}

/*--------------------------- HUY HOÀNG ---------------------------*/