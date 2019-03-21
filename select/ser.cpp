#include <unistd.h>
#include <cstring>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <algorithm>
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

	fd_set fd, copy;
	FD_ZERO(&fd);
	FD_SET(ser_sock, &fd);
	int maxfd = ser_sock;
	while(1)
	{
		copy = fd;
		int n = select(maxfd+1, &copy, NULL, NULL, NULL);
		for(int i = 0; i <= maxfd; i++)
		{
			if(FD_ISSET(i, &copy))
			{
				if(i == ser_sock)
				{
					socklen_t slen = sizeof(ser_addr);
					cli_sock = accept(ser_sock, (sockaddr *)&cli_addr, &slen);
					maxfd = max(maxfd, cli_sock);
					FD_SET(cli_sock, &fd);
				}
				else
				{
					char s[100];
					int len = read(i, s, sizeof(s));
					if(len)
					{
						s[len] = 0;
						write(i, s, len);
					}
					else
					{
						FD_CLR(i, &fd);
						close(i);
					}	
				}
			}
		}
	}
	close(ser_sock);
	return 0;
}	