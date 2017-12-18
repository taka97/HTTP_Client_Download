#ifndef HTTP_HEADER_H
#define HTTP_HEADER_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class HttpHeader
{
private:
	string HttpType;
	int Status;
	string Description;
	string TransferEncoding;
	string Connection;
	string ContentType;
public:
	HttpHeader(string header);
	string getStatus();
	string getDescription();
	string getHttptype();
};
#endif
