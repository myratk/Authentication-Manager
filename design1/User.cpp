#include "stdafx.h"
#include "User.h"


User::User(UserDetails ud)
{
	userDt = ud;
}
User::User(string f, string l, string e, string pw, string mn) {
	userDt.fName = f;
	userDt.lName = l;
	userDt.email = e;
	userDt.password = pw;
	userDt.maidenName = mn;
}

User::User() {}

string User::getFirstName() { return userDt.fName; }

string User::getLastName() { return userDt.lName; }

string User::getMaidenName() { return userDt.maidenName; }

string User::getEmail() { return userDt.email; }

string User::getPassword() { return userDt.password; }

string User::getsecpassword() { return userDt.secpassword; }

void User::setPassword(string p) {
	userDt.password = p;
}
void User::setsecPassword(string p) {
	userDt.secpassword = p;
}

