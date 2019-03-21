#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <stdlib.h>
using namespace std;
int main(int argc, char **argv)
{
	int ser_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(ser_sock == -1)
	{
		perror("socket error");
		exit(1);
	}
	printf("%d\n", ser_sock);
	pid_t pid = fork();
	if(!pid) printf("child %d\n", ser_sock);
	else 
	{
		printf("father %d\n", ser_sock);
		int sock = dup(ser_sock);
		printf("father2 %d\n", sock);
	}
	return 0;
}