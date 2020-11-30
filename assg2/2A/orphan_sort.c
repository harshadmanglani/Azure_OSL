#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define sz 5

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

// A function to implement selection sort 
void selectionSort(int arr[], int n) 
{ 
    int i, j, min_idx; 
  
    // One by one move boundary of unsorted subarray 
    for (i = 0; i < n-1; i++) 
    { 
        // Find the minimum element in unsorted array 
        min_idx = i; 
        for (j = i+1; j < n; j++) 
          if (arr[j] < arr[min_idx]) 
            min_idx = j; 
  
        // Swap the found minimum element with the first element 
        swap(&arr[min_idx], &arr[i]); 
    } 
}

void printarray(int arr[])
{
	int i=0;
	printf("The Array is : \n");
	while(i<sz){
		printf("%d\t", arr[i]);
		i++;
	}
}

int main(int argc, char *argv[])
{
	int nums[sz];
	printf("Enter sz numbers in any order : \n");
	int i=sz;
	while(i--){
		scanf("%d", &nums[i]);
	}
	pid_t cpid;
	cpid = fork();
	if (cpid == -1) {
   		perror("fork");
  		exit(EXIT_FAILURE);
	}
	else if (cpid == 0) {    /* Child reads from pipe */
	printf("Sorting by bubble sort : \n");
		bubbleSort(nums, sz);
		printarray(nums);
		
		printf("\n Child Process . . . . .\n");
		printf("Child ID: %d\n", getpid());
		printf("Parent ID: %d\n", getppid());
		// sleep(sz);
		printf("Child ID: %d\n", getpid());
		printf("Parent ID: %d\n", getppid());
               
       } else {            /* Parent writes argv[1] to pipe */
       	printf("Sorting by selection sort : \n");
       	selectionSort(nums, sz);
       	printarray(nums);
       	// sleep(2);
       printf("\n Parent Process . . . . . .\n");
        
       }
}