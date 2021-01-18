#include "stdafx.h"
#include "Error.h"

Error::Error() {
	errorCode = -1;
}
Error::Error(int ec, string em) {
	errorCode = ec;
	errorMsg = em;
}

Error::Error(int ec) {
	errorCode = ec;
}
int Error::getErrorCode() {
	return errorCode;
}

string Error::getErrorMsg() {
	return errorMsg;
}