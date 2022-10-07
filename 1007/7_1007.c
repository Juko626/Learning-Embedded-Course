#include <ncurses.h>
#include <unistd.h>

int main()
{

	initscr();

	printw("READY\n");
	refresh();
	usleep(1000* 200);

	printw("GO\n");
	refresh();
	usleep(1000*500);

	printw("FINISH\n");
	refresh();

	getch();
	endwin();
	return 0;
}

