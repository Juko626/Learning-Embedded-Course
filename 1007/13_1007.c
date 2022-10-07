#include <ncurses.h>
#include <unistd.h>
#include <pthread.h>


pthread_mutex_t mlock;

void *abc()
{
	int num=0;
	while(1)
	{
		pthread_mutex_lock(&mlock);
		mvprintw(10, 30, "        ");
		mvprintw(10, 30 ,"%d", num);
		refresh();
		pthread_mutex_unlock(&mlock);
		num--;
	}
}


int main()

{

	initscr();
	clear();
	
	pthread_mutex_init(&mlock, NULL);
	pthread_t tid;
	pthread_create(&tid, NULL, abc, NULL);

	int num=0;

	while(1)
	{
		pthread_mutex_lock(&mlock);
		mvprintw(10,10,"       ");
		mvprintw(10,10,"%d", num);
		refresh();
		pthread_mutex_unlock(&mlock);
		num++;
	}


	pthread_join(tid,NULL);
	getch();
	endwin();
	return 0;
}
