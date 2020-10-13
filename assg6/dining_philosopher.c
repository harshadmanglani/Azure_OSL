#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
sem_t chopstick[10]; // To guard chopsticks
int read_count = 0, critical_section, chop;

void philFuncAsymm(void *arg)
{
	int i = (int*) arg;
	// printf("%d\n", i);
	while(1)
	{
		sleep(1);
		printf("-----------\nPhilosopher %d is waiting to eat...\n-------------\n",i );
		// printf("%d -> %d : %d\n",i, chopstick[i], chopstick[(i+1)%chop] );
		sem_wait(&chopstick[i]);
		sem_wait(&chopstick[(i+1)%chop]);
		// Starting to reading critical section
		printf("------------\nPhilosopher %d is eating with %d & %d.\n--------------\n",i, i, (i+1)%chop );
		sleep(1);
		sem_post(&chopstick[i]);
		sem_post(&chopstick[(i+1)%chop]);
		printf("--------------\nPhilosopher %d has eaten\n--------------\n",i );

		printf("--------------\nPhilosopher %d is thinking\n--------------\n",i );
		sleep(2);	// Thinking
		// printf("--------------\nPhilosopher %d has finished thinking\n--------------\n",i );
	}
	
}

void philosopherFunc(void *arg)
{
	int i = (int*) arg;
	// printf("%d\n", i);
	while(1)
	{
		sleep(1);
		printf("--------------\nPhilosopher %d is waiting to eat\n--------------\n",i );
		// printf("%d -> %d : %d\n",i, chopstick[i], chopstick[(i+1)%chop] );

		if(i%2)	// L chopstick then R chopstick
		{
			sem_wait(&chopstick[i]);
			sem_wait(&chopstick[(i+1)%chop]);
			// Starting to reading critical section
			printf("--------------\nPhilosopher %d is eating with %d & %d.\n--------------\n",i, i, (i+1)%chop );
			sleep(1);
			sem_post(&chopstick[i]);
			sem_post(&chopstick[(i+1)%chop]);
			printf("--------------\nPhilosopher %d has eaten\n--------------\n",i );
		}
		else	// R chopstick then L chopstick
		{
			sem_wait(&chopstick[(i+1)%chop]);
			sem_wait(&chopstick[i]);
			// Starting to reading critical section
			printf("--------------\nPhilosopher %d is eating with %d & %d.\n--------------\n",i, i, (i+1)%chop );
			sleep(1);
			sem_post(&chopstick[(i+1)%chop]);
			sem_post(&chopstick[i]);
			printf("--------------\nPhilosopher %d has eaten\n--------------\n",i );
		}

		printf("--------------\nPhilosopher %d is thinking\n--------------\n",i );
		sleep(3);	// Thinking
		// printf("--------------\nPhilosopher %d has finished thinking\n--------------\n",i );
	}
	
}


int main()
{
	int phil, res; //, chop

	// Getting num of philosophers and writers
	printf("Enter the no. of philosophers: ");
	scanf("%d", &phil);
	printf("\nEnter the no. of chopsticks: ");
	scanf("%d", &chop);
	// chopstick = (sem_t*)malloc(chop);
	for (int i = 0; i < chop; ++i)
	{
		res = sem_init(&chopstick[i], 0, 1);
		if (res != 0) {
			perror("Empty semaphore initialization failed");
			exit(EXIT_FAILURE);
		}
	}
	sleep(2);

	// Declaring the Philosopher threads
	pthread_t phil_thread[phil];

	// Creating Philosopher threads
	for (int i = 0; i < phil; ++i)
	{
		// res = pthread_create(&phil_thread[i], NULL, philFuncAsymm, (void *)i);	// Asymmetric
		res = pthread_create(&phil_thread[i], NULL, philosopherFunc, (void *)i);	//Symmetric
		if (res != 0) {
			perror("Philosopher thread creation failed");
			exit(EXIT_FAILURE);
		}
	}

	// Joining philosopher threads
	for (int i = 0; i < phil; ++i)
	{
		res = pthread_join(&phil_thread[i], NULL);
		if (res != 0) {
			perror("Philosopher thread join failed");
			exit(EXIT_FAILURE);
		}
	}
	return 0;
}