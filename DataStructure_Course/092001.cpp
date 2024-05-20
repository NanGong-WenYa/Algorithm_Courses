#include <iostream>
#include <vector>

using namespace std; 

void countingSort(vector<int>& arr, int n) {
    const int MAX_VALUE = 1000;  // 假设候选人编号的最大值
    vector<int> count(MAX_VALUE + 1, 0);

    // 统计每个候选人编号的出现次数
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }
	//下面这个循环的嵌套太6了
    int index = 0;
    for (int i = 1; i <= MAX_VALUE; i++) {
        for (int j = 0; j < count[i]; j++) {
            arr[index++] = i;
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> votes(m);
    for (int i = 0; i < m; i++) {
        cin >> votes[i];
    }

    // 使用计数排序对选票进行排序
    countingSort(votes, m);

    // 输出排序后的选票编号
    for (int i = 0; i < m; i++) {
        cout << votes[i] << " ";
    }
    cout << "\n";

    return 0;
}






//  下面是计数排序版本
#include<iostream>
using namespace std;
template<class T>
void Rank(T a[], int n, int r[]) {
    for (int i = 0; i < n; i++)
    {
        r[i] = 0;
        /*cout << r[i];*/
    }
    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++)
            if (a[j] <= a[i])
            {
                r[i]++;
                /*cout << r[i];*/
            }

            else {
                r[j]++;
                /*cout << r[j];*/
            }
}

template<class T>
void Rearrange(T a[], int n, int r[]) {
    T* u = new T[n + 1];
    for (int i = 0; i < n; i++) {
       /* cout << r[i];*/
            u[r[i]] = a[i];
    }
    for (int i = 0; i < n; i++)
        a[i] = u[i];
    delete[]u;
}
int main() {
    int n, m;
    cin >> n >> m;
    int* votes = new int[m];
    int* ranks = new int[m];
    for (int i = 0; i < m; i++)
        cin >> votes[i];
    Rank<int>(votes, m, ranks);
    Rearrange<int>(votes, m, ranks);
    for (int i = 0; i < m; i++) {
        cout << votes[i] << ' ';
    }
    return 0;
}



