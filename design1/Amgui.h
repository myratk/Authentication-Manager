#ifndef AMGUI_H
#define AMGUI_H

#include <iostream>
#include <string>
#include <assert.h>
#include "curses.h"
#include "Point2D.h"
#include "User.h"
#include "Error.h"

class Amgui {
private:
	int tabc = 0;
	Point2D gotab[4] = { Point2D(26, 7), Point2D(21, 10), Point2D(25, 13), Point2D(26, 16) };
	enum tab_cycler { lbox, fpbox, subox, exitbox };
	void cycletab();
	void cycleback();
	void eventloop();
protected:
	int choice = 0;
	User user;
	UserDetails ud;
public:
	friend class Test;
	Amgui();
	enum user_choice { HomeLogin, HomeForgotpassword, HomeSignup, HomeExit };
	enum screen { home, login, successfulLogin, forgotpassword, resetPassword, registration, end};
	void DisplayWin(screen s);

	void clearWin();
	int Choice();
	User getUser();
};

#endif
