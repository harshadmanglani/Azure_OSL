#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#define max 10
#include <time.h>


void *thread_function(void *arg);
void get_matrix(int a[max][max],int m, int n);
void print_matrix(int a[max][max],int m, int n);

char message[] = "Hello World";

struct data
{
	int a[max][max] ,b[max][max] ,c[max][max], i, j, loop;
};

int main() {
	int res;
	// struct data *d = malloc(1);
	struct data d[1];
	int r1,c1,r2,c2,i,j,option=0;

	clock_t start, end;
    double cpu_time_used;

	printf("Enter the number of rows and columns of the first matrix\n");
	scanf("%d %d",&r1,&c1);
	printf("Enter the number of rows and columns of the second matrix\n");
	scanf("%d %d",&r2,&c2);
	while(c1 != r2)
	{
		printf("Invalid size. Re-enter\n");
		printf("Enter the number of rows and columns of the first matrix\n");
		scanf("%d %d",&r1,&c1);
		printf("Enter the number of rows and columns of the second matrix\n");
		scanf("%d %d",&r2,&c2);
	}
	for(i=0;i<r1;i++)
	{
		for (j=0;j<c2;j++)
		{
			d->c[i][j] = 0;
		}
	}
	print_matrix(d->c, r1, c2);

	printf("Enter the first matrix:\n");
	get_matrix(d->a,r1,c1);
	printf("Enter the second matrix:\n");
	get_matrix(d->b,r2,c2);


	// pthread_t a_thread;
	// pthread_t *thread = malloc(9);
	pthread_t thread[r1*c2];
	void *thread_result;
	d->loop = c1;
	for ( i = 0; i < r1; ++i)
	{
		for (int j = 0; j < c2; ++j)
		{
			d->i = i;
			d->j = j;
			// printf("%d, %d\n",d->i, d->j );
			res = pthread_create(&thread[(i*r1)+j], NULL, thread_function, (void *)d);
			if (res != 0) {
				perror("Thread creation failed");
				exit(EXIT_FAILURE);
			}
			// sleep(1);
		}
	}

	// sleep(1);
	start = clock();
	for ( i = r1*c2 - 1; i >= 0; --i)
	{
		printf("Waiting for thread to finish...\n");
		// sleep(1);
		res = pthread_join(thread[i], &thread_result);
		if (res != 0) {
			perror("Thread join failed");
			exit(EXIT_FAILURE);
		}
		printf("%d Thread joined, it returned %s\n",i, (char *)thread_result);
	}
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("fun() took %f seconds to execute \n", cpu_time_used);

	print_matrix(d->c, r1, c2);
	exit(EXIT_SUCCESS);
}
void *thread_function(void *arg) {
	// sleep(3);
	struct data *temp = (struct data *)arg;
	int k = 0,i=temp->i, j=temp->j;

	printf("%d, %d\n",i,j );
	for(k=0;k<temp->loop;k++)
	{
		temp->c[i][j] += temp->b[k][j] * temp->a[i][k];
	}
	printf("%d, %d\n",i,j );
	// strcpy(message, "Bye!");
	// sleep(4);
	pthread_exit("Thank you for the CPU time");


}
void get_matrix(int (*a)[max],int m, int n)
{
	int i,j;
	for(i=0;i<m;i++)
	{
		for (j=0;j<n;j++)
		{
			printf("\nEnter element %d,%d :",i+1,j+1);
			scanf("%d",&a[i][j]);
		}
	}
}
void print_matrix(int a[max][max],int m, int n)
{
	int i,j;
	printf("\n");
	for(i=0;i<m;i++)
	{
		printf("| ");
		for (j=0;j<n;j++)
		{
			printf("%d",a[i][j]);
			if(j!=n-1)
				printf("\t");
		}
		printf(" |\n");
	}
}
