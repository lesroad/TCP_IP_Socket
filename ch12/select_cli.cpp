#include <arpa/inet.h>
#include <stdio.h>
#include <cstring>
#include <unistd.h>
#include <algorithm>
#include <errno.h>
using namespace std;
int main(int argc, char **argv)
{
	int sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)  
	{
		perror("socket error");
		exit(1);
	}
	
	sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	addr.sin_port = htons(atoi(argv[2]));
	if(connect(sock, (sockaddr *)&addr, sizeof(addr)) == -1)
	{
		perror("connect error");
		printf("%d\n", errno);
		exit(1);
	}
	char buf[1024];
	while(1)
	{
		fgets(buf, sizeof(buf), stdin);
		if(!strcmp(buf, "q\n"))
		{
			close(sock);
			break;
		}
		write(sock, buf, strlen(buf));
		int l = read(sock, buf, sizeof(buf));
		buf[l] = 0;
		puts(buf);
	}
	return 0;
}


