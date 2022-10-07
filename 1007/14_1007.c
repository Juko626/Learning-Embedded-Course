#include <stdio.h>
#include <ncurses.h>

int main()
{
	initscr();

	keypad(stdscr, TRUE);
	while(1)
	{
		int ch = getch();

		if (ch ==KEY_LEFT)
		{
			printw("LEFT");
			refresh();
		}
	}

	getch();
	endwin();
	return 0;
}

