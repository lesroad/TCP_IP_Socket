//p109
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <cstdlib>
using namespace std;
int main(int argc, char **argv)
{
	int sock;
	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if(sock == -1) puts("host1_1 error");
	sockaddr_in my_addr, your_addr;
	memset(&my_addr, 0, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	my_addr.sin_port = htons(atoi(argv[1]));
	if(bind(sock, (sockaddr *)&my_addr, sizeof(my_addr)) == -1)
		puts("host1_2error");
	for(int i = 0; i < 3; i++)
	{
		sleep(5);
		char s[20];
		socklen_t len = sizeof(your_addr);
		recvfrom(sock, s, 100, 0, (sockaddr *)&your_addr, &len);
		printf("message %d : %s\n", i+1, s);
	}
	close(sock);
	return 0;
}
