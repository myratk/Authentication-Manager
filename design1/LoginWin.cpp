#include "stdafx.h"
#include "LoginWin.h"
#include "Test.h"

LoginWin::LoginWin() { //default contructor
	initscr();
}
void LoginWin::displayLogin() {
	// initialise
	// setup memory and clear screen

	// refresh screen to match memory

	int x = 0, y = 0, w = 60, h = 25;

	WINDOW* win = newwin(h, w, y, x);

	refresh();
	move(1, 1);
	printw("LOGIN WINDOW!");

	box(win, 0, 0);
	wrefresh(win);
}
void LoginWin::displayEmail() {
	mvprintw(4, 4, "User email");

	WINDOW* ebox = newwin(3, 20, 3, 20);
	refresh();
	box(ebox, 0, 0);
	wrefresh(ebox);
}
void LoginWin::displayPassword() {
	mvprintw(7, 4, "User Password");

	WINDOW* pbox = newwin(3, 20, 6, 20);
	refresh();
	box(pbox, 0, 0);
	wrefresh(pbox);
}
void LoginWin::displayOkCancel() {
	WINDOW* obox = newwin(3, 10, 9, 14);
	refresh();
	box(obox, 0, 0);
	mvwprintw(obox, 1, 1, "   Ok");
	wrefresh(obox);


	WINDOW* cbox = newwin(3, 10, 9, 34);
	refresh();
	box(cbox, 0, 0);
	mvwprintw(cbox, 1, 1, " Cancel");
	wrefresh(cbox);
}
void LoginWin::displayForgotP() {
	mvprintw(13, 20, "Forgot Password?");
}
void LoginWin::displaySignUp() {
	mvprintw(17, 22, "Sign Up now!");
}

void LoginWin::cycletab() {
	int i = tabc++ % 6;
	if (!(i < 6 && i >= 0)) throw AssertErr();
	move(gotab[i].getY(), gotab[i].getX());
	refresh();
}
void LoginWin::cycleback() {
	int i;
	if (tabc % 6 == 1) {
		i = 5; tabc = 6;
	}
	else {
		tabc -= 1;
		i = (tabc % 6) - 1;
	}
	move(gotab[i].getY(), gotab[i].getX());
}
void LoginWin::eventLoop() {
	noecho();
	cycletab();
	while (char c = getch()) {
		if (c == ERR)continue;
			int tab = (tabc % 6 == 0) ? 5 : tabc % 6 - 1;
			assert(tab >= 0 && tab < 6);
			
			switch (c) {
			case ' ':
				if (tab == obox) {
					choice = ok;
					return;
				}
				if (tab == cbox) {
					choice = cancel;
					return;
				}
				if (tab == fpbox) {
					choice = forgotpassword;
					return;
				}
				if (tab == subox) {
					choice = signup;
					return;
				}
				gotab[tab].setX(gotab[tab].getX() + 1); //move coordinates one space forward
				if (tab == ebox) {
					printw("%c", c);
					ud.email.append(1, c);
				}
				if (tab == pbox) {
					printw("%c", c);
					ud.password.append(1, c);
				}
				break;
			case 10:
			case -53: //enter
				if (tab == obox) {
					choice = ok;
					return;
				}
				if (tab == cbox) {
					choice = cancel;
					return;
				}
				if (tab == fpbox) {
					choice = forgotpassword;
					return;
				}
				if (tab == subox) {
					choice = signup;
					return;
				}
				break;
			case 8: //backspace
				if (tab == ebox) {
					if (!ud.email.empty())
						ud.email.resize(ud.email.size() - 1); //remove last character of string
				}
				if (tab == pbox) {
					if (!ud.password.empty())
						ud.password.resize(ud.password.size() - 1); //remove last character of string
				}
				if (tab == ebox || tab == pbox) {
					gotab[tab].setX(gotab[tab].getX() - 1); //move coordinates one space back
					move(gotab[tab].getY(), gotab[tab].getX()); //move cursor to those coordinates
					printw(" "); //print blank
					move(gotab[tab].getY(), gotab[tab].getX()); //move cursor back to those coordinates
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
				if (tab == obox) 
					tabc++;
				cycletab();
				break;
			case 3: //key_up
				if (tab == fpbox ||  tab == cbox)
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
					case pbox:
						if (int(c) != 127)printw("%c", '*');
						ud.password.append(1, c);
						break;
				}
			}
	}
}

void LoginWin::displayError(Error e) {
	noecho();
	string em = e.getErrorMsg();
	mvaddstr(2, 10, em.c_str()); //convert string to chars
	getch();
}

void LoginWin::displayLoginSucess() {
	int x = 2, y = 2, w = 56, h = 21;

	WINDOW* win = newwin(h, w, y, x);

	refresh();
	mvwprintw(win, 10, 14, "YOU ARE SUCCESSFULLY LOGGED IN");

	box(win, 0, 0);
	wrefresh(win);
	getch();
}

void LoginWin::DisplayWin(screen s)
{
	if (s == login) 
	{
		keypad(stdscr, TRUE);
		displayLogin();
		displayEmail();
		displayPassword();
		displayOkCancel();
		displayForgotP();
		displaySignUp();
		eventLoop();

		user = User(ud);
	}
	else if (s == successfulLogin) 
	{
		displayLoginSucess();
	}
}


