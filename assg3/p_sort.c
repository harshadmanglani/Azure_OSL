#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Function to swap 2 integers
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
// A function to implement bubble sort
void bubbleSort(int arr[], int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)

       // Last i elements are already in place
       for (j = 0; j < n-i-1; j++)
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);
}

// Function to print an array
void printarray(int arr[])
{
	int i=0;
	printf("The Array is : \n");
	while(i<10){
		printf("%d\t", arr[i]);
		i++;
	}
}

// Convert int array to a string
void converttostr(int nums[],int tofind, char* buffer)
{
	// char buffer[100];
	sprintf(buffer, "%d %d %d %d %d %d %d %d %d %d %d",tofind, nums[0], nums[1], nums[2], nums[3], nums[4], nums[5], nums[6], nums[7], nums[8], nums[9] );
}


int main(int argc, char *argv[])
{
	int nums[10];
	char buffer[100];
	int tofind;

	printf("Enter 10 numbers in any order : \n");
	int i=10;
	while(i--){
		scanf("%d", &nums[i]);
	}
	printf("\nEnter number to find : \n");
	scanf("%d", &tofind);
	// printf("Sorting by bubble sort : \n");
	// bubbleSort(nums, 10);
	// printarray(nums);

	pid_t cpid;
	cpid = fork();

    switch(cpid)
	{
		case -1: //
			perror("Fork Executed");
			exit(EXIT_FAILURE);
		case 0: //Child
			printf("\n Child Process . . . . .\n");
			sleep(5);
			 //Convert array to string called buffer
			converttostr(nums, tofind, buffer);
			//Call the program with the string as argument
			char *const ps_argv[] = {"./bin_search", buffer, 0};
			// The path of the program and the character array of the arguments
			execv("~/OSL/assg3/bin_search", ps_argv);
			break;
		default: //Parent
			printf("\n Parent Process . . . . . .\n");
			printf("Sorting by bubble sort : \n");
			bubbleSort(nums, 10);
			wait(NULL);
			printarray(nums);
			break;
	}
}
