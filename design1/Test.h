#ifndef TEST_H
#define TEST_H

#include "Session.h"
#include "Amgui.h"
#include "LoginWin.h"
#include "ForgotPasswordWin.h"
#include "RegistrationWin.h"
#include <assert.h>

class AssertErr {};

class Test {
private:
	Amgui gui = Amgui();
	LoginWin lWin = LoginWin();
	RegistrationWin rWin = RegistrationWin();
	ForgotPasswordWin fpWin = ForgotPasswordWin();
	Session sesh = Session();
	bool ok;

public:
	bool getOk();

	void testcycletab();
	void testcycletab2();

	void testLcycletab();
	void testLcycletab2();

	void testValidateLogin();
	void testValidateLogin2();

	void testValidateRegistration();
	void testValidateRegistration2();

	void testValidateRequestReset();
	void testValidateRequestReset2();

	void testValidateResetPassword();
	void testValidateResetPassword2();

	void testall();
};
#endif
