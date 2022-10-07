#include <stdio.h>
#include <unistd.h>
#include <pthread.h>



typedef struct{
	int y;
	int x;
}Node;


void *abc(void *p)
{
	Node a = *(Node *)p;

	while(1)
	{
		printf("%d\n" , a.y);
		printf("%d\n" , a.x);
		sleep(1);
	}
}

int main()
{
	Node qqq;
	pthread_t tid;
	int gv=1;
	qqq.y= 101010;
	qqq.x=234234;

	pthread_create(&tid, NULL, abc, &qqq);
	pthread_join(tid, NULL);
	


	return 0;
}

