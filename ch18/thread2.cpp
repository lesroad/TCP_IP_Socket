#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <unistd.h>
#include <pthread.h>
using namespace std;
void *p_main(void *x)
{
	int n = *((int *)x);
	for(int i = 1; i <= n; i++)
	{
		printf("%d\n", i);
		sleep(1);
	}
	char *str = (char *)malloc(sizeof(char) * 50);
	strcpy(str, "lesroad");
	return (void *)str;
}
int main()
{
	pthread_t id;
	int x = 5;
	void *s;
	pthread_create(&id, NULL, p_main, (void *)&x);
	pthread_join(id, &s);
	printf("%s\n", (char *)s);
	free(s);
	return 0;
}