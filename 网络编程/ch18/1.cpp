#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
using namespace std;

int main(int argc, char ** argv)
{
	int ser_sock, cli_sock;
	sockaddr_in ser_addr, cli_addr;
	ser_sock = socket(PF_INET, SOCK_STREAM, 0);

	int opt = 1;
	setsockopt(ser_sock, SOL_SOCKET, SO_REUSEADDR, &opt, 4);

	memset(&ser_addr, 0, sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	ser_addr.sin_port = htons(atoi(argv[1]));
	bind(ser_sock, (sockaddr *)&ser_addr, sizeof(ser_addr));

	listen(ser_sock, 5);

	socklen_t cli_len = sizeof(cli_addr);
	cli_sock = accept(ser_sock, (sockaddr *)&cli_addr, &cli_len);
	char s[100];
	sleep(10);
	read(cli_sock, s, 100);
	puts(s);
	close(ser_sock);
	return 0;
}