#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<long long> a;

long long fib(long long n) {
    if (n <= 2)
        return 1;
    else if (a[n] != 0)
        return a[n];
    else {
        a[n] = fib(n - 1) + fib(n - 2);
        return a[n];
    }
}

int main() {
    ifstream myLL("data.txt");
    long long data;

    if (!myLL.is_open()) {
        cout << "无法打开文件" << endl;
        return 0;
    }

    myLL >> data;
    myLL.close();
    if (data > 90 || data <= 0) {
        cout << "WRONG";
        return 0;
    }
    a.assign(data + 1, 0); 

    cout << fib(data);

    return 0;
}