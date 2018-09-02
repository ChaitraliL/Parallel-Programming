#include<iostream>
#include<omp.h>
#include<time.h>
using namespace std;
#define n 100000

int main()
{
	double start_time = clock();
	int a[n],b[n],c[n];
/*	for(int i = 0; i < n; i++)
	{
		a[i] = 1;
		b[i] = 2;	
	}*/ 
		#pragma omp parallel for
		for(int i = 0; i < n; i++)
		{
			a[i] = 1;
			b[i] = 2;
			c[i] = a[i] + b[i];
		}

	for(int i = 0; i < n; i++)
	{
		cout<<c[i]<<" ";
	}	
	double end_time = clock();
	double result_time = (end_time - start_time) / CLOCKS_PER_SEC;
	cout<<"\n"<<result_time;
	return 0;
}