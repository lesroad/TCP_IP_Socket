//错误代码
#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <algorithm>
using namespace std;
int main(int argc, char **argv)
{
	int ser_sock, cli_sock;
	sockaddr_in ser_addr, cli_addr;
	ser_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(ser_sock == -1) puts("socket error");

	int opt = 1;
	setsockopt(ser_sock, SOL_SOCKET, SO_REUSEADDR, &opt, 4);

	memset(&ser_addr, 0, sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	ser_addr.sin_port = htons(atoi(argv[1]));
	if(bind(ser_sock, (sockaddr *)&ser_addr, sizeof(ser_addr)) != 0)
		puts("bind error");

	if(listen(ser_sock, 5) != 0) puts("listen error");

	socklen_t addr_len = sizeof(cli_addr);
	cli_sock = accept(ser_sock, (sockaddr *)&cli_addr, &addr_len);
	if(cli_sock == -1) puts("accept error");

	FILE *rd, *wt;
	rd = fdopen(cli_sock, "r");
	wt = fdopen(dup(cli_sock), "w");
	char buf[1024];
	
	
		fgets(buf, sizeof(buf), rd);
		fputs(buf, stdout);
		fflush(stdout);
		//printf("message from client : %s\n", buf);
	
	fputs("Thank client!", rd);
	fclose(rd);
	fclose(wt);
	return 0;
}