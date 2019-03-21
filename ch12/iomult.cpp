#include <arpa/inet.h>
#include <unistd.h>
#include <algorithm>
#include <stdio.h>
#include <cstring>
using namespace std;
char buf[1024];
int main(int argc, char **argv)
{
	int ser_sock, cli_sock;
	sockaddr_in ser_addr, cli_addr;
	ser_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(ser_sock == -1) puts("socket error");

	int opt = 1;
	setsockopt(ser_sock, SOL_SOCKET, SO_REUSEADDR, &opt, 4);

	memset(&ser_addr, 0, sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	ser_addr.sin_port = htons(atoi(argv[1]));
	if(bind(ser_sock, (sockaddr *)&ser_addr, sizeof(ser_addr)) == -1)
		puts("bind error");

	if(listen(ser_sock, 5) == -1) puts("listen error");

	fd_set fd, copy_fd;
	FD_ZERO(&fd);
	FD_SET(ser_sock, &fd);
	int fd_max = ser_sock+1;
	timeval timeout;
	socklen_t s_len = sizeof(cli_addr);
	while(1)
	{
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;
		copy_fd = fd;
		int fd_num = select(fd_max, &copy_fd, 0, 0, &timeout);
		if(fd_num == 0) continue;
		for(int i = 0; i < fd_max; i++)
		{
			if(FD_ISSET(i, &copy_fd))
			{
				if(i == ser_sock)//accept时服务器套接字发生变化
				{
					cli_sock = accept(ser_sock, (sockaddr *)&cli_addr, &s_len);
					FD_SET(cli_sock, &fd);
					fd_max = max(fd_max, cli_sock+1);
				}
				else			//传输数据时客户端套接字发生变化
				{
					int len = read(i, buf, 100);
					if(!len) 	//eof时删除fd数组信息并关闭套接字
					{
						close(i);
						FD_CLR(i, &fd);
						printf("close client %d\n", i);
					}
					else
					{
						buf[len] = 0;
						printf("message form client %d : %s\n", i, buf);
						write(i, buf, 100);
					}
				}
			}
		}		
	}
	close(ser_sock);
	return 0;
}