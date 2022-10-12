#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

// AWS IP
const char *IP = "127.0.0.1";
const char *PORT = "12345";

int sock;

//인터럽트 발생시 종료
void interrupt(int arg)
{
	printf("\nYou typped Ctrl + C\n");
	printf("Bye\n");

	close(sock);
	exit(1);
}

int main()
{
	//SIGINT 신호를 받으면 인터럽트 함수 발생
	signal(SIGINT, interrupt);

//소켓 생성 
//생성 불가시 에러문 출력 후 종료
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		printf("ERROR :: 1_Socket Create Error\n");
		exit(1);
	}

// 주소 설정
	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(IP);
	addr.sin_port = htons(atoi(PORT));

	// Connect
	//서버와 연결
	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1)
	{
		printf("ERROR :: 2_Connect Error\n");
		exit(1);
	}

	char buf[100];
	while (1)
	{

		//메모리 초기화
		memset(buf, 0, 100);
		//입력 값
		scanf("%s", buf);

		//만약 입력 값이 exit면 exit를 보내고 while 문 종료
		if (!strcmp(buf, "exit"))
		{
			write(sock, buf, strlen(buf));
			break;
		}

		//입력받은 값을 서버에 송신
		write(sock, buf, strlen(buf));
		memset(buf, 0, 100);
		int len = read(sock, buf, 99);
		
		// len이 0이면  에러문 출력 후 while 문 종료
		if (len == 0)
		{
			printf("INFO :: Server Disconnected\n");
			break;
		}
		printf("%s\n", buf);
	}

	// close sock
	
	close(sock);
	return 0;
}
