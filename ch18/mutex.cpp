#include <stdio.h>
#include <pthread.h>
using namespace std;
pthread_mutex_t mutex;
int n = 0;
void *main1(void *arg)
{
	pthread_mutex_lock(&mutex);
	for(int i = 0; i < 2000000; i++)
		n += 1;
	pthread_mutex_unlock(&mutex);
}
void *main2(void * arg)
{
	pthread_mutex_lock(&mutex);
	for(int i = 0; i < 2000000; i++)
	{
		n -= 1;
	}
	pthread_mutex_unlock(&mutex);
}
int main()
{
	pthread_t id[100];
	pthread_mutex_init(&mutex, NULL);
	for(int i = 0; i < 100; i++)
	{
		if(i & 1)
		{
			pthread_create(&id[i], NULL, main1, NULL);
		}
		else
		{
			pthread_create(&id[i], NULL, main2, NULL);
		}
	}
	for(int i = 0; i < 100; i++)
		pthread_join(id[i], NULL);
	printf("%d\n", n);
	pthread_mutex_destroy(&mutex);
	return 0;
}