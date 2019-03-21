//48
#include <stdio.h>
#include <arpa/inet.h>
using namespace std;
int main()
{
	struct sockaddr_in add1, add2;
	char *ip;
	add1.sin_addr.s_addr = htonl(0x1020304);
	add2.sin_addr.s_addr = htonl(0x1010101);
	
	ip = inet_ntoa(add1.sin_addr);
	printf("%s\n", ip);
	inet_ntoa(add2.sin_addr);
	printf("%s\n", ip);
	return 0;
}
