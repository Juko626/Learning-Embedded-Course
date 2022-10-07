#include <stdio.h>
#include <ncurses.h>
#include <locale.h>
int main()
{
	setlocale(LC_CTYPE, "ko_KR.utf8");
	initscr();

	keypad(stdscr, TRUE);
	while(1)
	{
		int ch = getch();

		if (ch ==KEY_LEFT)
		{
			printw("왼쪽\n");
			refresh();
		}
		else if(ch ==KEY_RIGHT)
		{
			printw("오른쪽\n");
			refresh();
		}
		else if(ch == KEY_UP)
		{
			printw("위쪽\n");
			refresh();
		}
		else if(ch ==KEY_DOWN)
		{
			printw("아래쪽\n");
			refresh();
		}


	}

	getch();
	endwin();
	return 0;
}

