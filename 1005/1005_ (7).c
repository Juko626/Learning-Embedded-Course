#include<stdio.h>
#include<pthread.h>

void *abc()
{
	pthread_t id = pthread_self();
	printf("%lu\n", id);
}

int main()
{
	pthread_t t[4];

	for(int i=0; i<4; i++)
	{
		pthread_create(&t[i], NULL, abc, NULL);
	}

	for (int i=0; i<4; i++)
	{
		pthread_join(t[i], NULL);
	}
	return 0;
}

