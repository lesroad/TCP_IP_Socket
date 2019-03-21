#include <unistd.h>
#include <cstring>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <algorithm>
#include <sys/epoll.h>
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

	int epfd = epoll_create(10);
	epoll_event eve, eves[100];
	eve.events = EPOLLIN;
	eve.data.fd = ser_sock;
	epoll_ctl(epfd, EPOLL_CTL_ADD, ser_sock, &eve);

	while(1)
	{
		int n = epoll_wait(epfd, eves, 100, -1);
		for(int i = 0; i < n; i++)
		{
			if(eves[i].data.fd == ser_sock)
			{
				socklen_t slen = sizeof(ser_addr);
				cli_sock = accept(ser_sock, (sockaddr *)&ser_addr, &slen);
				eve.data.fd = cli_sock;
				epoll_ctl(epfd, EPOLL_CTL_ADD, cli_sock, &eve);
			}
			else
			{
				int fd = eves[i].data.fd;
				char s[100];
				int len = read(fd, s, sizeof(s));
				if(len)
				{
					s[len] = 0;
					write(fd, s, len);
				}
				else
				{
					epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
					close(fd);
				}
			}
		}
	}
	close(ser_sock);
	close(epfd);
	return 0;
}	