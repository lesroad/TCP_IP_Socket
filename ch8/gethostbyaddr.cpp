#include <stdio.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <netdb.h>
using namespace std;
int main(int argc, char ** argv)
{
	sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	hostent *host = gethostbyaddr((char *)&addr.sin_addr, 4, AF_INET);
	if(!host) puts("error!");
	printf("官方域名：%s\n", host->h_name);
	for(int i = 0; host->h_aliases[i]; i++)
	{
		printf("第%d个域名：%s", i+1, host->h_aliases[i]);
	}
	printf("地址族是%s\n", host->h_addrtype == AF_INET?"AF_INET":"AF_INET6");
	printf("ip地址长度是%d个字节\n", host->h_length);
	for(int i = 0; host->h_addr_list[i]; i++)
	{
		printf("第%d个ip地址为%s\n", i+1, inet_ntoa(*(in_addr *)host->h_addr_list[i]));
	}
	return 0;
}