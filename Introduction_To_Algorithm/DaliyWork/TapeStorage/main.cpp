#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maxPrograms(vector<int>& programLengths, int tapeLength) {
    // 对程序长度进行排序
    sort(programLengths.begin(), programLengths.end());

    int maxProgramsCount = 0;
    int currentLength = 0;

    // 遍历所有程序长度
    for (int length : programLengths) {
        // 如果当前长度加上程序长度小于等于磁带长度
        // 则将当前长度更新为当前长度加上程序长度
        // 并将最大程序数量加1
        if (currentLength + length <= tapeLength) {
            currentLength += length;
            maxProgramsCount++;
        }
        else {
            // 如果当前长度加上程序长度超过磁带长度
            // 则停止遍历
            break;
        }
    }

    return maxProgramsCount;
}

int main() {
    int n, tapeLength;
    cin >> n >> tapeLength;

    vector<int> programLengths(n);
    for (int i = 0; i < n; i++) {
        cin >> programLengths[i];
    }

    int maxProgramsCount = maxPrograms(programLengths, tapeLength);
    cout << maxProgramsCount << endl;

    return 0;
}