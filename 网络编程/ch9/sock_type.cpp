#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;
int main(int argc, char **argv)
{
	printf("tcp_type = %d\nudp_type = %d\n", SOCK_STREAM, SOCK_DGRAM);
	int tcp_sock, udp_sock;
	tcp_sock = socket(PF_INET, SOCK_STREAM, 0);
	udp_sock = socket(PF_INET, SOCK_DGRAM, 0);
	int sock_type;
	socklen_t optlen = sizeof(sock_type);
	int state = getsockopt(tcp_sock, SOL_SOCKET, SO_TYPE, &sock_type, &optlen);
	if(state) puts("getsockopt 1 error!");
	printf("sock one:%d\n", sock_type);
	state = getsockopt(udp_sock, SOL_SOCKET, SO_TYPE, &sock_type, &optlen);
	if(state) puts("getsockopt 2 error");	
	printf("sock two:%d\n", sock_type);
	return 0;
}