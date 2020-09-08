#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
void *thread_function(void *arg);

char message [] = "Hello world";

int main(){
	int res;
	pthread_t a_thread;
	void *thread_result;
	res = pthread_create(&a_thread, NULL, thread_function, (void *)message);
	if(res != 0)
	{
	perror("Thread creation failed!");
	exit(EXIT_FAILURE);
	}
	sleep(5);
	printf("Waiting for thread to finish..\n");
	res = pthread_join(a_thread, &thread_result);
	if(res != 0)
	{
	perror("Thread join failed");
	exit(EXIT_FAILURE);
	}

	printf("Thread joined, it returned %s\n", (char *)thread_result);
	printf("Message is onw %s\n", message);
	exit(EXIT_SUCCESS);
}

void *thread_function(void *arg)
{
	printf("thread function is running. Argument was %s\n", (char *)arg);
	sleep(3);
	printf("i'm here");
	strcpy(message, "Bye PICT");
//	pthread_exit("Thank you for the CPU");
}


