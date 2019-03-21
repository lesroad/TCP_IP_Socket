#include <stdio.h>
#include <unistd.h>
using namespace std;
int main()
{
	int fds[2];
	char s[] = "hello";
	char s1[20];
	pipe(fds);
	pid_t pid = fork();
	if(pid == 0)
	{
		write(fds[1], s, sizeof(s));
	}
	else
	{
		int len = read(fds[0], s1, 10);
		s1[len] = 0;
		puts(s1);
	}
	return 0;
}