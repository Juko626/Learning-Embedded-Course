#include <stdio.h>
#include <pthread.h>

void* run(){
	static int cnt =15;
	cnt++;
	printf("%d\n" ,cnt);
}


int main()
{
	pthread_t t1,t2;

	pthread_create(&t1, NULL, run, NULL);
	pthread_create(&t2, NULL, run, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	return 0;
}

