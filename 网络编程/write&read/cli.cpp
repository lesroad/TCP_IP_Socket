#include <arpa/inet.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
using namespace std;
int main(int argc, char **argv)
{
   
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1)
        puts("socket error");

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));
    if(connect(sock, (sockaddr *)&addr, sizeof(addr)) != 0)
        puts("connect error");

    char s[100] = "123456";
    write(sock, s, 100);
    int len = read(sock, s, 55);
    printf("len = %d\n", len);
    s[len] = 0;
    puts(s);
    close(sock);
 
    return 0;
}

