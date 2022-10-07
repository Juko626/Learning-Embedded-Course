#include <stdio.h>
#include <pthread.h>

pthread_t tid[37];

void *VVCC(void *arg)
{
	int a =*(int*)arg;
	printf("%d ",a);
}

int main()
{
	int id[37];
	for (int i=0; i<37; i++)
	{
		id[i]= i;
		pthread_create(&tid[i], NULL, VVCC , &id[i]);
	}
	for (int i=0; i<37; i++)
	{
		pthread_join(tid[i],NULL);

	}
	printf("VVCC END");
	return 0;
}

