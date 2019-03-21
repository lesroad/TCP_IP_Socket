#include <unistd.h>
#include <cstring>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/wait.h>
using namespace std;
void f(int arg)
{
	waitpid(-1, NULL, WNOHANG);
}
int main(int argc, char **argv)
{
	char port[] = "1234";
	int ser_sock, cli_sock;
	ser_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(ser_sock == -1)
	{
		perror("seocket error");
		exit(1);
	}
	int opt = 1;
	setsockopt(ser_sock, SOL_SOCKET, SO_REUSEADDR, &opt, 4);

	sockaddr_in ser_addr, cli_addr;
	memset(&ser_addr, 0, sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(atoi(port));
	ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(ser_sock, (sockaddr *)&ser_addr, sizeof(ser_addr)) == -1)
	{
		perror("bind error");
		exit(1);
	}

	if(listen(ser_sock, 20) == -1)
	{
		perror("listen error");
		exit(1);
	}

	struct sigaction act;
	act.sa_handler = f;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGCHLD, &act, NULL);

	while(1)
	{
		socklen_t slen = sizeof(cli_addr);
		cli_sock = accept(ser_sock, (sockaddr *)&cli_addr, &slen);
		if(cli_sock == -1) 
		{
			//这里不要写perror 否则会出现中断系统调用
			continue;
		}
		char str[100];
		printf("ip : %s, port : %d\n", inet_ntop(AF_INET, \
			&cli_addr.sin_addr.s_addr, str, sizeof(str)), \
			ntohs(cli_addr.sin_port));
		pid_t pid = fork();
		if(pid == 0)
		{
			close(ser_sock);
			int len;
			char s[1024];	
			while(len = read(cli_sock, s, sizeof(s)), len != 0)
			{
				s[len] = 0;
				write(cli_sock, s, len);
			}
			close(cli_sock);
			return 0;
		}
		else if(pid > 0)
			close(cli_sock);
		else
		{
			perror("fork error");
			continue;
		}
	}
	close(ser_sock);
	return 0;
}	