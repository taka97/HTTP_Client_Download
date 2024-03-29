#include "HttpClient.h"
#include "FileClient.h"
#include <iomanip>
#include <algorithm>

// khởi tạo với tham số cho trước
// dữ liệu cần khởi tạo
// m_url = ?
// m_httptype = ?
// m_hostName = ?
// m_pathserver = ?
HttpClient::HttpClient(string url, string httptype)
{
	if (url.find("http://") != -1)
		m_url = url.substr(7);
	else
		m_url = url;
	m_httptype = httptype;
	m_hostName = m_url.substr(0, m_url.find('/'));
}

HttpClient::~HttpClient()
{
}

bool HttpClient::isFile(string url)
{
	size_t num = ext.size();
	if (url.length() < 5 || url.back() == '/')
		return false;
	return url.substr(url.length() - 5).find(".") != string::npos ? true : false;
}

string HttpClient::folderName(string url)
{
	size_t sIdx, eIdx;
	sIdx = eIdx = url.length() - 2;
	for (sIdx = eIdx; sIdx != 0; sIdx--)
		if (url[sIdx] == '/')
		{
			sIdx++;
			break;
		}

	return url.substr(sIdx, eIdx - sIdx + 1);
}

void HttpClient::extractLinkFromFile(string fileName, string url, vector<string> &fileURL, vector<string> &folderURL)
{
	ifstream inFile(fileName);
	if (!inFile.is_open())
		cout << "Cannt open file 'Temporary' file" << endl;
	else
	{
		size_t fileSize = 0;
		string strTmp;
		size_t size, i;
		bool flagFound = false;

		inFile.seekg(0, inFile.end);
		fileSize = inFile.tellg();
		inFile.seekg(0, inFile.beg);

		while (!inFile.eof())
		{
			inFile.ignore(fileSize, '"');
			getline(inFile, strTmp, '"');

			if (strTmp == "")
				break;
			// check if link is file?
			if (isFile(strTmp))
			{
				if (strTmp[0] == '/')	// filename with short path
					strTmp = m_hostName + strTmp;
				else if (strTmp[0] == '.')
					strTmp = url + strTmp.substr(2);
				else if (strTmp.find("http://") == -1)	// only filename
					strTmp = url + strTmp;

				// check if this link is already exist?
				size = fileURL.size();
				for (i = 0; i < size; i++)
					if (strTmp == fileURL[i])
					{
						flagFound = true;
						break;
					}

				if (!flagFound)
					fileURL.push_back(strTmp);
			}
			else if (strTmp.back() == '/')	// check if link is folder?
			{
				if (strTmp[0] == '/')					// short link to full link
					strTmp = m_hostName + strTmp;
				if (strTmp.find("http://") != -1)		// remove http://
					strTmp = strTmp.substr(7);
				if (strTmp.find(url) != -1 && strTmp.length() > url.length())				// check if link is subfolder
				{
					// check if this link is already exist?
					size = folderURL.size();
					for (i = 0; i < size; i++)
						if (strTmp == folderURL[i])
						{
							flagFound = true;
							break;
						}

					if (!flagFound)
						folderURL.push_back(strTmp);
				}
			}
			strTmp.clear();
			flagFound = false;
		}
	}
}

void HttpClient::extractLinkFromFile(string fileName, string url, vector<string> &fileURL)
{
	ifstream inFile(fileName);
	if (!inFile.is_open())
		cout << "Cannt open file 'Temporary' file" << endl;
	else
	{
		size_t fileSize = 0;
		string strTmp;
		size_t size, i;
		bool flagFound = false;

		inFile.seekg(0, inFile.end);
		fileSize = inFile.tellg();
		inFile.seekg(0, inFile.beg);

		while (!inFile.eof())
		{
			inFile.ignore(fileSize, '"');
			getline(inFile, strTmp, '"');

			if (strTmp == "")
				break;
			// check if link is file?
			if (isFile(strTmp))
			{
				if (strTmp[0] == '/')	// filename with short path
					strTmp = m_hostName + strTmp;
				else if (strTmp[0] == '.')
					strTmp = url + strTmp.substr(2);
				else if (strTmp.find("http://") == -1)	// only filename
					strTmp = url + strTmp;

				// check if this link is already exist?
				size = fileURL.size();
				for (i = 0; i < size; i++)
					if (strTmp == fileURL[i])
					{
						flagFound = true;
						break;
					}

				if (!flagFound)
					fileURL.push_back(strTmp);
			}
			strTmp.clear();
			flagFound = false;
		}
	}
}

bool HttpClient::createFolder(string folderName, string path)
{
	folderName = path + folderName;
	cout << "Creating Folder: " << setw(50) << left << folderName;
	CreateDirectory(folderName.c_str(), NULL);

	int errorCode = GetLastError();
	switch (errorCode)
	{
	case ERROR_ALREADY_EXISTS:
		cout << "The specified directory already exists" << endl;
		return false;
	case ERROR_PATH_NOT_FOUND:
		cout << "One or more intermediate directories do not exist; this function will only create the final directory in the path" << endl;
		return false;
	default:
		cout << "Success" << endl;
		return true;
	}
}

bool HttpClient::createFolder(vector<string> dsFolder, string path)
{
	bool flag = true;		// true if create all folder is success, the other is false
	size_t numFolder = dsFolder.size();
	if (path == "")
	{
		for (size_t i = 0; i < numFolder; i++)
			if (!createFolder(dsFolder[i], path))
				flag = false;
	}
	else
	{
		if (!createFolder(path.substr(0, path.length() - 1)))
			flag = false;
		if (flag)
		{
			for (size_t i = 0; i < numFolder; i++)
				createFolder(dsFolder[i], path);
		}
	}
	return flag;
}

void HttpClient::downloadFile(string preName)
{
	FileClient client(m_url, m_httptype, preName);
	client.download();
}

void HttpClient::downloadFolder(string url, string preName, bool DownloadSubFolder)
{
	string pathSave = preName + folderName(url);
	createFolder(pathSave);		// create folder <MSSV>_folderName

	FileClient tempFile(url, m_httptype, "tmp", "", false);
	tempFile.download();		// download html file to extract link

	size_t size;
	pathSave.append("/");

	if (DownloadSubFolder)
	{
		vector<string> fileURL;
		vector<string> folderURL;
		extractLinkFromFile("tmp", url, fileURL, folderURL);	// extract link from html file

		size = folderURL.size();
		if (size != 0)
		{
			//// create sub-folder
			//for (size_t i = 0; i < size; i++)
			//	createFolder(folderName(folderURL[i]), pathSave);
			cout << "--------------------------------\n" << "Downloading files in folder " << pathSave << "\n--------------------------------" << endl;
			for (size_t i = 0; i < size; i++)
				downloadFolder(folderURL[i], pathSave, false);
		}

		size = fileURL.size();
		if (size != 0)
		{
			for (size_t i = 0; i < size; i++)
				FileClient(fileURL[i], m_httptype, "", pathSave).download();
		}
	}
	else
	{
		vector<string> fileURL;
		extractLinkFromFile("tmp", url, fileURL);	// extract link from html file

		size = fileURL.size();
		if (size != 0)
		{
			for (size_t i = 0; i < size; i++)
				FileClient(fileURL[i], m_httptype, "", pathSave).download();
		}
	}
	remove("tmp");
}

void HttpClient::download(string preName)
{
	// check if URL is file?
	if (isFile(m_url))
	{
		downloadFile(preName);
		cout << endl << endl << "Files is downloaded completely" << endl << endl;
	}
	else if (m_url[m_url.length() - 1] == '/')
	{
		downloadFolder(m_url, preName);
		cout << endl << endl << "All files and folders are downloaded completely" << endl << endl;
	}
}