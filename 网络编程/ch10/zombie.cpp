#include <stdio.h>
#include <unistd.h>//fork、sleep
using namespace std;
int main(int argc, char **argv)
{
	pid_t pid = fork();
	if(pid == 0)
	{
		puts("child process");
	}
	else
	{
		printf("father process, child id = %d\n", pid);
		sleep(30);
	}
	return 0;
}