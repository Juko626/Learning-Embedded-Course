#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *abc()
{
	printf("========\n");
	printf("%X\n" , (int*)malloc(4));
}

int main()
{
	pthread_t t1, t2;
	
	pthread_create(&t1, NULL, abc, NULL);
	pthread_create(&t2, NULL, abc, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2,NULL);

		return 0;
}

