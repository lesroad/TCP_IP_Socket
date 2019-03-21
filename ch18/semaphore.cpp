#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
using namespace std;
int x,sum = 0;
sem_t sem1, sem2;
void *main1(void *arg)
{
	puts("请输入5个数");
	for(int i = 0; i < 5; i++)
	{
		sem_wait(&sem1);
		scanf("%d", &x);
		sem_post(&sem2);
	}
}
void *main2(void *arg)
{
	for(int i = 0; i < 5; i++)
	{
		sem_wait(&sem2);
		sum += x;
		sem_post(&sem1);
	}
}
int main()
{
	pthread_t id1, id2;

	sem_init(&sem1, 0, 1);
	sem_init(&sem2, 0, 0);

	pthread_create(&id1, NULL, main1, NULL);
	pthread_create(&id2, NULL, main2, NULL);

	pthread_join(id1, NULL);
	pthread_join(id2, NULL);

	printf("和为%d\n", sum);

	sem_destroy(&sem1);
	sem_destroy(&sem2);

	pthread_detach(id1);
	pthread_detach(id2);
	return 0;
}