#include <arpa/inet.h>
#include <stdio.h>
#include <cstring>
#include <unistd.h>
#include <algorithm>
#include <iostream>
using namespace std;
int main(int argc, char **argv)
{
	int ser_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(ser_sock == -1)  
	{
		perror("socket error");
		exit(1);
	}
	int opt = 1;
	setsockopt(ser_sock, SOL_SOCKET, SO_REUSEADDR, &opt, 4);
	sockaddr_in ser_addr, cli_addr;
	memset(&ser_addr, 0, sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	ser_addr.sin_port = htons(atoi(argv[1]));
	if(bind(ser_sock, (sockaddr *)&ser_addr, sizeof(ser_addr)) == -1)
	{
		perror("bind error");
		exit(1);
	}
	if(listen(ser_sock, 5) == -1)
	{
		perror("listen error");
		exit(1);
	}
	fd_set reads, copy;
	FD_ZERO(&reads);
	FD_SET(ser_sock, &reads);
	int num = ser_sock+1;
	int cli_sock;
	timeval timeout;
	while(1)
	{
		copy = reads;
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;
		int k = select(num, &copy, 0, 0, &timeout);
		if(k < 1) continue;
		for(int i = 0; i < num; i++)
		{
			if(FD_ISSET(i, &copy))
			{
				if(i == ser_sock)
				{
					socklen_t len = sizeof(ser_addr);
					cli_sock = accept(ser_sock, (sockaddr *)&cli_addr, &len);
					num = max(cli_sock+1, num);	
					FD_SET(cli_sock, &reads);		
				}
				else
				{
					char buf[1024];
					int l = read(i, buf, sizeof(buf));
					if(!l)
					{
						FD_CLR(i, &reads);
						close(i);
					} 
					else
					{
						buf[l] = 0;
						puts(buf);
						write(i, buf, l);
					}

				}
			}
		}
	}
	close(ser_sock);
	return 0;
}