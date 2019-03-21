#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <algorithm>
#include <arpa/inet.h>
#include <pthread.h>
#include <iostream>
using namespace std;
char name[100], na[100];
void *wr(void *arg)
{
	char s[100], mes[100];
	int sock = *(int *)arg;
	int x = sizeof(s);
	while(1)
	{
		fgets(s, sizeof(s), stdin);
		s[strlen(s) - 1] = 0;
		if(!strcmp(s, "q")) break;
		sprintf(mes, "%s %s", name, s);
		write(sock, mes, strlen(mes));
	}
	sprintf(mes, "【系统消息】%s退出聊天室", na);
	write(sock, mes, strlen(mes));
	close(sock);
	exit(0);
}
void *rd(void *arg)
{
	int sock = *(int *)arg;
	char s[100];
	while(1)
	{
		int len = read(sock, s, 100);
		s[len] = 0;
		puts(s);
	}
}
int main(int argc, char **argv)
{
	puts("请输入用户名！");
	char mes[50];
	cin >> na;
	getchar();//防止fgets读回车
	int sock = socket(PF_INET, SOCK_STREAM, 0);//创建套接字

	sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(atoi("9190"));
	sprintf(name, "[%s]", na);
	connect(sock, (sockaddr *)&addr, sizeof(addr));//请求连接
	sprintf(mes, "【系统消息】%s进入聊天室", na);
	write(sock, mes, strlen(mes));

	pthread_t id_rd, id_wr;
	//创建读写线程
	pthread_create(&id_wr, NULL, wr, (void *)&sock);
	pthread_create(&id_rd, NULL, rd, (void *)&sock);

	pthread_join(id_wr, NULL);//等待写线程终止
	//pthread_join(id_rd, NULL);
	close(sock);
	return 0;
}