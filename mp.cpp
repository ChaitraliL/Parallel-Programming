#include<iostream>
#include<omp.h>
#include<time.h>
using namespace std;
#define n 100000

int main()
{
	double start_time = clock();
	int arr[n],sum = 0;

	#pragma omp parallel for
	for(int i = 0; i<n; i++)
	{
		arr[i] = 1;
	}
	#pragma omp parallel for reduction(+:sum)
		for(int i = 0; i<n; i++)
		{
			sum+=arr[i];
		}
	cout<<sum;
	double end_time = clock();
	double result_time = (end_time - start_time) / CLOCKS_PER_SEC;
	cout<<"\n"<<result_time;
	return 0;
}