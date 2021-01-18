#include "stdafx.h"
#include "Test.h"
#include "expect.h"

bool Test::getOk() {
	return ok;
}

bool testctab() {
	Test t;
	t.testcycletab();
	return t.getOk();
}
void Test::testcycletab() {
	try { //try-catch block = exception handling
		gui.cycletab();
		ok = true;
	}
	catch (AssertErr) {
		ok = false;
	}
}
void Test::testcycletab2() {
	describe("testcycleback2()", [] {
		// xdescribe("skip me", [] {});
		// xit("skip me too");
		describe("amgui cycleback func", [] {
			it("should check cycleback ok", [] {
				expect(testctab()).toBe(true);
				});
			});

		});
}

bool testLctab() {
	Test t;
	t.testLcycletab();
	return t.getOk();
}
void Test::testLcycletab() {
	try { //try-catch block = exception handling
		lWin.cycletab();
		ok = true;
	}
	catch (AssertErr) {
		ok = false;
	}
}
void Test::testLcycletab2() {
	describe("testLcycleback2()", [] {
		// xdescribe("skip me", [] {});
		// xit("skip me too");
		describe("login window cycleback func", [] {
			it("should check cycleback ok", [] {
				expect(testLctab()).toBe(true);
				});
			});

		});
}

bool testValLogin() {
	Test t;
	t.testValidateLogin();
	return t.getOk();
}
void Test::testValidateLogin() {
	lWin.ud.email = "myra@mail.com";
	lWin.ud.password = "m123";
	lWin.user = User(lWin.ud);
	Status stat = sesh.authMgr.ValidateLogin(lWin.user);
	if (stat.getStatusCode() == Status::userSession) 
		ok = true;
	else if (stat.getStatusCode() == Status::LoginErrorSession)
		ok = false;
}
void Test::testValidateLogin2() {
	describe("testValidateLogin2()", [] {
		describe("test Manager::ValidateLogin()", [] {
			it("should return usersession ", [] {
				expect(testValLogin()).toBe(true);
				});
			});
		});
}

bool testValReg() {
	Test t;
	t.testValidateRegistration();
	return t.getOk();
}
void Test::testValidateRegistration() {
	rWin.ud.fName = "Shane";
	rWin.ud.lName = "Adams";
	rWin.ud.email = "shane@mail.com";
	rWin.ud.password = "S123";
	rWin.ud.secpassword = "S123";
	rWin.ud.maidenName = "Kelly";
	rWin.user = User(rWin.ud);

	Status stat = sesh.authMgr.ValidateRegistration(rWin.user);
	if (stat.getStatusCode() == Status::RegistrationSession)
		ok = true;
	else if (stat.getStatusCode() == Status::RegistrationErrorSession)
		ok = false;
}
void Test::testValidateRegistration2() {
	describe("testValidateRegistration2()", [] {
		describe("test Manager::ValidateRegistration()", [] {
			it("should return registrationsession ", [] {
				expect(testValReg()).toBe(true);
			});
		});
	});
}

bool testValReqReset() {
	Test t;
	t.testValidateRequestReset();
	return t.getOk();
}
void Test::testValidateRequestReset() {
	fpWin.ud.email = "irti@mail.com";
	fpWin.ud.maidenName = "Shahana";
	fpWin.user = User(fpWin.ud);

	Status stat = sesh.authMgr.ValidateRequestReset(fpWin.user);
	cout << stat.getStatusCode();
	if (stat.getStatusCode() == Status::ForgotpasswordSession)
		ok = true;
	else if (stat.getStatusCode() == Status::ForgotPasswordErrorSession)
		ok = false;
}
void Test::testValidateRequestReset2() {
	describe("testValidateRequestReset2()", [] {
		describe("test Manager::ValidateRequestReset()", [] {
			it("should return forgotpasswordsession ", [] {
				expect(testValReqReset()).toBe(true);
				});
			});
		});
}

bool testValResetPass() {
	Test t;
	t.testValidateResetPassword();
	return t.getOk();
}
void Test::testValidateResetPassword() {
	fpWin.ud.email = "irti@mail.com";
	fpWin.ud.maidenName = "Shahana";
	fpWin.ud.password = "12345";
	fpWin.ud.secpassword = "12345";
	fpWin.user = User(fpWin.ud);

	Status stat = sesh.authMgr.ValidateResetPassword(fpWin.user);
	if (stat.getStatusCode() == Status::ForgotpasswordSession)
		ok = true;
	else if (stat.getStatusCode() == Status::ForgotPasswordErrorSession)
		ok = false;
}
void Test::testValidateResetPassword2() {
	describe("testValidateResetPassword2()", [] {
		describe("test Manager::ValidateResetPassword()", [] {
			it("should return forgotpasswordsession ", [] {
				expect(testValResetPass()).toBe(true);
				});
			});
		});
}


void Test::testall() {
	testcycletab2();
	testLcycletab2();
	testValidateLogin2();
	testValidateRegistration2();
	testValidateRequestReset2();
	testValidateResetPassword2();
	testSummary();
}