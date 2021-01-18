#include "stdafx.h"
#include "Session.h"

Session::Session() {} //default constructor

void Session::runSession() {
	Amgui gui = Amgui();
	while (currScreen == Amgui::home) {
		gui.DisplayWin(Amgui::home); //display home screen
		gui.clearWin();

		switch (gui.Choice()) { //switch screen based on user choice
		case Amgui::HomeLogin:
			currScreen = Amgui::login;
			Login();
			break;
		case Amgui::HomeForgotpassword:
			currScreen = Amgui::forgotpassword;
			ForgotPassword();
			break;
		case Amgui::HomeSignup:
			currScreen = Amgui::registration;
			Register();
			break;
		case Amgui::HomeExit:
			currScreen = Amgui::end;
			endwin();
			break;
		default:
			break;
		}
	}
}

void Session::Login() {
	while (currScreen == Amgui::login)
	{
		LoginWin login = LoginWin();
		login.DisplayWin(currScreen); //display Login screen
		if (login.Choice() == LoginWin::ok) { //ok was pressed
			User user = login.getUser();
			Status stat = authMgr.ValidateLogin(user);
			if (stat.getStatusCode() == Status::userSession) { //status ok?
				login.clearWin();
				currScreen = Amgui::successfulLogin;
				login.DisplayWin(currScreen); //display successfulLogin screen
				endwin(); //deallocate memory and end ncurses
				return;
			}
			else if (stat.getStatusCode() == Status::LoginErrorSession){ //error status?
				login.displayError(stat.getError());
				login.clearWin();
				currScreen = Amgui::login; //display login screen again
			}
		}
		if (login.Choice() == LoginWin::cancel) { //cancel was pressed
			login.clearWin();
			endwin(); //deallocate memory and ends ncurses
			currScreen = Amgui::end;
			return;
		}
		if (login.Choice() == LoginWin::forgotpassword) { //forgot password was pressed
			login.clearWin();
			currScreen = Amgui::forgotpassword;
			ForgotPassword();
		}
		if (login.Choice() == LoginWin::signup) { //signup was pressed 
			login.clearWin();
			currScreen = Amgui::registration;
			Register();
		}
	}
}

void Session::ForgotPassword() {
	do {
		ForgotPasswordWin forgotPass = ForgotPasswordWin();
		forgotPass.clearWin();
		forgotPass.DisplayWin(currScreen); //display ForgotPassword screen
		if (forgotPass.Choice() == ForgotPasswordWin::reset) { //reset was pressed
			User user = forgotPass.getUser();
			Status stat = authMgr.ValidateRequestReset(user);
			if (stat.getStatusCode() == Status::ForgotpasswordSession) { //ok status?
				currScreen = Amgui::resetPassword;
				err = false;
				do {
					forgotPass.clearWin();
					forgotPass.DisplayWin(currScreen); //display resetPassword screen
					if (forgotPass.Choice() == ForgotPasswordWin::reset) { //reset was pressed
						user = forgotPass.getUser();
						stat = authMgr.ValidateResetPassword(user);
						if (stat.getStatusCode() == Status::ForgotpasswordSession) { //okay status?
							err = false;
							currScreen = Amgui::home;
							break;
						}
						else if (stat.getStatusCode() == Status::ForgotPasswordErrorSession) { //error status?
							err = true;
							forgotPass.displayError(stat.getError());
						}
					}
					if (forgotPass.Choice() == ForgotPasswordWin::rtrn) { //return was pressed
						currScreen = Amgui::home;
						break;
					}
					else if (forgotPass.Choice() == ForgotPasswordWin::cancel) {// cancel was pressed
						forgotPass.clearWin();
						endwin(); //deallocate memory and ends ncurses
						currScreen = Amgui::end;
						return;
					}
				} while (err); // while error in reset password screen
			}
			else if (stat.getStatusCode() == Status::ForgotPasswordErrorSession) { //error status?
				forgotPass.displayError(stat.getError());
				err = true;
			}
		}
		else if (forgotPass.Choice() == ForgotPasswordWin::rtrn) { //return was pressed
			currScreen = Amgui::home;
			err = false;
			break;
		}
		else if (forgotPass.Choice() == ForgotPasswordWin::cancel) { //cancel was pressed
			currScreen = Amgui::end;
			endwin(); //deallocate memory and ends ncurses
			err = false;
			break;
		}
	} while (err); // while error in forgotpassword screen
}

void Session::Register() {
	do {
		RegistrationWin reg = RegistrationWin();
		reg.clearWin();
		reg.DisplayWin(currScreen); //display register screen
		if (reg.Choice() == RegistrationWin::cancel) { //cancel was pressed
			currScreen = Amgui::end;
			endwin();
			return;
		}
		else if (reg.Choice() == RegistrationWin::ok) { //submit was pressed
			User user = reg.getUser();
			Status stat = authMgr.ValidateRegistration(user);
			if (stat.getStatusCode() == Status::RegistrationSession) { //ok status?
				reg.clearWin();
				err = false;
				currScreen = Amgui::home;
				break;
			}
			else if (stat.getStatusCode() == Status::RegistrationErrorSession) { //error status?
				reg.displayError(stat.getError());
				err = true;
			}
		}
		else if (reg.Choice() == RegistrationWin::rt) { //return was pressed
			currScreen = Amgui::home;
			err = false;
			break;
		}
	} while (err); //while error in registration screen 
}
