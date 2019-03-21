#include <stdio.h>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>
using namespace std;
int main(int argc, char **argv)
{
        int sock;
        sockaddr_in your_addr;
        sock = socket(PF_INET, SOCK_STREAM, 0);
        if(sock == -1) puts("host2 1 error");
        memset(&your_addr, 0, sizeof(your_addr));
        your_addr.sin_family = AF_INET;
        your_addr.sin_addr.s_addr = inet_addr(argv[1]);
        your_addr.sin_port = htons(atoi(argv[2]));
        char s1[] = "hello! lesroad!";
        char s2[] = "GO time!";
        char s3[] = "Goodbye.";
	connect(sock, (sockaddr *)&your_addr, sizeof(your_addr));
	int l1 = strlen(s1); 
	int l2 = strlen(s2);
	int l3 = strlen(s3); 
	printf("l1 = %d, l2 = %d, l3 = %d\n", l1, l2, l3);
	write(sock, &l1, 4);
	write(sock, s1, l1);
	write(sock, &l2, 4);
	write(sock, s2, l2);
	write(sock, &l3, 4);
	write(sock, s3, l3);
        close(sock);
        return 0;
}
                                                                                                                                                 
                                                                                                                                                 
 
