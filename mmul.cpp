#include<iostream>
#include<time.h>
using namespace std;

#define NRA 62               
#define NCA 15                 
#define NCB 7                  

int main () 
{
  int i, j, k;
  double	a[NRA][NCA],b[NCA][NCB],c[NRA][NCB];        


    for (i=0; i<NRA; i++)
      for (j=0; j<NCA; j++)
        a[i][j]= i+j;

    for (i=0; i<NCA; i++)
      for (j=0; j<NCB; j++)
        b[i][j]= i*j;

    for (i=0; i<NRA; i++)
      for (j=0; j<NCB; j++)
        c[i][j]= 0;

    double start_time = clock();
    for (i=0; i<NRA; i++)    
      {
        for(j=0; j<NCB; j++)       
          for (k=0; k<NCA; k++)
            c[i][j] += a[i][k] * b[k][j];
      }
    double end_time = clock();
    double result_time = (end_time - start_time) / CLOCKS_PER_SEC;   

  /*** Print results ***/
  cout<<"Result Matrix:\n";
  for (i=0; i<NRA; i++)
    {
      for (j=0; j<NCB; j++) 
        cout<<c[i][j]<<"\t";
      cout<<"\n"; 
    }

  cout<<"\n"<<result_time;
  return 0;
}
