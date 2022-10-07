#include <ncurses.h>
#include <unistd.h>

int main()
{
	initscr();

	for (int i=0; i<5; i++)
	{
		printw("%c", 'a'+i);
		refresh();
		sleep(1);
	}

	endwin();
	return 0;
}
