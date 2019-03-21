#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <algorithm>
#include <cstring>
using namespace std;
int main(int argc, char **argv)
{
	int sock;
	sock = socket(PF_INET, SOCK_STREAM, 0);
	sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	addr.sin_port = htons(atoi(argv[2]));
	connect(sock, (sockaddr *)&addr, sizeof(addr));
	char buf[1024];
	while(1)
	{
		scanf("%s", buf);
		int l = strlen(buf);
		if(strcmp(buf, "q") == 0) break;
		write(sock, buf, l);
		sleep(0.5);
		int len = read(sock, buf, 100);
		buf[len] = 0;
		printf("message from server : %s\n", buf);
	}
	close(sock);
	return 0;
}