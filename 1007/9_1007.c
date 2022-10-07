#include <ncurses.h>
#include <unistd.h>

int main()
{
	initscr();

	for (float i=0; i<10; i+=0.01)
	{
		printw("%0.2f", i);
		refresh();
		usleep(1000*10);
		clear();
	}
	char* a = "finish";
	printw("%s",a);
	refresh();
	sleep(2);
	endwin();
	return 0;
}

