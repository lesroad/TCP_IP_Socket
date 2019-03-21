//p89加法运算
#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <arpa/inet.h>
using namespace std;
const int N = 1024;
char s[N];
int sum(int n, int *a)
{
	int ans = a[0];
	for(int i = 1; i < n; i++)
	{
		ans += a[i];
	}
	return ans;
}
int main(int argc, char **argv)
{
	int ser_sock, cli_sock;
	ser_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(ser_sock == -1) puts("ser_1error");
	sockaddr_in ser_addr, cli_addr;
	memset(&ser_addr, 0, sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	ser_addr.sin_port = htons(atoi(argv[1]));
	if(bind(ser_sock, (sockaddr *)&ser_addr, sizeof(ser_addr)) == -1)
		puts("ser_2 error");
	if(listen(ser_sock, 5) == -1) puts("ser_3 error");
	socklen_t len = sizeof(cli_addr);
	cli_sock = accept(ser_sock, (sockaddr *)&cli_addr, &len);
	if(cli_sock == -1)  puts("ser_4 error");
	int n = 0, now = 0, cnt;//n必须初始0
	read(cli_sock, &n, 1);
	while(now < (n*4))
	{
		cnt = read(cli_sock, &s[now], N);
		now += cnt;
	}
	int ans = sum(n, (int *)s);
	write(cli_sock, &ans, 4);
	close(cli_sock);
	close(ser_sock);
	return 0;
}
