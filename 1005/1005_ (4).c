#include <stdio.h>
#include <pthread.h>

pthread_t t[4];
int cnt;

void* run()
{
	for (int i=0; i<10000; i++)
	{
		cnt++;
	}
}

int main()
{
	for (int i=0; i<4; i++)
	{
		pthread_create(&t[i], NULL, run , NULL);
	}

	for (int i=0; i<4; i++)
	{
		pthread_join(t[i], NULL);
	}

	printf("%d\n",cnt);
	return 0;
}

