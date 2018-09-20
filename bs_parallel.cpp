#include <stdio.h> 
#include <stdlib.h> 
#include <omp.h>
#define size 100 
int binarySearch(int arr[], int l, int r, int x) 
{ 
    while (l <= r) 
    { 
        int m = l + (r-l)/2; 
  
        // Check if x is present at mid 
        if (arr[m] == x) 
            return m; 
  
        // If x greater, ignore left half 
        if (arr[m] < x) 
            l = m + 1; 
  
        // If x is smaller, ignore right half 
        else
            r = m - 1; 
    } 
  
    // if we reach here, then element was 
    // not present 
    return -1; 
} 
  
int main(void) 
{ 
    int arr[size]; 
    for(int i = 1 ; i < size; i++)
    {
    	arr[i] = rand();
    } 
    arr[0] = 10;
    int n = sizeof(arr)/ sizeof(arr[0]); 
    int x = 10; 
    int tn,chunksize;
    
    double start = omp_get_wtime();
    #pragma omp parallel
    {
    	int from,to;
    	tn = omp_get_num_threads();
    	chunksize = n / tn,from = omp_get_thread_num()*chunksize,to = from + chunksize;
    	printf("%d\t%d\n",omp_get_thread_num(),binarySearch(arr,from,to-1,x));
    }
    printf("Time: \t %f \n", omp_get_wtime()-start);
    
    double starts = omp_get_wtime();
    int result = binarySearch(arr, 0, n-1, x); 
    (result == -1)? printf("Element is not present"
                                       " in array") 
               : printf("Element is present at "
                                "index %d", result); 
    printf("Time: \t %f \n", omp_get_wtime()-starts);
    return 0; 
} 
