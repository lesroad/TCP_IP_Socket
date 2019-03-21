#include <stdio.h>
#include <arpa/inet.h>
#include <algorithm>
#include <cstring>
#include <unistd.h>
using namespace std;

int main(int argc, char **argv)
{
   

    int ser_sock, cli_sock;
    ser_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(ser_sock == -1)
        puts("socket error");

    int opt = 1;
    setsockopt(ser_sock, SOL_SOCKET, SO_REUSEADDR, &opt, 4);
    sockaddr_in ser_addr, cli_addr;
    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    ser_addr.sin_port = htons(atoi(argv[1]));
    if(bind(ser_sock, (sockaddr *)&ser_addr, sizeof(ser_addr)) != 0)
        puts("bind error");

    if(listen(ser_sock, 5) != 0)
        puts("listen error");

    char s[100];
    socklen_t c_len = sizeof(cli_addr);
    cli_sock = accept(ser_sock, (sockaddr *)&cli_addr, &c_len);
    int len = read(cli_sock, s, 60);
    printf("len = %d\n", len);
    write(cli_sock, s, 50);
    close(cli_sock);
    close(ser_sock);
 
    return 0;
}
