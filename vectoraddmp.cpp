#include<iostream>
#include<omp.h>
using namespace std;
#define n 100000

int main()
{
	int a[n],b[n],c[n];
	for(int i = 0; i < n; i++)
	{
		a[i] = 1;
		b[i] = 2;	
	} 
	
	double start_time = omp_get_wtime();
	#pragma omp parallel for
	for(int i = 0; i < n; i++)
	{
		c[i] = a[i] + b[i];
	}
	double end_time = omp_get_wtime();

	for(int i = 0; i < n; i++)
	{
		cout<<c[i]<<" ";
	}	
	double result_time = (end_time - start_time);
	cout<<"\n"<<result_time;
	return 0;
}
//0.000244117
