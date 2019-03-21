#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <stdio.h>
#include <cstdlib>
const int N = 1024;
using namespace std;
int main(int argc, char **argv)
{
        int cli_sock, n, x;
        char s[N]; 
        cli_sock = socket(PF_INET, SOCK_STREAM, 0);
        if(cli_sock == -1) puts("cli_1 error");
        sockaddr_in ser_addr;
        memset(&ser_addr, 0, sizeof(ser_addr));
        ser_addr.sin_family = AF_INET;
        ser_addr.sin_addr.s_addr = inet_addr(argv[1]);
        ser_addr.sin_port = htons(atoi(argv[2]));
        if(connect(cli_sock, (sockaddr *)&ser_addr, sizeof(ser_addr)) == -1)
                puts("cli_2 error");
        puts("请输入个数");
        cin>>n;
        write(cli_sock, &n, 4);
        printf("请输入%d个数\n", n);
        for(int i = 0; i < n; i++)
        {
                printf("请输入第%d个数: ", i+1);
                scanf("%d", &x);
		write(cli_sock, &x, 4);
        }
        int ans;
        read(cli_sock, &ans, 4);
        printf("结果为%d\n", ans);
        close(cli_sock);
        return 0;
}

