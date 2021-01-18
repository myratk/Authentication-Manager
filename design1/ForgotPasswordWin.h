
#ifndef FORGOTPASSWORDWIN_H
#define FORGOTPASSWORDWIN_H

#include "stdafx.h"
#include "Amgui.h"

using std::cout;
using std::endl;

class ForgotPasswordWin : public Amgui{
private: 
	enum tab_cycler { ebox, mnbox, rstbox, rtbox, cbox }; // reset box, return box
	enum tab_cyclerEnterPass { pbox, rpbox }; //password box, re enter password box
	Point2D gotab[5] = { Point2D(7,9),Point2D(7,13),Point2D(7,17), Point2D(23,17), Point2D(40,17) };
	int tabc = 0;

	void displayForgotPass();
	void displayInstructions();
	void displayResetButtons();
	void cycletab();
	void cycleback();
	void eventLoop();

	void displayResetPass();
	void displayEnterPass();
	void resetVals();
	void eventloopEnterPass();

public:
	friend class Test;
	ForgotPasswordWin();
	enum user_choice { reset, rtrn, cancel };

	void DisplayWin(screen);
	void displayError(Error e);
};

#endif