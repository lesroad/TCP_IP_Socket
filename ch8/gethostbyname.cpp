#include <stdio.h>
#include <netdb.h>
#include <iostream>
#include <arpa/inet.h>//inet_ntoa
using namespace std;
int main(int argc, char **argv)
{
	hostent *host = gethostbyname(argv[1]);
	if(!host) puts("error");
	printf("官方域名：%s\n", host->h_name);
	for(int i = 0; host->h_aliases[i]; i++)
		printf("第%d个域名：: %s\n", i+1, host->h_aliases[i]);
	printf("地址族是%s\n", host->h_addrtype == AF_INET?"AF_INET":"AF_INET6");
	for(int i = 0; host->h_addr_list[i]; i++)
		printf("第%d个ip地址：%s\n", i+1, inet_ntoa(*(in_addr *)host->h_addr_list[i]));
	return 0;
}
