#include<iostream>
#include<time.h>
using namespace std;
#define n 10000

int main()
{
	int arr[n];
	for(int i = 0; i < n; i++)
		arr[i] = rand() % n + 1;

	double start_time = clock();
	for(int i = 0; i < n-1; i++)
	{
		for(int j = 0; j < n-i-1; j++)
		{
			if(arr[j] > arr[j+1])
			{
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
	double end_time = clock();
	double result_time = (end_time - start_time) / CLOCKS_PER_SEC;

	for(int i = 0; i < n; i++)
		cout<<arr[i]<<" ";
	cout<<"\n"<<result_time;
	return 0;
}