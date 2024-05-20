#include<iostream>
#include<cstdlib>
using namespace std;
int main() {
	int n;
	cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
	int* min = new int[n];
	min[0] = arr[0];

	for (int i = 1; i < n; i++) {
		int temp=abs(arr[i]-arr[i-1]);

		for (int j = i -1; j >=0; j--) {
			if (abs(arr[i] - arr[j]) < temp)
				temp = abs(arr[i] - arr[j]);
		}
		min[i] = temp;
	}
	int sum = 0;
	for (int i = 0; i < n; i++) {
		sum += min[i];
	}
	cout << sum;
	return 0;
}