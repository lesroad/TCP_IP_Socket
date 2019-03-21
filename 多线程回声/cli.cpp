#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
using namespace std;
int main(int argc, char **argv)
{
	char port[] = "8080";
	int sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == -1)
	{
		perror("socket error");
		exit(1);
	}
	sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);
	addr.sin_port = htons(atoi(port));
	socklen_t len = sizeof(addr);
	if(connect(sock, (sockaddr *)&addr, len) != 0)
	{
		perror("connect error");
		exit(1);
	}
	char s[100];
	while(1)
	{
		fgets(s, sizeof(s), stdin);
		if(strcmp(s, "q\n") == 0)
		{
			break;
		}
		write(sock, s, strlen(s));
		int l = read(sock, s, sizeof(s));
		s[l] = 0;
		fputs(s, stdout);
	}
	close(sock);
	return 0;
}