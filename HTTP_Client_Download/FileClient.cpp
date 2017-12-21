#include "FileClient.h"

FileClient::FileClient(string url, string httptype, string preName, string pathSave)
{
	m_url = url;
	FindAndReplace(m_url, " ", "%20");
	m_httptype = httptype;
	m_hostname = m_url.substr(0, url.find('/'));
	m_pathServer = m_url.substr(url.find('/'));
	m_pathSave = pathSave;
	m_filename = preName + url.substr(url.find_last_of('/') + 1);
	m_tempFile = "download.tmp";

	if (m_pathSave != ".")
	{
		m_filename = m_pathSave + m_filename;
		m_tempFile = m_pathSave + m_tempFile;
	}

	sClient = INVALID_SOCKET;
	host = NULL;
	recvBuffer = NULL;
}

FileClient::~FileClient()
{
	if (recvBuffer)
		delete[]recvBuffer;
}

int FileClient::download()
{
	// get address of server
	host = gethostbyname(m_hostname.c_str());
	if (host == NULL)
	{
		cout << "gethostbyname() is failed" << endl;
		return -1;
	}

	memcpy((char*)&servAdd.sin_addr, (char*)host->h_addr, sizeof(servAdd.sin_addr));
	servAdd.sin_family = host->h_addrtype;
	servAdd.sin_port = htons(80);

	// create socket on client
	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sClient == INVALID_SOCKET)
	{
		cout << "socket() is failed" << endl;
		return -1;
	}

	// connect to server
	if (connect(sClient, (sockaddr *)&servAdd, sizeof(servAdd)) == SOCKET_ERROR)
	{
		cout << "Ket noi that bai" << endl;;
		closesocket(sClient);
		return -1;
	}

	m_request += "GET ";
	m_request += m_pathServer;
	m_request += ' ' + m_httptype;
	m_request += "\r\nHost: ";
	m_request += m_hostname;
	m_request += "\r\nConnection: close";
	m_request += "\r\n\r\n";

	int sendret = send(sClient, m_request.c_str(), m_request.length(), 0);
	if (sendret == -1)
	{
		cout << "send() failed" << endl;
		return -1;
	}

	ofstream outFile;
	outFile.open(m_tempFile, ios::binary);

	if (!outFile.is_open())
	{
		cout << "OpenFile is failed" << endl;
		return -1;
	}

	int iRecv;
	recvBuffer = new char[BUFFER_LEN];
	ZeroMemory(recvBuffer, BUFFER_LEN);
	size_t offset;

	size_t iResponseLength = 0;

	cout << "Downloading file: " << m_filename << endl;

	// header
	do
	{
		iRecv = recv(sClient, recvBuffer, BUFFER_LEN, 0);
		if (iRecv > 0)
		{
			string header;
			m_response.append(recvBuffer, iRecv);

			if ((offset = m_response.find("\r\n\r\n")) != string::npos)
			{
				header = m_response.substr(0, offset);
				if (m_response.length() > offset + 4)
				{
					outFile.write(m_response.substr(offset + 4).c_str(), m_response.length() - offset - 4);
				}
				m_response = m_response.substr(0, offset);
				iResponseLength += iRecv;
				cout << "Downloaded: " << iResponseLength << " bytes\r";
				ZeroMemory(recvBuffer, BUFFER_LEN);
				break;
			}

			iResponseLength += iRecv;
			cout << "Downloaded: " << iResponseLength << " bytes\r";
			ZeroMemory(recvBuffer, BUFFER_LEN);
		}
	} while (iRecv > 0);

	// data
	do
	{
		iRecv = recv(sClient, recvBuffer, BUFFER_LEN, 0);
		if (iRecv > 0)
		{
			outFile.write(recvBuffer, iRecv);
			iResponseLength += iRecv;
			cout << "Downloaded: " << iResponseLength << " bytes\r";
			ZeroMemory(recvBuffer, BUFFER_LEN);
		}
		else if (iRecv == 0)
			cout << endl << "Download completed" << endl;
		else if (iRecv == SOCKET_ERROR)
			cout << "revc() is failed" << endl;
	} while (iRecv > 0);

	outFile.close();
	renderFile(m_response);

	closesocket(sClient);
}

void FileClient::renderFile(string header)
{
	size_t offset = header.find("chunked");
	if (offset != string::npos)
	{
		char buffer[BUFFER_LEN];
		ifstream inFile(m_tempFile, ios::binary);
		ofstream outFile(m_filename, ios::binary);
		int chunkedLength = 0;
		int readingLength;

		while (!inFile.eof())
			//while (fileSize != inFile.tellg())
		{
			inFile >> hex >> chunkedLength;
			inFile.ignore(2);

			readingLength = BUFFER_LEN;
			do
			{
				if (chunkedLength > BUFFER_LEN)
				{
					chunkedLength -= BUFFER_LEN;
					inFile.read(buffer, readingLength);
					outFile.write(buffer, readingLength);
				}
				else
				{
					ZeroMemory(buffer, BUFFER_LEN);
					inFile.read(buffer, chunkedLength);
					outFile.write(buffer, chunkedLength);
					break;
				}
			} while (true);
		}

		inFile.close();
		outFile.close();

		remove(m_tempFile.c_str());
	}
	else
	{
		remove(m_filename.c_str());
		rename(m_tempFile.c_str(), m_filename.c_str());
		remove(m_tempFile.c_str());
	}
}

size_t FileClient::FindAndReplace(string &strContent, string findCh, string replaceCh)
{
	size_t offset;
	size_t count = 0;
	size_t length = strContent.length();
	do
	{
		offset = strContent.find(findCh);
		if (offset != string::npos)
			strContent.replace(offset, 1, replaceCh);
	} while (offset != string::npos);

	return count;
}