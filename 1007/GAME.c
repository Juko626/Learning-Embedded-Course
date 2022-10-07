#include<stdio.h>
#include <ncurses.h>
#include<locale.h>
#include<pthread.h>

#define N 7
char map[N][N+1] = {

	"#######",
	"#     #",
	"# ##  #",
	"# ^^ a#",
	"#   ###",
	"#    Y#",
	"#######",
};

int ny = 1;
int nx = 1;

int my = 5;
int mx = 1;
int hp = 100;

int endflag = 0;
void print()
{
	clear();
	for(int y = 0; y<N; y++)
	{
		for(int x = 0; x<N; x++)
		{
			if(y == ny && x == nx)
			{
				printw("🐭");
			}
			else if (y == my && x == mx)
			{
				printw("😾");
			}
			else if(map[y][x] == '#')
			{
				printw("🏾");
			}
			else if(map[y][x] == '^')
			{
				printw("🌵");
			}			
			else if(map[y][x] == 'Y')
			{
				printw("🏠");
			}

			else if(map[y][x] == 'a')
			{
				printw("🧀");
			}

			else if(map[y][x] == ' ')
			{
				printw("  ");
			}

			else
			{
			printw("%c",map[y][x]);
			}
		}
		printw("\n");
	}
	printw("HP : %d\n", hp);
	refresh();
}

int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,-1,1};

void *monster()
{
	while(1)
	{
		if (endflag ==1)break;
		int i = rand()%4;
		int new_mx = mx + dx[i];
		int new_my = my + dy[i];
		if(map[new_my][new_mx] == '#'||map[new_my][new_mx]=='a')continue;
		mx = new_mx;
		my = new_my;
		usleep(200000);

	}
}



int main()
{
	setlocale(LC_CTYPE,"ko_KR.utf8");
	initscr();

	pthread_t t1;

	pthread_create(&t1,NULL,monster,NULL);

	int flag = 0;
	nodelay(stdscr,TRUE);
	keypad(stdscr,TRUE);
	while(1)
	{
		print();
		int ch = getch();

		if(ch==ERR) ch = 0;

		if (ch == KEY_LEFT)
		{
			if(map[ny][nx-1]!='#')
			{
				nx--;
				flag = 0;
			}
		}
		if (ch == KEY_RIGHT)
		{
			if(map[ny][nx+1]!='#')
			{
				nx++;
				flag = 0;
			}
		}
		if (ch == KEY_UP)
		{
			if(map[ny-1][nx]!='#')
			{
				ny--;
				flag = 0;
			}
		}
		if (ch == KEY_DOWN)
		{
			if(map[ny+1][nx]!='#')
			{
				ny++;
				flag = 0;
			}
		}
		if(map[ny][nx] == '^'&&flag ==0)
		{
			hp-=10;
			flag = 1;
		}
		
		if((my==ny&&mx==nx) || hp == 0)
		{
			print();
			usleep(500 *1000);
			clear();
			mvprintw(10,30,"GAME OVER");
			refresh();
			sleep(1);
			endflag =1;
			break;
		}	
		if(map[ny][nx] == 'Y')
		{
			print();
			usleep(500 *1000);
			clear();
			mvprintw(10,30,"WIN (%d)",hp);
			refresh();
			sleep(1);
			endflag = 1;
			break;
		}
		if(map[ny][nx] == 'a')
		{
			hp = 100;
			map[ny][nx] = ' ';
			print();
		}
	}
	getch();
	endwin();

	pthread_join(t1,NULL);
	return 0;
}
