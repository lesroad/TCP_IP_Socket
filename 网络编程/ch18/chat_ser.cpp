#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
using namespace std;
int cli_socks[100], num = 0, judge = 0;
pthread_mutex_t mutex;
void *t_main(void *arg)
{
	char str[100];
	int sock = *(int *)arg;
	while(1)
	{
		int len = read(sock, str, 100);
		if(!len) break;
		str[len] = 0;
		pthread_mutex_lock(&mutex);
		//向所有客户端发送消息
		for(int i = 1; i <= num; i++)
		{
			write(cli_socks[i], str, sizeof(str));
		}
		pthread_mutex_unlock(&mutex);
	}
	int i;
	//线程同步
	pthread_mutex_lock(&mutex);
	for(i = 1; i <= num; i++)
	{
		if(cli_socks[i] == sock)
			break;
	}
	while(i < num) 
	{
		cli_socks[i] = cli_socks[i+1];
		i++;
	}
	num--;
	pthread_mutex_unlock(&mutex);
	printf("close connect is %d\n", sock);
	close(sock);
	if(!num && judge) exit(0);
}
int main(int argc, char ** argv)
{
	int ser_sock, cli_sock;
	sockaddr_in ser_addr, cli_addr;
	ser_sock = socket(PF_INET, SOCK_STREAM, 0);//创建套接字
	if(ser_sock == -1) 
		puts("socket error");

	//地址再分配
	int opt = 1;
	setsockopt(ser_sock, SOL_SOCKET, SO_REUSEADDR, &opt, 4);

	memset(&ser_addr, 0, sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	ser_addr.sin_port = htons(atoi("9190"));
	//分配地址信息
	bind(ser_sock, (sockaddr *)&ser_addr, sizeof(ser_addr));
	//转化可接受连接状态
	listen(ser_sock, 5);

	pthread_mutex_init(&mutex, NULL);//创建互斥量
	pthread_t id;
	puts("等待进入...");
	while(1)
	{
		socklen_t cli_len = sizeof(cli_addr);
		//请求受理
		cli_sock = accept(ser_sock, (sockaddr *)&cli_addr, &cli_len);
		judge = 1;
		//利用互斥量锁住临界区
		pthread_mutex_lock(&mutex);
		cli_socks[++num] = cli_sock;
		pthread_mutex_unlock(&mutex);

		pthread_create(&id, NULL, t_main, (void *)&cli_sock);//创建线程
		pthread_detach(id);//销毁线程
		printf("connect is %d\n", cli_sock);
	}
	pthread_mutex_destroy(&mutex);//销毁互斥量
	close(ser_sock);
	return 0;
}