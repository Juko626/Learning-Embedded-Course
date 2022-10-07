#include <ncurses.h>
#include <unistd.h>

int main()
{
	initscr();

	printw("Hello");
	refresh();
	sleep(1);

	printw(" NEXT");
	refresh();
	sleep(1);

	printw("TARGET\n");
	printw("IS\n");
	refresh();
	sleep(1);

	printw("GOGO\nBYE");
	refresh();
	sleep(1);

	getch();
	endwin();
	return 0;
}
