#include<iostream>
#include<time.h>
using namespace std;
#define n 1000

int main()
{
	double start_time = clock();
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

	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			vo[i] += m[i][j] * vi[j];
		}	
	}
	for(int i = 0; i < n; i++)
	{
		cout<<vo[i]<<" ";
	} 
	double end_time = clock();
	double result_time = (end_time - start_time) / CLOCKS_PER_SEC;
	cout<<"\n"<<result_time;
	return 0;
}