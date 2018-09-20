#include<iostream>
#include<omp.h>
using namespace std;
#define n 1445

int main()
{
	int m[n][n],vi[n],vo[n];

	for(int i = 0; i < n; i++)
	{
		vi[i] = 1;
		//cout<<vo[i]<<" ";
		for(int j = 0; j < n; j++)
		{
			m[i][j] = 1;
		}	
	}

	double start_time = omp_get_wtime(); //omp function doesn't make difference in serial but it does in parallel
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			vo[i] += m[i][j] * vi[j];
		}	
	}
	double end_time = omp_get_wtime();
	double result_time = (end_time - start_time);
	for(int i = 0; i < n; i++)
	{
		cout<<vo[i]<<" ";
	} 
	cout<<"\n"<<result_time;
	return 0;
}
