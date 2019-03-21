#include <stdio.h>
#include <signal.h> //signal
#include <unistd.h> //alarm
using namespace std;

void timeout(int sig)
{
	if(sig == SIGALRM) puts("time out!");
	alarm(2);
}
void key(int sig)
{
	if(sig == SIGINT) 
		puts("crtl+c press!");
}
int main(int argc, char **argv)
{
	signal(SIGALRM, timeout);
	signal(SIGINT, key);
	alarm(2);

	for(int i = 0; i < 3; i++)
	{
		puts("wait...");
		sleep(100);
	}
	return 0;
}