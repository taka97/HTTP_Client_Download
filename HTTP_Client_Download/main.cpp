#include "HttpClient.h"

int main(int argc, char** argv)
{
	string url, httptype;
	string folderName;
	// check condition
	HttpClient client(url, httptype);
	client.download(folderName);

	return 0;
}