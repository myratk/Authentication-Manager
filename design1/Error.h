#ifndef ERROR_H
#define ERROR_H

#include <iostream> 
#include <string>
using namespace std;

class Error {
private:
	int errorCode = -1; //-1 --> no error
	string errorMsg;
public:
	Error();
	Error(int ec);
	Error(int ec, string em);
	int getErrorCode();
	string getErrorMsg();
};

#endif
