#include <stdio.h>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>
using namespace std;
int main(int argc, char **argv)
{	
	int sock;
	sockaddr_in your_addr;
	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if(sock == -1) puts("host2 1 error");
	memset(&your_addr, 0, sizeof(your_addr));
	your_addr.sin_family = AF_INET;
	your_addr.sin_addr.s_addr = inet_addr(argv[1]);
	your_addr.sin_port = htons(atoi(argv[2]));
	char s1[] = "hello! lesroad!";
	char s2[] = "GO time!";
	char s3[] = "Goodbye";
	sendto(sock, s1, 100, 0, (sockaddr *)&your_addr, sizeof(your_addr));
	sendto(sock, s2, 100, 0, (sockaddr *)&your_addr, sizeof(your_addr));
	sendto(sock, s3, 100, 0, (sockaddr *)&your_addr, sizeof(your_addr));
	close(sock);
	return 0;
}
