//p109  
//read write不会将字符串末尾设为'\0'
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <cstdlib>
using namespace std;
int main(int argc, char **argv)
{
	int sock, your_sock;
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1) puts("host1_1 error");
	sockaddr_in my_addr, your_addr;
	memset(&my_addr, 0, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	my_addr.sin_port = htons(atoi(argv[1]));
	if(bind(sock, (sockaddr *)&my_addr, sizeof(my_addr)) == -1)
		puts("host1_2error");
	listen(sock, 5);
	socklen_t len = sizeof(your_addr);
	your_sock = accept(sock, (sockaddr *)&your_addr, &len);
	for(int i = 0; i < 3; i++)
	{
		char s[20];
		int cnt = 0, n;
		read(your_sock, &n, 4);
		cout<<"n的值："<<n<<endl;	
		while(cnt < n)
		{
			int ll = read(your_sock, &s[cnt], n);
			cnt += ll;
		}
		s[n] = 0;
		printf("message %d : %s, cnt = %d\n", i+1, s, cnt);
	}
	close(sock);
	close(your_sock);
	return 0;
} 
