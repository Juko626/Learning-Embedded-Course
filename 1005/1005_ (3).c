#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
pthread_t tid[4];

int cnt;

void *run()
{
	for (int i=0; i<10000; i++) cnt++;
}

int main()
{
	for (int i=0; i<4; i++)
	{
		pthread_create(&tid[i], NULL, run, &i);
		usleep(100);
	}
	for (int i=0; i<4; i++) pthread_join(tid[i], NULL);

	printf("%d\n", cnt);

	return 0;
}

