// design1.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <curses.h>

using std::cout;
using std::endl;

int main() {
	//int main1(int argc, char **argv) {
	// initialise
	// setup memory and clear screen
	initscr();

	move(10, 10);

	//print a string to a window
	printw("Hello world!");

	// refresh screen to match memory
	refresh();

	// move(y,x) move to specific location
	int c = getch();
	printw("%d", c);
	//getch as we know it
	getch();

	//deallocate memory and ends ncurses
	endwin();

	return 0;
}

