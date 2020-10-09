#include<stdio.h>
#include<stdlib.h> 
#include <unistd.h>
#include<pthread.h>
#include<semaphore.h>
#define pmax 5

enum 
{HUNGRY,THINKING,EATING}
state[pmax];

sem_t m;
sem_t philosopher[5];

void test( int pno)
{
  if(state[pno] == HUNGRY && state[(pno+4)%5]!= EATING && state[(pno+1)%5]!= EATING )

  {  
    state[pno] = EATING;
    sleep(2);
    printf("\n-----------------------------------------------------\n");
    printf("Philosopher %d is EATING with fork %d and %d \n", pno,(pno+4)%5,(pno+1)%5);
    printf("\n-----------------------------------------------------\n");
    sem_post(&philosopher[pno]);
  }  
}

void pickup(int pno)
{
  printf("\nPhilosopher %d wants to EAT\n",pno );
  sem_wait(&m);
  state[pno] = HUNGRY;
  test(pno);
  sem_post(&m);
  // if unable to eat wait to be signalled
  if(state[pno] != EATING)
    sem_wait(&philosopher[pno]);
  sleep(1);
}

void putdown(int pno)
{
  sem_wait(&m);
  state[pno] = THINKING;

  printf("\nPhilosopher %d has finished EATING\n",pno);
  printf("Philosopher %d is THINKING\n",pno);
  printf("\n=====================================================\n");
  // test left and right neighbours
  test((pno+4)%pmax); //lefpnot
  test((pno+1)%pmax); //right
  sem_post(&m);
}
void *philosopherfn(void *arg)
{
  while(1)
  {
    int phil = *(int*) arg;
    sleep(1);
    pickup(phil);
    putdown(phil);
  }
}
int main(){
    pthread_t thr[pmax];
    int i;
    sem_init(&m,0,1);
    //init chops
    for(i = 0; i < pmax; i++)
    {
        sem_init(&philosopher[i], 0, 0);
    }


    for(i = 0; i < pmax; i++)
    {
        pthread_create(&thr[i], NULL, philosopherfn, &i);
        sleep(1);
    }
    for(i = 0; i < pmax; i++){
        pthread_join(thr[i], NULL);
        sleep(1);
    }
    return 0;
}