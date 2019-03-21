#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <algorithm>
#include <arpa/inet.h>
#include <pthread.h>
using namespace std;
char name[200];

int main(int argc, char **argv)
{
	
	int sock = socket(PF_INET, SOCK_STREAM, 0);

	sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	addr.sin_port = htons(atoi(argv[2]));

	connect(sock, (sockaddr *)&addr, sizeof(addr));
    scanf("%s", name);
    write(sock, name, sizeof(name));
    char s[100];
    read(sock, s, 100);
    puts(s);
	
	close(sock);
	return 0;
}