#include <stdio.h>
#include <ncurses.h>
#include <locale.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>


#define N 10

pthread_mutex_t mlock;





char map[N][N] =
{
	"##########",
	"# #      #",
	"###      #",
	"#        #",
	"#   M    #",
	"#        #",
	"#        #",
	"#        #",
	"#        #",
	"##########",
};

int flag1=0;
int ny = 1;
int nx = 1;
int hp=100;
int flag=0;

int direct_Y[4] ={-1,1,0,0};
int direct_X[4] = {0,0,-1,1};




typedef struct{

	int idx_y;
	int idx_x;
}Node;


Node m_arr[10];
int m_arr_cnt=0;


void find_monster()
{
	pthread_mutex_lock(&mlock);
	for (int i=0; i<N; i++)
	{
		for (int j=0; j<N; j++)
		{
			if (map[i][j]=='M')
			{
				m_arr[m_arr_cnt].idx_y = i;
				m_arr[m_arr_cnt].idx_x = j;
				m_arr_cnt++;
			}
			
		}
	}
	pthread_mutex_unlock(&mlock);
}


void *monster_move()
{
	while(1)
	{
		for (int i=0; i<m_arr_cnt; i++)
		{
			int random = rand()%4;
			int nmy= m_arr[i].idx_y + direct_Y[random];
			int nmx= m_arr[i].idx_x + direct_X[random];

			if(map[nmy][nmx]!=' ') continue;
			m_arr[i].idx_y = nmy;
			m_arr[i].idx_x =nmx;

		}

			usleep(1000 *2000);
	}
}








void print()
{
	clear();
	for (int y=0; y<N; y++)
	{
		for (int x= 0; x<N; x++)
		{
			if(y==ny && x == nx)
			{
				printw("@");
			}
			else {
				printw("%c", map[y][x]);
			}
		}
		printw("\n");
	}
	printw("HP : %d\n", hp);
	refresh();
}

int sec=0;
void msec()
{
	sec=0;

}





int main()
{
	pthread_mutex_init(&mlock, NULL);
	pthread_t tid;
	pthread_create(&tid, NULL ,monster_move, NULL);


	setlocale(LC_CTYPE, "ko_KR.utf8");
	initscr();


	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	
	find_monster();
		
	while(1)
	{
		
		pthread_mutex_lock(&mlock);
		//monster_move();
		print();

		
		int ch = getch();
		if (ch ==ERR) ch=0;
		if (ch ==KEY_LEFT)
		{
			flag=0;

			if(map[ny][nx-1]=='#') continue;
			nx--;
			//printw("왼쪽\n");
			//refresh();
		}
		else if(ch ==KEY_RIGHT)
		{
			flag=0;
			if(map[ny][nx+1]=='#') continue;
			nx++;
	

			//printw("오른쪽\n");

		//	refresh();
		}
		else if(ch == KEY_UP)
		{
			flag=0;
			if(map[ny-1][nx]=='#') continue;
			ny--;
			//printw("위쪽\n");
		//	refresh();
		}
		else if(ch ==KEY_DOWN)
		{
			flag=0;
			if(map[ny+1][nx]=='#') continue;
			ny++;
			//printw("아래쪽\n");
		//	refresh();
		}
		if (map[ny][nx] =='^'&& flag==0)
		{
			hp-=10;
			flag=1;
		}

		for (int i=0; i<m_arr_cnt; i++)
		{

			if((nx ==m_arr[i].idx_x  && ny == m_arr[i].idx_y) || hp==0)
			{
				sleep(0.5);
				clear();
				mvprintw(10,10,"GAME OVER");
				refresh();
				sleep(3);
				flag1=1;
				break;
			}
		}
		if(flag1==1) break;
		if (map[ny][nx] =='Y')
		{
			print();
			usleep(500*1000);
			clear();
			mvprintw(10,10,"WIN (%d)" ,hp);
			refresh();
			sleep(1);
			break;
		}
		if (map[ny][nx] =='a')
		{
			hp=100;
			map[ny][nx]=' ';
		};
		
		pthread_mutex_unlock(&mlock);

	}
	pthread_join(tid, NULL);
	getch();
	endwin();
	return 0;
}

