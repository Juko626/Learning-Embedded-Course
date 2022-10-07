#include<stdio.h>
#include<pthread.h>

void *abc(int time)
{
	if(time==1)
	{
		printf("ABC\n");
	}
	else if(time==2)
	{
		printf("MINMIN\n");

	}
	else if(time==3)
	{
		printf("COCO\n");
	}
	else if(time==4)
	{
		printf("KFCKFC\n");
	}
}

int main()
{
	pthread_t t[4];
	int k=0;

	for(int i=0; i<4; i++)
	{
		pthread_create(&t[i], NULL, abc(i+1), NULL);
	}

	for (int i=0; i<4; i++)
	{
		pthread_join(t[i], NULL);
	}
	return 0;
}

