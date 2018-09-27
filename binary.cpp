#include <stdio.h> 
#include <omp.h>
#include <stdlib.h>
#define SIZE 1000000
void binarySearch(int arr[], int l, int r, int x,int pos) 
{ 
   if (r >= l) 
   { 
        int mid = l + (r - l)/2; 

        #pragma omp task
        {
          //printf("section %d thread no: %d\n",1,omp_get_thread_num());   
              //pos = mid;
              if (arr[mid] == x)
              printf("pos: %d\n",mid);
        } 
        
        #pragma omp task
        {
          //printf("section %d thread no: %d\n",2,omp_get_thread_num()); 
              if (arr[mid] > x) 
              binarySearch(arr, l, mid-1, x,pos);
        } 

        #pragma omp task
        {
          //printf("section %d thread no: %d\n",3,omp_get_thread_num());
            if (arr[mid] < x)
            binarySearch(arr, mid+1, r, x,pos); 
        }
   } 
} 

int binarySearch_ser(int arr[], int l, int r, int x) 
{ 
   if (r >= l) 
   { 
        int mid = l + (r - l)/2; 
  
        if (arr[mid] == x)
          return mid; 
        if (arr[mid] > x) 
              return binarySearch_ser(arr, l, mid-1, x);
        if (arr[mid] < x)
              return binarySearch_ser(arr, mid+1, r, x); 
   } 
   return -1;
} 
  
int main(void) 
{ 
   int arr[SIZE]; //= {2, 3, 4, 10, 40}; 
   int n = sizeof(arr)/ sizeof(arr[0]); 
   int x = 25,pos = -1,result; 
    #pragma omp parallel for
    for (int i = 0; i < SIZE; i++) 
    {
       arr[i]=i+1;
    }
/*    for (int i = 0; i < SIZE; i++) 
    {
       printf("%d\n",arr[i]);;
    }*/
    omp_set_num_threads(2);
    double start = omp_get_wtime(); 
   #pragma omp parallel 
   {
      #pragma omp single
      {
        //printf("no of threads: %d\n",omp_get_num_threads());
        binarySearch(arr, 0, n-1, x,pos); 
      }
   }
    double end = omp_get_wtime();
    long double elapsed=end-start;
    printf("\nTime requried for parallel is %Lf \n",elapsed); 
  // printf("position: %d\n",pos);

    start = omp_get_wtime();
    result = binarySearch_ser(arr,0,n-1,x);
    end = omp_get_wtime(); 
   (result == -1)? printf("Element is not present in array") 
                 : printf("Element is present at index %d\n", 
                                                   result); 
    elapsed=end-start;
    printf("\nTime requried for serial is %Lf \n",elapsed);
   return 0; 
} 
