#ifndef LOGINWIN_H
#define LOGINWIN_H

#include "stdafx.h"
#include "Amgui.h"

using std::cout;
using std::endl;
using std::string;

class LoginWin : public Amgui{
private:
	enum tab_cycler { ebox, pbox, obox, cbox, fpbox, subox };
	Point2D gotab[6] = { Point2D(21,4),Point2D(21,7),Point2D(15,10),Point2D(35,10),Point2D(19,13),Point2D(21,17) };
	int tabc = 0;

	void displayLogin();
	void displayEmail();
	void displayPassword();
	void displayOkCancel();
	void displayForgotP();
	void displaySignUp();
	void cycletab();
	void cycleback();
	void eventLoop();

	void displayLoginSucess();
public:
	friend class Test;
	LoginWin();
	enum user_choice { ok, cancel, forgotpassword, signup };

	void DisplayWin(screen);
	void displayError(Error e);
};
#endif