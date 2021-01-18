#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include "User.h"
#include "Status.h"
#include <string>
#include <fstream>
#include <vector>

class Manager {
private:
	Status stat = Status(Status::homeSession);
	enum fields { fname, lname, email, pword, mname };
	bool verifyPassword(string e, string p);
	bool userExists(string e);
	bool multipleMaidenNames(string mn);
	bool passwordNotSame(string p1, string p2);
public:
	Manager();
	Status ValidateLogin(User user);
	Status ValidateRegistration(User user);
	Status ValidateRequestReset(User user);
	Status ValidateResetPassword(User user);

	int errorCodes[7] = { 0, 10, 11, 12, 13, 20, 21 };
	string errorMsgs[7] = { "Incorrect Email or Password", "Please fill all fields", "Email already exists", "Passwords don't match",
		"Please enter only one maiden name", "No such user found", "Passwords don't match" };
	/*errorCodes[0] = 0; errorMsgs[0] = "Incorrect Email or Password";
	errorCodess[1] = 10; errorMsgs[1] = "Please fill all fields";
	errorCodes[2] = 11; errorMsgs[2] = "Email already exists";
	errorCodes[3] = 12; errorMsgs[3] = "Passwords don't match";
	errorCodes[4] = 13; errorMsgs[4] = "Please enter only one maiden name";
	errorCodes[5] = 20; errorMsgs[5] = "No such user found";
	errorCodes[6] = 21; errorMsgs[6] = "Passwords don't match"; */
};
#endif
