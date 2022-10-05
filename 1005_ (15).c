#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
int a_cnt=0;
int b_cnt=0;
int c_cnt=0;
char a ='A';
char c ='A';
int b=0;
void* DDD1()
{
	while(1)
	{
		if (a_cnt==3)
		{
			a='A';
			a_cnt=0;
		}
		printf("[DDD1] %c\n",a+a_cnt);
		a_cnt++;
		usleep(300*1000);
	}
	return 0;
}

void* DDD2()
{
	while(1)
	{
		if (b ==5)
		{
			b=0;
		}
		printf("[DDD2] %d\n",++b);
		usleep(200*1000);
	}
	return 0;
}

void* DDD3()
{
	while(1)
	{
		
		printf("[DDD3] %c\n",c+c_cnt);
		c_cnt++;
		usleep(300*1000);
	}
	return 0;
}


int main()
{
	pthread_t t1, t2 ,t3;

	pthread_create(&t1, NULL, DDD1, NULL);
	pthread_create(&t2, NULL, DDD2, NULL);
	pthread_create(&t3, NULL, DDD3, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);

	return 0;
}

