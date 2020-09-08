#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
sem_t full,empty;
pthread_mutex_t m;
int count=0,in=0,out=0,a[5];

void *producerfunc(void *ptr)
{
int k=(int*) ptr;
while(1)
{
sem_wait(&empty);
pthread_mutex_lock(&m);
if(count>=5)
printf("\nBuffer is full..");
else
{
a[in]=rand()%100;
printf("\nProducer %d produced item: %d", k, a[in]);
in=(in+1)%5;
count++;
}
pthread_mutex_unlock(&m);
sem_post(&full);
sleep(rand()%10);
}
}

void *consumerfunc(void *ptr)
{
int k=(int *)ptr;
while(1)
{
sem_wait(&full);
pthread_mutex_lock(&m);
if(count<=0)
printf("\nBuffer is empty..");
else{
printf("\nConsumer %d consumed item: %d", k, a[out]);
out=(out+1)%5;
count--;
}
pthread_mutex_unlock(&m);
sem_post(&empty);
sleep(rand()%7);
}
}

int main(int argc, char *argv)
{
int i,p,c;
pthread_t pth[10],cth[10];
pthread_mutex_init(&m,NULL);
sem_init(&full,0,0);
sem_init(&empty,0,0);

printf("\nEnter the number of producers and consumers: ");
scanf("%d%d", &p, &c);

for(i=0;i<p;i++)
pthread_create(&pth[i],NULL,producerfunc,(void *)i);
for(i=0;i<c;i++)
pthread_create(&cth[i],NULL,consumerfunc,(void *)i);
for(i=0;i<p;i++)
pthread_join(pth[i], NULL);
for(i=0;i<c;i++)
pthread_join(cth[i], NULL);

pthread_mutex_destroy(&m);
sem_destroy(&full);
sem_destroy(&empty);
return 0;
}


