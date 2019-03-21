//p47
#include <stdio.h>
#include <arpa/inet.h>
using namespace std;
int main()
{
	char *s = "127.232.124.79";
	struct sockaddr_in S;
	if(!inet_aton(s, &S.sin_addr))
		puts("错误！");
	else 
		printf("%#x\n", S.sin_addr);
	return 0;
}
