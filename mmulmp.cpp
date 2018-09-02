#include<iostream>
#include<omp.h>
#include<time.h>
using namespace std;

#define NRA 62               
#define NCA 15                 
#define NCB 7                  

int main () 
{
  double start_time = clock();
  int i, j, k, chunk;
  double	a[NRA][NCA],b[NCA][NCB],c[NRA][NCB];        

  chunk = 10;                    /* set loop iteration chunk size */


  #pragma omp parallel shared(a,b,c,chunk) private(i,j,k)
  {

    /*** Initialize matrices ***/
    #pragma omp for schedule (static, chunk) 
    for (i=0; i<NRA; i++)
      for (j=0; j<NCA; j++)
        a[i][j]= i+j;
    #pragma omp for schedule (static, chunk)
    for (i=0; i<NCA; i++)
      for (j=0; j<NCB; j++)
        b[i][j]= i*j;
    #pragma omp for schedule (static, chunk)
    for (i=0; i<NRA; i++)
      for (j=0; j<NCB; j++)
        c[i][j]= 0;

    #pragma omp for schedule (static, chunk)
    for (i=0; i<NRA; i++)    
      {
        for(j=0; j<NCB; j++)       
          for (k=0; k<NCA; k++)
            c[i][j] += a[i][k] * b[k][j];
      }
  }   /*** End of parallel region ***/

  /*** Print results ***/
  cout<<"Result Matrix:\n";
  for (i=0; i<NRA; i++)
    {
      for (j=0; j<NCB; j++) 
        cout<<c[i][j]<<"\t";
      cout<<"\n"; 
    }

  double end_time = clock();
  double result_time = (end_time - start_time) / CLOCKS_PER_SEC;
  cout<<"\n"<<result_time;
  return 0;
}
