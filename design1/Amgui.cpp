#include "stdafx.h"
#include "Amgui.h"
#include "Test.h"

Amgui::Amgui() { //default contrsuctor
	initscr();
}
void Amgui::DisplayWin(screen s) {
	if (s == home) //home screen display
	{
		int x = 0, y = 0, w = 60, h = 25;

		WINDOW* menuwin = newwin(h, w, y, x);

		refresh();
		move(1, 22);
		printw("Welcome to Home!");

		box(menuwin, 0, 0);
		wrefresh(menuwin);

		mvprintw(7, 27, "Login");
		mvprintw(10, 22, "Forgot Password");
		mvprintw(13, 26, "Sign-up");
		mvprintw(16, 27, "Exit");

		eventloop();
	}
}

void Amgui::cycletab() {
	int i = tabc++ % 4;
	if (!(i < 4 && i >= 0)) throw AssertErr();
	move(gotab[i].getY(), gotab[i].getX());
}
void Amgui::cycleback() {
	int i;
	if (tabc % 4 == 1) {
		i = 3; tabc = 4; }
	else {
		tabc -= 1;
		i = (tabc % 4) - 1; }
	move(gotab[i].getY(), gotab[i].getX());
}

void Amgui::eventloop() {
	noecho();
	keypad(stdscr, TRUE);
	cycletab();

	while (int c = getch()) {
		if (c == ERR)continue;
		int tab = (tabc % 4 == 0) ? 3 : tabc % 4 - 1;
		assert(tab >= 0 && tab < 4);

		switch (c) {
		case ' ': 
		case 10:
		case -53: //enter 
			if (tab == lbox) {
				choice = HomeLogin;
				return;
			}
			if (tab == fpbox) {
				choice = HomeForgotpassword;
				return;
			}
			if (tab == subox) {
				choice = HomeSignup;
				return;
			}
			if (tab == exitbox) {
				choice = HomeExit;
				return;
			}
			break;
		case 5: //key_right
		case 2: //key_down
		case 9: //shift
			cycletab();
			break;
		case 4: //key_left
		case 3: //key_up
		case '_': //shift tab
			cycleback();
			break;
		default:
			break;
		}
	}
}

void Amgui::clearWin() {
	erase();
	refresh();
}
int Amgui::Choice() {
	return choice;
}

User Amgui::getUser() {
	return user;
}
