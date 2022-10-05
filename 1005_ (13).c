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
	Node *b = (Node *)p;
	while(1)
	{
		//printf("%d\n", a.y);
		//printf("%d\n", a.x);
		printf("%d\n", b->y);
		printf("%d\n", (*b).y);
		sleep(1);
	}
}

int main()
{
	Node var;
	pthread_t tid;

	var.y = 10;
	var.x =40;

	pthread_create(&tid, NULL, abc, &var);
	pthread_join(tid, NULL);

	return 0;

}


