#ifndef USER_H
#define USER_H

#include "stdafx.h"
#include <iostream>
#include <string>
#include "UserDetails.h"

using namespace std;

class User
{
private:
	UserDetails userDt;
public:
	User(UserDetails ud);
	User(string f, string l, string e, string pw, string mn);
	User();
	string getFirstName();
	string getLastName();
	string getMaidenName();
	string getEmail();
	string getPassword();
	string getsecpassword();
	void setPassword(string p);
	void setsecPassword(string p);
};
#endif