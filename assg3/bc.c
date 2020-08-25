#include <stdio.h>
#include <stdlib.h>

int binarySearch(int arr[], int l, int r, int x) 
{ 
    if (r >= l) { 
        int mid = l + (r - l) / 2; 
        if (arr[mid] == x) 
            return mid; 

        if (arr[mid] > x) 
            return binarySearch(arr, l, mid - 1, x); 

        return binarySearch(arr, mid + 1, r, x); 
    }
    return -1; 
}

int main(int argc, char const *argv[]) 
{
    int i;
    int nums[10];
    int tofind;
    // Convert string to int array
    sscanf( argv[1], "%d %d %d %d %d %d %d %d %d %d %d",&tofind, &nums[0], &nums[1], &nums[2], &nums[3], &nums[4], &nums[5], &nums[6], &nums[7], &nums[8], &nums[9]);
    i=0;
    int n = sizeof(nums) / sizeof(nums[0]); 
    int result = binarySearch(nums, 0, n - 1, tofind); 
    (result == -1) ? printf("Element is not present in array\n") : printf("Element is present at index %d\n", result);
    return 0; 
} 