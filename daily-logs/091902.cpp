#include<iostream>
#include<fstream>
using namespace std;
long long fib(long long n) {
	if (n == 1 || n == 2)return 1;
	else if (n >= 3 && n <= 90)return fib(n - 1) + fib(n - 2);
	else return -1;
}
int main() {
	ifstream myLL("data.txt");
	long long data;
	if (!myLL.is_open())
	{
		cout << "can not open this file" << endl;
		return 0;
	}
	myLL >> data;
	cout << fib(data);
	myLL.close();
}