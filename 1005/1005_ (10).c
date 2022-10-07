#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int a = 100;
int b;

void* abc()
{
	int c =10;
	printf("=============\n");
	printf("0x%X\n", &a);
	printf("0x%X\n", &b);
	printf("0x%X\n", &c);
}

int main()
{
	pthread_t t1, t2;
	pthread_create(&t1, NULL, abc, NULL);
	pthread_create(&t2, NULL, abc, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return 0;
}

