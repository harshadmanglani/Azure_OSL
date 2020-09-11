#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
sem_t empty, full;
pthread_mutex_t mutex;
int in, out, a[10];

void printQueue()
{
	// printf("%d, %d\n", in, out);
	int i;
	if (in == out)
		printf("Empty");
	for (i = out; i != in; i = (i+1)%5)
	{ 
		printf("%d ", a[i]); 
	}
	printf("\n");
}

void producerFunc(void *arg)
{
	int i = (int*) arg;
	while(1)
	{
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		// Critical section start
		// printf("%d\n", i);
		a[in] = rand()%100;
		printf("Producer %d produced %d\n",i,a[in] );
		in = (in+1)%5;
		printQueue();
		// Critical section end
		sem_post(&full);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
	
}

void consumerFunc(void *arg)
{
	int i = (int*) arg;
	while(1)
	{
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		// Critical section start
		// printf("%d\n", i);
		printf("Consumer %d consumed %d\n",i,a[out] );
		a[out] = 0;
		out = (out+1)%5;
		printQueue();
		// Critical section end
		sem_post(&empty);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
	
}


int main()
{
	int num_prod, num_con, res;
	// Initializing the empty semaphore
	res = sem_init(&empty, 0, 5);
	if (res != 0) {
		perror("Empty semaphore initialization failed");
		exit(EXIT_FAILURE);
	}
	// Initializing the full semaphore
	res = sem_init(&full, 0, 0);
	if (res != 0) {
		perror("Full semaphore initialization failed");
		exit(EXIT_FAILURE);
	}
	// Initializing the mutex
	res = pthread_mutex_init(&mutex, NULL);
	if (res != 0) {
		perror("Mutex initialization failed");
		exit(EXIT_FAILURE);
	}
	// Getting num of producers and consumers
	printf("\nEnter the number of producers :");
	scanf("%d", &num_prod);
	printf("\nEnter the number of consumers :");
	scanf("%d", &num_con);

	// Declaring the produer and consumer threads
	pthread_t prod_thread[num_prod];
	pthread_t con_thread[num_con];

	// Creating num_prod producer threads
	for (int i = 0; i < num_prod; ++i)
	{
		res = pthread_create(&prod_thread[i], NULL, producerFunc, (void *)i);
		if (res != 0) {
			perror("Producer thread creation failed");
			exit(EXIT_FAILURE);
		}
	}
	// Creating num_con consumer threads
	for (int i = 0; i < num_con; ++i)
	{
		res = pthread_create(&con_thread[i], NULL, consumerFunc, (void *)i);
		if (res != 0) {
			perror("Consumer thread creation failed");
			exit(EXIT_FAILURE);
		}
	}

	// Joining num_prod producer threads
	for (int i = 0; i < num_prod; ++i)
	{
		res = pthread_join(&prod_thread[i], NULL);
		if (res != 0) {
			perror("Producer thread join failed");
			exit(EXIT_FAILURE);
		}
	}
	// Joining num_con consumer threads
	for (int i = 0; i < num_con; ++i)
	{
		res = pthread_join(&con_thread[i], NULL);
		if (res != 0) {
			perror("Consumer thread join failed");
			exit(EXIT_FAILURE);
		}
	}




	return 0;
}
