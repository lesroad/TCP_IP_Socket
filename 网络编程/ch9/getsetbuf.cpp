#include <stdio.h>
#include <arpa/inet.h>
using namespace std;
int main(int argc, char **argv)
{
	int tcp_sock, udp_sock;
	tcp_sock = socket(PF_INET, SOCK_STREAM, 0);
	udp_sock = socket(PF_INET, SOCK_DGRAM, 0);
	//查看输入输出缓冲
	int rcvbuf, sndbuf;
	socklen_t len = 4;
	int state = getsockopt(tcp_sock, SOL_SOCKET, SO_RCVBUF, &rcvbuf, &len);
	if(state) puts("1 error");
	printf("tcp rcvbuf:%d\n", rcvbuf);
	state = getsockopt(tcp_sock, SOL_SOCKET, SO_SNDBUF, &sndbuf, &len);
	if(state) puts("2 error");
	printf("tcp sndbuf:%d\n", sndbuf);	
	state = getsockopt(udp_sock, SOL_SOCKET, SO_RCVBUF, &rcvbuf, &len);
	if(state) puts("3 error");
	printf("udp rcvbuf:%d\n", rcvbuf);
	state = getsockopt(udp_sock, SOL_SOCKET, SO_SNDBUF, &sndbuf, &len);
	if(state) puts("4 error");
	printf("udp sndbuf:%d\n", sndbuf);

	//修改输入输出缓冲
	rcvbuf *= 2, sndbuf *= 3;
	state = setsockopt(tcp_sock, SOL_SOCKET, SO_RCVBUF, &rcvbuf, len);
	if(state) puts("5 error");
	printf("tcp set rcvbuf:%d\n", rcvbuf);
	state = setsockopt(tcp_sock, SOL_SOCKET, SO_SNDBUF, &sndbuf, len);
	if(state) puts("6 error");
	printf("tcp set sndbuf:%d\n", sndbuf);	
	return 0;
}