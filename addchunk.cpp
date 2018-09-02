#include<iostream>
#include<time.h>
#include<omp.h>
#define n 100000
using namespace std;

int main()
{
	double start_time = clock();
	int arr[n],sum = 0,suml;

	for(int i = 0; i<n; i++)
	{
		arr[i] = 1;
	}

	#pragma omp parallel private(suml)
	{
		int tn = omp_get_num_threads(),chunksize = n / tn,from = omp_get_thread_num()*chunksize,to = from + chunksize;
		for(int i = from; i < to; i++)
		{
			suml += arr[i];
		}

		#pragma omp critical
		{
			sum += suml;
		}
	}
	cout<<sum;
	double end_time = clock();
	double result_time = (end_time - start_time) / CLOCKS_PER_SEC;
	cout<<"\n"<<result_time;
	return 0;
}