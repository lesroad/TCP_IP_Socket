#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>
using namespace std;
void *func(void *arg)
{
	int cli_sock = *(int *)arg;
	int l = 0;
	char s[100];
	while(l = read(cli_sock, s, sizeof(s)), l != 0)
	{
		s[l] = 0;
		write(cli_sock, s, l);
	}
	close(cli_sock);
}
int main(int argc, char **argv)
{
	char port[] = "8080";
	int ser_sock, cli_sock;
	ser_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(ser_sock == -1)
	{
		perror("socket error");
		exit(1);
	}
	sockaddr_in ser_addr, cli_addr;
	memset(&ser_addr, 0, sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	ser_addr.sin_port = htons(atoi(port));
	socklen_t len = sizeof(ser_addr);
	if(bind(ser_sock, (sockaddr *)&ser_addr, len) == -1)
	{
		perror("bind error");
		exit(1);
	}
	listen(ser_sock, 6);

	while(1)
	{
		cli_sock = accept(ser_sock, (sockaddr *)&cli_addr, &len);
		if(cli_sock == -1) continue;
		pthread_t tid;
		pthread_create(&tid, NULL, func, &cli_sock);
		pthread_detach(tid);
	}
	close(ser_sock);
	close(cli_sock);
	return 0;
}