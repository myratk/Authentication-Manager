#ifndef STATUS_H
#define STATUS_H
#include <iostream>
#include "Error.h"

class Status {
public:
	enum StatusCode {
		homeSession,
		userSession, LoginSession, LoginErrorSession,
		ForgotpasswordSession, ForgotPasswordErrorSession,
		RegistrationSession, RegistrationErrorSession
	};
private:
	Error error;
	StatusCode sc;

public:
	Status(StatusCode);
	Status(Error &e, StatusCode);
	Error getError();
	int getStatusCode();
};

#endif