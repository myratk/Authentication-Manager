#include "stdafx.h"
#include "Status.h"

Status::Status(StatusCode statcode) {
	sc = statcode;
}
Status::Status(Error &e, StatusCode statcode) {
	error = e;
	sc = statcode;
}
Error Status::getError() {
	return error;
}

int Status::getStatusCode() {
	return sc;
}