#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

// 서비스할 포트 미리 정해둠
const char *PORT = "12345";


int server_sock;
int client_sock;

//인터럽트 함수가 발생하는 경우는 서버에서 ctrl + C 하는 경우밖에 없음 
void interrupt(int arg)
{
	printf("\nYou typed Ctrl + C\n");
	printf("Bye\n");

	close(client_sock);
	close(server_sock);
	exit(1);
}


//띄어쓰기가 있으면 띄어쓰기를 없애준다
void removeEnterChar(char *buf)
{
	int len = strlen(buf);
	for (int i = len - 1; i >= 0; i--)
	{
		if (buf[i] == '\n')
			buf[i] = '\0';
		break;
	}
}

int main()
{
	// Ctrl + C 누를 경우 안전종료
	//SIGINT 가 들어오면 interrupt를 실행함
	signal(SIGINT, interrupt);

/
	// socket create

	//server_sock 소켓을 생성
	//PF_INET = IPv4
	//SOCK_STREAM TCP /IP?? 
	// 0 주소?

	server_sock = socket(PF_INET, SOCK_STREAM, 0);
	//소켓을 생성할 수 없으면 에러문을 출력하고 종료
	if (server_sock == -1)
	{
		printf("ERROR :: 1_Socket Create Error\n");
		exit(1);
	}

	// option setting
	// 종료 시 3분 정도 동일한 포트 배정 불가 에러 해결
	//실습의 편의를 위해 줄이는 것
	int optval = 1;
	setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, (void *)&optval, sizeof(optval));

	// 주소 설정
	//가장 중요한 주소 설정!
	// 구조체 선언후
	//IPv4
	// IP를 host to network long int 로 바꿈
	//문자열로 들어온 PORT번호 숫자로 바꾸고 host to network short int 로 바꿈

	struct sockaddr_in server_addr = {0};
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(atoi(PORT));


	// bind
	// 주소를 선언한 후 적용하는 것 이 bind 
	// bind 못하면 에러문 출력 후 종료
	if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
	{
		printf("ERROR :: 2_bind Error\n");
		exit(1);
	}

	// listen
	//클라이언트 연결 요청 대기
	//클라이언트 대기 큐? 에 넣음
	// listen 이 안되면 에러문 출력하고 종료
	if (listen(server_sock, 5) == -1)
	{
		printf("ERROR :: 3_listen Error");
		exit(1);
	}

//클라이언트 소켓 초기화
	client_sock = 0;
	struct sockaddr_in client_addr = {0};
	socklen_t client_addr_len = sizeof(client_addr);


	while (1)
	{
		// 새로운 클라이언트를 위해 초기화
		memset(&client_addr, 0, sizeof(client_addr));

		// accpet
		//클라이언트 연결 승인
		//은행원이 창구로 연결해줌
		//못하면 에러문 출력하고 종료 
		client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_addr_len);
		if (client_sock == -1)
		{
			printf("ERROR :: 4_accept Error\n");
			break;
		}

		// read & write
		//buf 설정
		char buf[100];
		while (1)
		{
			// 다음을 위해 메모리 초기화 
			memset(buf, 0, 100);



			//성공 시 buf 길이 반환
			//실패시 0 길이 반환 
			int len = read(client_sock, buf, 99);

			// remove '\n'
			removeEnterChar(buf);

			// client 와 연결이 끊어졌을 때 클라이언트 종료
			if (len == 0)
			{
				//0 반환 시 실패이므로 실패문 출력하고 break;
				// 은행에 온 손님이 여러가지 일을 원할 수 있음
				printf("INFO :: Disconnect with client... BYE\n");
				break;
			}

			// client 에서 exit 입력했을 때 클라이언트 종료
			if (!strcmp("exit", buf))
			{
				printf("INFO :: Client want close... BYE\n");
				break;
			}
			//받은 메시지를 그대로 클라이언트에게 전송
			write(client_sock, buf, strlen(buf));
		}
		// 클라이언트 소켓 close
		close(client_sock);
	}
	// 서버 소켓 close
	close(server_sock);
	return 0;
}
