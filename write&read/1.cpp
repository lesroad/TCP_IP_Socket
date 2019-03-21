#include <stdio.h>
#include <arpa/inet.h>
#include <algorithm>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

int main(int argc, char **argv)
{
 	char s[100] = "lesroad", ss[100];
 	int fd = open("1.txt", O_CREAT | O_RDWR, 0777);
 	// int fd1 = dup(fd);
 	write(fd, s, strlen(s));
 	// close(fd1);
 	//lseek(fd, 0, SEEK_SET);
 	int l = read(fd, ss, 100);
 	puts(ss);
 	printf("%d\n", l);
 	close(fd);
    return 0;
}
