#include <signal.h>
#include <stdio.h>
#include <unistd.h> //alarm
using namespace std;
void timeout(int sig)
{
    if(sig == SIGALRM)
    {
        puts("alarm!");
        alarm(2);
    }
}
int main(int argc, char **argv)
{
    struct sigaction act;
    act.sa_handler = timeout;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGALRM, &act, 0);
    alarm(2);
    for(int i = 0; i < 3; i++)
    {
        puts("wait...");
        sleep(100);
    }
    return 0;
}
