#ifndef SESSION_H
#define SESSION_H

#include <iostream>
#include "Manager.h"
#include "Amgui.h"
#include "LoginWin.h"
#include "RegistrationWin.h"
#include "ForgotPasswordWin.h"

using namespace std;

class Session {
private:
	Manager authMgr;

	bool err = false;
	Amgui::screen currScreen = Amgui::home;

	void Login();
	void ForgotPassword();
	void Register();
public:
	friend class Test;
	Session();
	void runSession();
};

#endif
