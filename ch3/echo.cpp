#include <cstdio>
using namespace std;
void error(char *s)
{
	fputs(s, stderr);
	fputc('\n', stderr);
	puts("1");
	exit(1);
}
int main()
{
	int x = 1;
	if(!x) error("cuowu!");
	return 0;
}
