#include <stdio.h>

int binarysearch(int sorted_array[], int search, int start, int end)
{
	int mid = (end - start)/2;
	if(search == sorted_array[mid])
	return mid;

	else if(search < sorted_array[mid])
	return binarysearch(sorted_array, search, start, mid);

	else
	return binarysearch(sorted_array, search, mid, end);
}

int* bubbleSort(int unsorted_array[], int size)
{
	int temp;
	for(int i=0; i<size; i++)
		for(int j=i+1; j<size; j++)
			if(unsorted_array[j] < unsorted_array[i])
			{
				temp  = unsorted_array[j];
				unsorted_array[j] = unsorted_array[i];
				unsorted_array[i] = temp;		
			}
	return unsorted_array;
}

void printArray(int array[], int size)
{
	for(int i=0; i<size; i++)
	{
		printf(" %d\t",array[i]);
	}
}

int main(){
	int arr [5];
	int search;
	for(int i=0; i<5; i++)
	scanf("%d", &(arr[i]);
	printArray(arr, 5);
	arr = bubbleSort(arr, 5);
	printArray(arr, 5);
	printf("Enter the element you want to search: ");
	scanf("%d", &search);
	printf("Element is present at: %d\n",binarysearch(arr, search, 0, 5));
	return 0;
}

