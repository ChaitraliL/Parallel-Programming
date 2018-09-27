#include<omp.h>
#include<stdlib.h> 
#include<stdio.h> 
#include<math.h> 
#define SIZE 10000
void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    int L[n1], R[n2]; 
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  
void mergeSort(int arr[], int l, int r) 
{ 
    if (l < r) 
    { 
        int m = l+(r-l)/2; 
             #pragma omp task 
             {
/*                 int tid=omp_get_thread_num();
                 printf("\nTid Section 1: %d,",tid);*/
                 mergeSort(arr, l, m);
             }
             #pragma omp task 
             { 
/*                 int tid=omp_get_thread_num();
                 printf("\nTid Section 2: %d,",tid);*/
                 mergeSort(arr, m+1, r); 
             }
             #pragma omp taskwait //explicit barrier   
        merge(arr, l, m, r); 
    }
} 

void mergeSort_ser(int arr[], int l, int r) 
{ 
    if (l < r) 
    { 
        int m = l+(r-l)/2; 
        mergeSort_ser(arr, l, m);
        mergeSort_ser(arr, m+1, r);   
        merge(arr, l, m, r); 
   } 
}

void printArray(int A[], int size) 
{ 
    int i; 
    for (i=0; i < size; i++) 
        printf("%d \n", A[i]); 
    printf("\n"); 
} 
  
int main() 
{ 
    omp_set_num_threads(2); // if thread no is increased it increases the time due to more context switching 

    int arr[SIZE]; //= {12, 11, 13, 5, 6, 7}; 
    #pragma omp parallel for
    for (int i = 0; i < SIZE; i++) 
    {
       arr[i]=(int)(rand()*100);
    }
    int arr_size = sizeof(arr)/sizeof(arr[0]); 
    
    double start = omp_get_wtime(); 
    #pragma omp parallel
    {
        #pragma omp single
        {
            mergeSort(arr, 0, arr_size - 1);
        }
    }
    double end = omp_get_wtime();  

/*    printf("\nSorted array is \n"); 
    printArray(arr, arr_size);*/

    double elapsed=end-start;
    printf("\nTime requried for parallel is %f \n",elapsed); 
     
    start = omp_get_wtime(); 
    mergeSort_ser(arr, 0, arr_size - 1); 
    end = omp_get_wtime(); 

/*    printf("\nSorted array is \n"); 
    printArray(arr, arr_size);*/

    elapsed=end-start;
    printf("\nTime requried for serial is %f \n",elapsed);

    return 0; 
} 