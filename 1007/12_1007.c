#include <ncurses.h>
#include <unistd.h>

int main()

{
	initscr();
	clear();

	int num=0;

	while(1)
	{
		mvprintw(10,10,"       ");
		mvprintw(10,10,"%d", num);
		refresh();
		num++;
	}


	getch();
	endwin();
	return 0;
}
