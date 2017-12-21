#include "HttpClient.h"
#include "FileClient.h"

HttpClient::HttpClient(string url, string httptype)
{
	if (url.find("http://") != -1)
		m_url = url.substr(7, url.length() - 7);
	else
		m_url = url;
	m_httptype = httptype;
	m_hostName = m_url.substr(0, m_url.find('/'));
}

HttpClient::~HttpClient()
{
}

void HttpClient::downloadFile(string preName)
{
	FileClient client(m_url, m_httptype, preName);
	client.download();
}

void HttpClient::downloadFolder(string preName)
{

}

size_t HttpClient::numPoint(string str)
{
	size_t numPoint = 0;
	size_t length = str.length();
	for (size_t i = 0; i < length; i++)
		if (str[i] == '.')
			numPoint++;

	return numPoint;
}

void HttpClient::download(string preName)
{
	// check if URL is file?
	if (numPoint(m_url) > numPoint(m_hostName))
	{
		// URL is for download file
		if (m_url[m_url.length() - 1] == '/')
		{
			cout << "Downloading folder" << endl;
		}
		else
			downloadFile(preName);
	}
}

void HttpClient::createFolder(string path, vector<string> dsFolder)
{
}