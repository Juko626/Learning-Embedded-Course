#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mlock;
pthread_t tid[4];

int cnt;

void *run()
{
	pthread_mutex_lock(&mlock);
	for (int i=0; i<10000; i++) cnt++;
	pthread_mutex_unlock(&mlock);

}

int main()
{
	pthread_mutex_init(&mlock, NULL);
	for (int i=0; i<4; i++)
	{
		pthread_create(&tid[i], NULL, run, &i);
		usleep(100);
	}
	for (int i=0; i<4; i++) pthread_join(tid[i], NULL);

	printf("%d\n", cnt);

	return 0;
}

