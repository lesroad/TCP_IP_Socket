//p46
#include <stdio.h>
#include <arpa/inet.h>
using namespace std;
int main()
{
	char ip[2][20] = {"1.2.3.4", "1.2.3.256"};
	for(int i = 0; i < 2; i++)
	{
		int num = inet_addr(ip[i]);	
		if(num == INADDR_NONE)
			puts("错误地址！");
		else
			printf("%#x\n", num);
	}
	return 0;
}
