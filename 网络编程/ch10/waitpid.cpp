#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> //waitpid
using namespace std;
int main(int argc, char **argv)
{
	pid_t pid = fork();
	if(pid == 0)
	{
		sleep(10);
		puts("child process");
		return 5;
	}
	else 
	{
		printf("child id = %d\n", pid);
		int state;
		while(!waitpid(-1, &state, WNOHANG));//等到有子进程结束时才会执行下一行，不会阻塞
		if(WIFEXITED(state))
			printf("child send %d\n", WEXITSTATUS(state));
		sleep(20);
	}
	return 0;
}