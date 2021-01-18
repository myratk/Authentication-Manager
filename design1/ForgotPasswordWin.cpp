#include "stdafx.h"
#include "ForgotPasswordWin.h"

ForgotPasswordWin::ForgotPasswordWin() { //default contructor
	initscr();
}

void ForgotPasswordWin::displayForgotPass() {
	// refresh screen to match memory

	int x = 0, y = 0, w = 60, h = 25;

	WINDOW* win = newwin(h, w, y, x);

	refresh();
	move(1, 21);
	printw("Forgot Password");

	box(win, 0, 0);
	wrefresh(win);
}
void ForgotPasswordWin::displayInstructions() {
	mvprintw(7, 6, "Enter your email");

	WINDOW* ebox = newwin(3, 35, 8, 6);
	refresh();
	box(ebox, 0, 0);
	wrefresh(ebox);

	mvprintw(11, 6, "Enter your mother's maiden name");

	WINDOW* mnbox = newwin(3, 35, 12, 6);
	refresh();
	box(mnbox, 0, 0);
	wrefresh(mnbox);
}
void ForgotPasswordWin::displayResetButtons() {
	WINDOW* rbox = newwin(3, 15, 16, 3);
	refresh();
	box(rbox, 0, 0);
	mvwprintw(rbox, 1, 1, "    Reset");
	wrefresh(rbox);

	WINDOW* rtbox = newwin(3, 15, 16, 20);
	refresh();
	box(rtbox, 0, 0);
	mvwprintw(rtbox, 1, 1, "   Return");
	wrefresh(rtbox);

	WINDOW* cbox = newwin(3, 15, 16, 37);
	refresh();
	box(cbox, 0, 0);
	mvwprintw(cbox, 1, 1, "   Cancel");
	wrefresh(cbox);
}

void ForgotPasswordWin::cycletab() {
	int i = tabc++ % 5;
	move(gotab[i].getY(), gotab[i].getX());
	refresh();
}
void ForgotPasswordWin::cycleback() {
	int i;
	if (tabc % 5 == 1) {
		i = 4; tabc = 5;
	}
	else {
		tabc -= 1;
		i = (tabc % 5) - 1;
	}
	move(gotab[i].getY(), gotab[i].getX());
}
void ForgotPasswordWin::eventLoop() {
	noecho();
	cycletab();
	while (char c = getch()) {
		if (c == ERR)continue;
		int tab = (tabc % 5 == 0) ? 4 : tabc % 5 - 1;
		assert(tab >= 0 && tab < 5);
		
		switch (c) {
		case ' ':
			if (tab == rstbox) {
				choice = reset;
				return;
			}
			else if (tab == rtbox) {
				choice = rtrn;
				return;
			}
			else if (tab == cbox) {
				choice = cancel;
				return;
			}
			else if (tab == ebox) {
				printw("%c", c);
				ud.email.append(1, c);
			}
			else if (tab == mnbox) {
				printw("%c", c);
				ud.maidenName.append(1, c);
			}
			gotab[tab].setX(gotab[tab].getX() + 1); //move coordinates one space forward
			break;
		case 10:
		case -53: //enter
			if (tab == rstbox) {
				choice = reset;
				return;
			}
			if (tab == rtbox) {
				choice = rtrn;
				return;
			}
			if (tab == cbox) {
				choice = cancel;
				return;
			}
			break;
		case 8: //backspace
			if (tab == ebox) {
				if (!ud.email.empty()) {
					ud.email.resize(ud.email.size() - 1); //remove last character of string
					gotab[ebox].setX(gotab[ebox].getX() - 1); //move coordinates one space back
					move(gotab[ebox].getY(), gotab[ebox].getX()); //move cursor to those coordinates
					printw(" "); //print blank
					move(gotab[ebox].getY(), gotab[ebox].getX()); //move cursor back to those coordinates
				}
			}
			if (tab == mnbox) {
				if (!ud.maidenName.empty()) {
					ud.maidenName.resize(ud.maidenName.size() - 1); //remove last character of string
					gotab[mnbox].setX(gotab[mnbox].getX() - 1); //move coordinates one space back
					move(gotab[mnbox].getY(), gotab[mnbox].getX()); //move cursor to those coordinates
					printw(" "); //print blank
					move(gotab[mnbox].getY(), gotab[mnbox].getX()); //move cursor back to those coordinates
				}
			}
			break;
		case 5: //key_right
		case 9:
			cycletab();
			break;
		case 4: //key_left
		case '_': //shift tab
			cycleback();
			break;
		case 2: //key_down
			if (tab == rstbox)
				tabc += 2;
			else if (tab == rtbox)
				tabc++;
			cycletab();
			break;
		case 3: //key_up
			if (tab == ebox)
				tabc = 4;
			else if (tab == cbox)
				tabc -= 2;
			else if (tab == rtbox)
				tabc--; 
			cycleback();
			break;
		default:
			gotab[tab].setX(gotab[tab].getX() + 1); //move coordinates one space forward
			switch (tab) {
			case ebox:
				if (int(c) != 127)printw("%c", c);
				ud.email.append(1, c);
				break;
			case mnbox:
				if (int(c) != 127)printw("%c", c);
				ud.maidenName.append(1, c);
				break;
			}
		}
	}
}

void ForgotPasswordWin::displayError(Error e) {
	noecho();
	string em = e.getErrorMsg();
	mvaddstr(5, 5, em.c_str());
	getch();
}

void ForgotPasswordWin::DisplayWin(screen s){
	if (s == forgotpassword)
	{
		displayForgotPass();
		displayInstructions();
		displayResetButtons();
		eventLoop();

		if (choice == reset) {
			user = User(ud);
		}
	}
	else if (s == resetPassword)
	{
		ud.password = "";
		ud.secpassword = "";
		displayResetPass();
		displayEnterPass();
		displayResetButtons();
		resetVals();
		eventloopEnterPass();

		if (choice == reset) {
			user.setPassword(ud.password);
			user.setsecPassword(ud.secpassword);
		}
	}
}

void ForgotPasswordWin::displayResetPass() {
	// initialise
	// setup memory and clear screen
	initscr();

	// refresh screen to match memory

	int x = 0, y = 0, w = 60, h = 25;

	WINDOW* win = newwin(h, w, y, x);

	refresh();
	move(1, 21);
	printw("Reset Password");

	box(win, 0, 0);
	wrefresh(win);
}
void ForgotPasswordWin::displayEnterPass() {
	mvprintw(7, 6, "Enter your new password");

	WINDOW* pbox = newwin(3, 35, 8, 6);
	refresh();
	box(pbox, 0, 0);
	wrefresh(pbox);

	mvprintw(11, 6, "Re-enter password");

	WINDOW* rpbox = newwin(3, 35, 12, 6);
	refresh();
	box(rpbox, 0, 0);
	wrefresh(rpbox);
}
void ForgotPasswordWin::eventloopEnterPass() {
	noecho();
	cycletab();
	while (char c = getch()) {
		if (c == ERR)continue;
		int tab = (tabc % 5 == 0) ? 4 : tabc % 5 - 1;
		assert(tab >= 0 && tab < 5);

		switch (c) {
		case ' ':
			if (tab == rstbox) { //reset box
				choice = reset;
				return;
			}
			else if (tab == rtbox) { //return box
				choice = rtrn;
				return;
			}
			else if (tab == cbox) {
				choice = cancel;
				return;
			}
			else if (tab == pbox) {
				printw("*");
				ud.password.append(1, c);
			}
			else if (tab == rpbox) {
				printw("*");
				ud.secpassword.append(1, c);
			}
			gotab[tab].setX(gotab[tab].getX() + 1); //move coordinates one space forward
			break;
		case 10:
		case -53: //enter
			if (tab == rstbox) {
				choice = reset;
				return;
			}
			else if (tab == rtbox) {
				choice = rtrn;
				return;
			}
			else if (tab == cbox) {
				choice = cancel;
				return;
			}
			break;
		case 8: //backspace
			if (tab == pbox) {
				if (!ud.password.empty()) {
					ud.password.resize(ud.password.size() - 1); //remove last character of string
					gotab[pbox].setX(gotab[pbox].getX() - 1); //move coordinates one space back
					move(gotab[pbox].getY(), gotab[pbox].getX()); //move cursor to those coordinates
					printw(" "); //print blank
					move(gotab[pbox].getY(), gotab[pbox].getX()); //move cursor back to those coordinates
				}
			}
			if (tab == rpbox) {
				if (!ud.secpassword.empty()) {
					ud.secpassword.resize(ud.secpassword.size() - 1); //remove last character of string
					gotab[rpbox].setX(gotab[rpbox].getX() - 1); //move coordinates one space back
					move(gotab[rpbox].getY(), gotab[rpbox].getX()); //move cursor to those coordinates
					printw(" "); //print blank
					move(gotab[rpbox].getY(), gotab[rpbox].getX()); //move cursor back to those coordinates
				}
			}
			break;
		case 5: //key_right
		case 9: //tab
			cycletab();
			break;
		case 4: //key_left
		case '_': //shift tab
			cycleback();
			break;
		case 2: //key_down
			if (tab == rstbox)
				tabc += 2;
			else if (tab == rtbox)
				tabc++;
			cycletab();
			break;
		case 3: //key_up
			if (tab == pbox)
				tabc = 4;
			else if (tab == rtbox)
				tabc--;
			else if (tab == cbox) {
				tabc -= 2;
			}
			cycleback();
			break;
		default:
			gotab[tab].setX(gotab[tab].getX() + 1); //move coordinates one space forward
			switch (tab) {
			case pbox:
				if (int(c) != 127)printw("*");
				ud.password.append(1, c);
				break;
			case rpbox:
				if (int(c) != 127)printw("*");
				ud.secpassword.append(1, c);
				break;
			}
		}
	}
}
void ForgotPasswordWin::resetVals() {
	tabc = 0;
	gotab[pbox].setX(7); gotab[pbox].setY(9); //its original values
	gotab[rpbox].setX(7); gotab[rpbox].setY(13);
}
