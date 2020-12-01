#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
sem_t writer; // To guard critical_section
pthread_mutex_t mutex; // To guard read_count
int read_count = 0, critical_section;
void readerFunc(void *arg)
{
    int i = (int*) arg;
    while(1)
    {
        sleep(1);
        printf("Reader %d is waiting to read...\n",i );
        pthread_mutex_lock(&mutex);
        read_count++;
        if (read_count == 1)
        {
        sem_wait(&writer);
        }
        pthread_mutex_unlock(&mutex);
        // Starting to reading critical section
        printf("Reader %d read %d.\n",i, critical_section );
        // sleep(rand()%5);
        // Finishing reading
        pthread_mutex_lock(&mutex);
        read_count--;
        // printf("Readcount: %d\n", read_count);
        if (read_count == 0)
        {
        sem_post(&writer);
        }
        pthread_mutex_unlock(&mutex);
        printf("Reader %d has finished\n",i );
    }
}
void writerFunc(void *arg)
{

    int i = (int*) arg;
    while(1)
    {
        printf("Writer %d is waiting to write...\n", i);
        sleep(1);
        sem_wait(&writer);
        printf("Writer %d changed critical_section from %d to %d.\n",i,

        critical_section, critical_section + 1);
        critical_section++;
        // sleep(rand()%6);
        sem_post(&writer);
        printf("Writer %d has written.\n", i);
    }
}

int main()
{
    int rdr, wrtr, res;
    // Initializing the write semaphore
    res = sem_init(&writer, 0, 1);
    if (res != 0) {
    perror("Empty semaphore initialization failed");
    exit(EXIT_FAILURE);
    }
    // Initializing the mutex
    res = pthread_mutex_init(&mutex, NULL);
    if (res != 0) {
    perror("Mutex initialization failed");
    exit(EXIT_FAILURE);
    }
    // Getting num of readers and writers
    printf("\nEnter the number of readers :");
    scanf("%d", &rdr);
    printf("\nEnter the number of writers :");
    scanf("%d", &wrtr);
    // Declaring the reader and writer threads
    pthread_t rdr_thread[rdr];
    pthread_t wrtr_thread[wrtr];
    // Creating rdr reader threads
    for (int i = 0; i < rdr; ++i)
    {
        res = pthread_create(&rdr_thread[i], NULL, readerFunc, (void *)i);
        if (res != 0) 
        {
            perror("Reader thread creation failed");
            exit(EXIT_FAILURE);
        }
    }
    // Creating wrtr writer threads
    for (int i = 0; i < wrtr; ++i)
    {
        res = pthread_create(&wrtr_thread[i], NULL, writerFunc, (void *)i);
        if (res != 0) {
        perror("Writer thread creation failed");
        exit(EXIT_FAILURE);
        }
    }
    // Joining rdr reader threads
    for (int i = 0; i < rdr; ++i)
    {
        res = pthread_join(&rdr_thread[i], NULL);
        if (res != 0) {
        perror("Reader thread join failed");
        exit(EXIT_FAILURE);
        }
    }
    // Joining wrtr writer threads
    for (int i = 0; i < wrtr; ++i)
    {
        res = pthread_join(&wrtr_thread[i], NULL);
        if (res != 0) {
        perror("Writer thread join failed");
        exit(EXIT_FAILURE);
        }
    }
return 0;
}