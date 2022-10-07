#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *abc(void *p)
{
	int *a = (int *)p;

	while(1)
	{
		printf("%d\n" , *a);
		sleep(1);
	}
}

int main()
{
	pthread_t tid;
	int gv=1;

	pthread_create(&tid, NULL, abc, &gv);
	pthread_join(tid, NULL);
	


	return 0;
}

