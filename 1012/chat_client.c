#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>

#define NAME_SIZE 20
#define MSG_SIZE 100

// AWS IP
const char *IP = "127.0.0.1";
const char *PORT = "12345";

pthread_t send_tid;
pthread_t receive_tid;
int exitFlag;
int sock;

// 채팅창에 보여질 이름의 형태
char name[NAME_SIZE] = "[DEFAULT]";
char msg[MSG_SIZE];

void *sendMsg()
{
	char buf[NAME_SIZE + MSG_SIZE];

	// exitFlag 는, 다른 한 쪽의 쓰레드를 종료하는 용도
	while (!exitFlag)
	{
		memset(buf, 0, NAME_SIZE + MSG_SIZE);
		// 채팅 프로그램이므로, 띄어쓰기는 반드시 들어가야
		// 그래서 fgets 사용하며, 엔터까지 입력됨을 유의하라
		fgets(msg, MSG_SIZE, stdin);
		if (!strcmp(msg, "exit\n"))
		{
			exitFlag = 1;
			write(sock, msg, strlen(msg));
			break;
		}
		if (exitFlag)
			break;
		// 실제로 서버에 보낼 메세지 형태
		// buf = "[ssafy] 안녕 얘들아"
		sprintf(buf, "%s %s", name, msg);
		write(sock, buf, strlen(buf));
	}
}

void *receiveMsg()
{
	char buf[NAME_SIZE + MSG_SIZE];
	while (!exitFlag)
	{
		memset(buf, 0, MSG_SIZE);
		int len = read(sock, buf, NAME_SIZE + MSG_SIZE - 1);
		if (len == 0)
		{
			printf("INFO :: Server Disconnected\n");
			kill(0, SIGINT);
			exitFlag = 1;
			break;
		}
		printf("%s\n", buf);
	}
}

void interrupt(int arg)
{
	printf("\nYou typped Ctrl + C\n");
	printf("Bye\n");

	pthread_cancel(send_tid);
	pthread_cancel(receive_tid);
	pthread_join(send_tid, 0);
	pthread_join(receive_tid, 0);

	close(sock);
	exit(1);
}

// 커멘드 아규먼트 필요로 함: 사용할 닉네임
int main(int argc, char *argv[])
{
	signal(SIGINT, interrupt);

	// 잘못 사용했을 경우, 프로그램 사용법 안내
	if (argc != 2)
	{
		printf("Usage : %s <name>\n", argv[0]);
		exit(1);
	}

	// sprintf 사용해서, [닉네임] 형태로 name 저장
	sprintf(name, "[%s]", argv[1]);

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		printf("ERROR :: 1_Socket Create Error\n");
		exit(1);
	}

	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(IP);
	addr.sin_port = htons(atoi(PORT));

	// Connect
	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1)
	{
		printf("ERROR :: 2_Connect Error\n");
		exit(1);
	}

	// Thread Run
	pthread_create(&send_tid, NULL, sendMsg, NULL);
	pthread_create(&receive_tid, NULL, receiveMsg, NULL);

	pthread_join(send_tid, 0);
	pthread_join(receive_tid, 0);

	// close sock
	close(sock);
	return 0;
}
