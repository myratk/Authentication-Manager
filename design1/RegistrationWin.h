#ifndef REGISTRATIONWIN_H
#define REGISTRATIONWIN_H

#include "stdafx.h"
#include "Amgui.h"

using namespace std;

class RegistrationWin : public Amgui{
private:
	enum tab_cycler { fnbox, lnbox, ebox, pbox, rpbox, mnbox, rtbox, obox, cbox, };
	Point2D gotab[9] = { Point2D(23,5),Point2D(42,5),
		Point2D(23,8), Point2D(23, 11), Point2D(23, 14), Point2D(23, 17), Point2D(5, 22), Point2D(30, 22), 
		Point2D(45, 22)};
	int tabc = 0;

	void displayUserReg();
	void displayName();
	void displayEmail();
	void displayPassword();
	void displayReenterPassword();
	void displayMaidenName();
	void displayOkCancel();

	void cycletab();
	void cycleback();
	void eventLoop();

public:
	friend class Test;
	RegistrationWin();
	enum user_choice { rt, ok, cancel, };

	void DisplayWin(screen);
	void displayError(Error e);
};

#endif 

 
 



