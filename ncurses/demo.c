#include <wchar.h>
#include <stdio.h>
#include <ncurses.h>
#include <locale.h>

const wchar_t chars[2] = {L'\0x2588', L'\0x25A1'};

int main(void)
{
	setlocale(LC_ALL, "");

	initscr();

	printw("HELLO WORLD!!!\n");

	add_wch(chars[0]);

	add_wch(chars[1]);

	refresh();

	getch();

//	clear();

	endwin();

	return 0;
}
