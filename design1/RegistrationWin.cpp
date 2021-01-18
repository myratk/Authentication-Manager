#include "stdafx.h"
#include "RegistrationWin.h"

RegistrationWin::RegistrationWin() { //default contructor
	initscr();
}

void RegistrationWin::displayUserReg() {
	// refresh screen to match memory

	int x = 0, y = 0, w = 60, h = 25;

	WINDOW* win = newwin(h, w, y, x);

	refresh();
	move(1, 21);
	printw("USER REGISTRATION");

	box(win, 0, 0);
	wrefresh(win);
}
void RegistrationWin::displayName() {
	mvprintw(5, 4, "Name(F/L)");

	WINDOW* fbox = newwin(3, 18, 4, 22);
	refresh();
	box(fbox, 0, 0);
	wrefresh(fbox);

	WINDOW* lbox = newwin(3, 18, 4, 41);
	refresh();
	box(lbox, 0, 0);
	wrefresh(lbox);
}
void RegistrationWin::displayEmail() {
	mvprintw(8, 4, "Email");

	WINDOW* ebox = newwin(3, 37, 7, 22);
	refresh();
	box(ebox, 0, 0);
	wrefresh(ebox);
}
void RegistrationWin::displayPassword() {
	mvprintw(11, 4, "Password");

	WINDOW* pbox = newwin(3, 37, 10, 22);
	refresh();
	box(pbox, 0, 0);
	wrefresh(pbox);
}
void RegistrationWin::displayReenterPassword() {
	mvprintw(14, 4, "Re-enter Password");

	WINDOW* rpbox = newwin(3, 37, 13, 22);
	refresh();
	box(rpbox, 0, 0);
	wrefresh(rpbox);
}
void RegistrationWin::displayMaidenName() {
	mvprintw(17, 4, "Mother's");
	mvprintw(18, 4, "maiden name");

	WINDOW* mnbox = newwin(3, 37, 16, 22);
	refresh();
	box(mnbox, 0, 0);
	wrefresh(mnbox);
}
void RegistrationWin::displayOkCancel() {
	WINDOW* rtbox = newwin(3, 20, 21, 4);
	refresh();
	box(rtbox, 0, 0);
	mvwprintw(rtbox, 1, 1, " Return to Login");
	wrefresh(rtbox);

	WINDOW* obox = newwin(3, 10, 21, 29);
	refresh();
	box(obox, 0, 0);
	mvwprintw(obox, 1, 1, " Submit");
	wrefresh(obox);


	WINDOW* cbox = newwin(3, 10, 21, 44);
	refresh();
	box(cbox, 0, 0);
	mvwprintw(cbox, 1, 1, " Cancel");
	wrefresh(cbox);

}

void RegistrationWin::cycletab() {
	int i = tabc++ % 9;
	move(gotab[i].getY(), gotab[i].getX());
	refresh();
}
void RegistrationWin::cycleback() {
	int i;
	if (tabc % 9 == 1) {
		i = 8; tabc = 9;
	}
	else {
		tabc -= 1;
		i = (tabc % 9) - 1;
	}
	move(gotab[i].getY(), gotab[i].getX());
}
void RegistrationWin::eventLoop() {
	noecho();
	cycletab();
	while (char c = getch()) {
		if (c == ERR)continue;
		int tab = (tabc % 9 == 0) ? 8 : tabc % 9 - 1;
		assert(tab >= 0 && tab < 9);
		
		switch (c) {
		case ' ':
			if (tab == rtbox) {
				choice = rt;
				return;
			}
			if (tab == obox) {
				choice = ok;
				return;
			}
			if (tab == cbox) {
				choice = cancel;
				return;
			}
			printw("%c", c);
			gotab[tab].setX(gotab[tab].getX() + 1); //move coordinates one space forward
			if (tab == fnbox) { ud.fName.append(1, c); }
			if (tab == lnbox) {	ud.lName.append(1, c); }
			if (tab == ebox) { ud.email.append(1, c); }
			if (tab == mnbox) { ud.maidenName.append(1, c); }
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
			if (tab == rtbox) {
				choice = rt;
				return;
			}
			break;
		case 8: //backspace
			if (tab == fnbox) {
				if (!ud.fName.empty())
					ud.fName.resize(ud.fName.size() - 1); //remove last character from string
			}
			if (tab == lnbox) {
				if (!ud.lName.empty())
					ud.lName.resize(ud.lName.size() - 1);//remove last character from string
			}
			if (tab == ebox) {
				if (!ud.email.empty())
					ud.email.resize(ud.email.size() - 1); //remove last character from string
			}
			if (tab == pbox) {
				if (!ud.password.empty())
					ud.password.resize(ud.password.size() - 1); //remove last character from string
			}
			if (tab == rpbox) {
				if (!ud.secpassword.empty())
					ud.secpassword.resize(ud.secpassword.size() - 1); //remove last character from string
			}
			if (tab == mnbox) {
				if (!ud.maidenName.empty())
					ud.maidenName.resize(ud.maidenName.size() - 1); //remove last character from string
			}
			if (!(tab == rtbox || tab == obox || tab == cbox)) {
				gotab[tab].setX(gotab[tab].getX() - 1); //move coordinates one space back
				move(gotab[tab].getY(), gotab[tab].getX()); //move cursor to those coordinates
				printw(" "); //print blank
				move(gotab[tab].getY(), gotab[tab].getX()); //move cursor back to those coordinates
			}
			break;
		case 5: //key_right
		case 9: //shift
			cycletab();
			break;
		case 4: //key_left
		case '_': //shift tab
			cycleback();
			break;
		case 2: //key_down
			if (tab == fnbox || tab == obox)
				tabc++;
			else if (tab == rtbox)
				tabc += 2;
			cycletab();
			break;
		case 3: //key_up
			if (tab == lnbox || tab == ebox || tab == obox)
				tabc--;
			else if (tab == cbox)
				tabc -= 2;
			else if (tab == fnbox) {
				if (tabc <= 2)
					tabc = 8;
				else
					tabc -= 2;
			}
			cycleback();
			break;
		default:
			gotab[tab].setX(gotab[tab].getX() + 1); //move coordinates one space forward
			switch (tab) {
			case fnbox:
				if (int(c) != 127)printw("%c", c);
				ud.fName.append(1, c);
				break;
			case lnbox:
				if (int(c) != 127)printw("%c", c);
				ud.lName.append(1, c);
				break;
			case ebox:
				if (int(c) != 127)printw("%c", c);
				ud.email.append(1, c);
				break;
			case pbox:
				if (int(c) != 127)printw("%c", '*');
				ud.password.append(1, c);
				break;
			case rpbox:
				if (int(c) != 127)printw("%c", '*');
				ud.secpassword.append(1, c);
				break;
			case mnbox:
				if (int(c) != 127)printw("%c", c);
				ud.maidenName.append(1, c);
				break;
			}
		}
	}
}

void RegistrationWin::displayError(Error e) {
	noecho();
	string em = e.getErrorMsg();
	if (e.getErrorCode() == 10) {
		mvaddstr(3, 20, em.c_str());
		getch();
	}
	else if (e.getErrorCode() == 11) {
		mvaddstr(3, 20, em.c_str());
		getch();
	}
	else if (e.getErrorCode() == 12) {
		mvaddstr(3, 15, em.c_str());
		getch();
	}
}

void RegistrationWin::DisplayWin(screen s) {
	if (s == registration)
	{
		keypad(stdscr, TRUE);
		displayUserReg();
		displayName();
		displayEmail();
		displayPassword();
		displayReenterPassword();
		displayMaidenName();
		displayOkCancel();
		eventLoop();

		if (choice == ok) {
			user = User(ud);
		}
	}
}
