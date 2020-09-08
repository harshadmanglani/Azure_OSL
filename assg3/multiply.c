#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

void printr2(){
	printf("Enter the number of rows in the second matrix (max 10): \n");
}
void printc2(){
	printf("Enter the number of columns in the second matrix (max 10): \n");
}
void printr1(){
	printf("Enter the number of rows in the first matrix (max 10): \n");
}
void printc1(){
	printf("Enter the number of columns in the first matrix (max 10): \n");
}
void printb(){
	printf("Enter the elements of the second matrix: \n");
}
void printa(){
	printf("Enter the elements of the first matrix: \n");
}

void print_menu(){
	printf("\n\n1. Give input\n2. Multiplication with threads\n3. Multiplication without threads\n\n6. Exit\n\n");
}

void print_arr(int arr[10][10], int r, int c){
	for(int i=0;i<r;i++)
		{
			for(int j=0;j<c;j++)
			{	if(j==0 )
				printf("| ");

				if(arr[i][j]<10)printf("0");
				printf("%d ",arr[i][j]);
				if(j==c-1)
							printf(" |");}
			printf("\n     ");
		}
}

struct multiplier{
	int *a;
	int b;
	int c;
};

int input_num(){
	//number of rows/columns
	int n1;
	scanf("%d",&n1);
	return n1;
}

void input_matrix(int a[10][10], int r, int c){			//input function for elements of the matrix

	for(int i=0;i<r;i++)
		for(int j=0;j<c;j++)
		scanf("%d",&a[i][j]);
}


void multiplication(int a[10][10], int b[10][10], int r1, int c1, int r2, int c2){
	clock_t t = clock();
	int arr[10][10];

	for(int i=0;i<r1;i++)
		for(int j=0;j<c2;j++)
			for(int k=0;k<r1;k++)
			{
				arr[i][j]+=a[i][k]*b[k][j];
				//printf("arr[%d][%d] = a[%d][%d]*b[%d][%d]\n",i,j,i,k,k,j);
			}

	t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds

    printf("fun() took %f seconds to execute \n\n\n", time_taken);
		printf("A=   ");
		print_arr(a, r1, c1);
		printf("\nB=   ");
		print_arr(b, r2, c2);
		printf("\nA*B= ");
		print_arr(arr, r1, c2);
		printf("\n");

}

void *thread_function(void *arg){
	struct multiplier *st = arg;
	struct multiplier s = *st;
//	printf("%d %d %d\n",*(s.a), s.b, s.c);
//	sleep(10);
	*(s.a) += (s.b) * (s.c);
	printf("%d %d %d\n",*(s.a), s.b, s.c);
//	sleep(10);
	pthread_exit(NULL);
}

void multiplication_threads(int a[10][10], int b[10][10], int r1, int c1, int r2, int c2){
	clock_t t = clock();
	int arr[10][10];
	pthread_t threads[r1*c2*r1];
	int lots_of_threads = 0;
	int ctr = 0;
	for(int i=0;i<r1;i++)
		for(int j=0;j<c2;j++)
		{
			arr[i][j] = 0;
			for(int k=0;k<r1;k++)
			{
				// arr[i][j]+=a[i][k]*b[k][j];
				struct multiplier temp = {&(arr[i][j]), a[i][k], b[k][j]};
				int res = pthread_create(&(threads[ctr]), NULL, thread_function, (void *)&temp);
				ctr++;
				if(res!=0)
				{
					printf("an error occurred");
					perror("thread creation failed");
					exit(EXIT_FAILURE);
				}
				//printf("arr[%d][%d] = a[%d][%d]*b[%d][%d]\n",i,j,i,k,k,j);
			}
		}

	 for(lots_of_threads =0; lots_of_threads < r1*c2*r1; lots_of_threads++)
        {
                int res = pthread_join(threads[lots_of_threads], NULL);
                if(res == 0)
				;
                        // printf("Picked up a thread\n");
                else
                        printf("pthread_join failed");
        }
		t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    printf("fun() took %f seconds to execute \n\n\n", time_taken);

		printf("A=   ");
		print_arr(a, r1, c1);
		printf("\nB=   ");
		print_arr(b, r2, c2);
		printf("\nA*B= ");
		print_arr(arr, r1, c2);
		printf("\n");
}



int main(void) {

	int c=0, r1=10, c1=10, r2=10, c2=10;
	int a[10][10], b[10][10];

	for(int i=0;i<10;i++)
	for(int j=0;j<10;j++){
		a[i][j]=0;
		b[i][j]=0;
	}

	while(c!=6){
			print_menu();
		scanf("%d", &c);
		switch(c) {
		case 1:{
			printr1();
			r1=input_num();
			printc1();
			c1=input_num();
			printr2();
			r2=input_num();
			printc2();
			c2=input_num();

			printa();
			input_matrix(a, r1, c1);
			printb();
			input_matrix(b, r2, c2);
			break;
				}

		case 2:{
			if(c1!=r2)
				printf("Performing the operation isn't possible since matrix parameters are invalid.\n");
			else{
				multiplication_threads(a, b, r1, c1, r2, c2);
			}
			break;
		}


		case 3:{
			if(c1!=r2)
				printf("Performing the operation isn't possible since matrix parameters are invalid.\n");
			else{
				multiplication(a, b, r1, c1, r2, c2);
			}
			break;
		}

		case 6:break;

		default: printf("Invalid choice.\n");
					c=0;
	}
 }
	return EXIT_SUCCESS;
}
