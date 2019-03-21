//p46
#include <stdio.h>
#include <arpa/inet.h>
using namespace std;
int main()
{
    unsigned short host_port = 0x1234;
    unsigned short net_port;
    unsigned long host_addr = 0x12345678;
    unsigned long net_addr;
    
    net_port = htons(host_port);
    net_addr = htonl(host_addr);
    
    printf("%#x->%#x\n", host_port, net_port);
    printf("%#x->%#x\n", host_addr, net_addr); 
    return 0;
}
