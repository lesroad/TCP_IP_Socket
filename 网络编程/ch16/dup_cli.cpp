#include <arpa/inet.h>
#include <stdio.h>
#include <algorithm>
#include <unistd.h>
#include <cstring>
#include <iostream>
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
	FILE *rd, *wt;
	rd = fdopen(sock, "r");
	wt = fdopen(sock, "w");
	while(1)
	{
		if(fgets(buf, 100, rd) == NULL) break;
		fputs(buf, stdout);
		fflush(stdout);
	}
	fputs("Thank you!\n", wt);
	fflush(wt);
	fclose(rd);fclose(wt);
	return 0;
}