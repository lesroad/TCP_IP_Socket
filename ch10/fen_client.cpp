#include <stdio.h>
#include <arpa/inet.h>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
using namespace std;
int main(int argc, char **argv)
{
	int sock;
	sockaddr_in ser_addr;
	char s[200];
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1) puts("socket error");
	memset(&ser_addr, 0, sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = inet_addr(argv[1]);
	ser_addr.sin_port = htons(atoi(argv[2]));
	if(connect(sock, (sockaddr *)&ser_addr, sizeof(ser_addr)) == -1)
		puts("connect error");


	pid_t pid = fork();
	if(pid == 0)
	{
		while(1)
		{
			puts("wait for message...");
			scanf("%s", s);
			if(!strcmp(s, "q") || !strcmp(s, "Q"))
			{
				shutdown(sock, 1);
				break;
			}
			else
				write(sock, s, strlen(s));
			sleep(0.5);
		}

	}
	else
	{
		while(1)
		{
			int len = read(sock, s, 100);
			if(len == 0) break;
			s[len] = 0;
			printf("message from server:%s\n", s);
		}
	}
	close(sock);
	return 0;
}