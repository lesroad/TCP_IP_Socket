#include <stdio.h>
#include <signal.h>//sigaction
#include <unistd.h>//fosk, sleep
#include <sys/wait.h>//waitpid
using namespace std;
void get_child_pid(int sig) //信号处理函数
{
	if(sig == SIGCHLD)
	{
		int state;
		pid_t pid = waitpid(-1, &state, WNOHANG);
		if(WIFEXITED(state))
		{
			printf("child process pid %d, send %d\n", pid, WEXITSTATUS(state));
		}
	}
}
int main(int argc, char **argv)
{
	struct sigaction act;
	act.sa_handler = get_child_pid;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGCHLD, &act, 0);//信号注册函数

	pid_t pid = fork();
	if(pid == 0)
	{
		sleep(10);
		return 9;
	}
	else
	{
		printf("one child pid = %d\n", pid);
		sleep(2);
		pid = fork();
		if(pid == 0)
		{
			sleep(10);
			return 18;
		}
		else
		{
			printf("two child pid = %d\n", pid);
			for(int i = 0; i < 5; i++)
			{
				puts("wait...");
				sleep(5);
			}
		}
	}
	return 0;
}