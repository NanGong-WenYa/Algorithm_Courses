#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maxPrograms(vector<int>& programLengths, int tapeLength) {
    // �Գ��򳤶Ƚ�������
    sort(programLengths.begin(), programLengths.end());

    int maxProgramsCount = 0;
    int currentLength = 0;

    // �������г��򳤶�
    for (int length : programLengths) {
        // �����ǰ���ȼ��ϳ��򳤶�С�ڵ��ڴŴ�����
        // �򽫵�ǰ���ȸ���Ϊ��ǰ���ȼ��ϳ��򳤶�
        // ����������������1
        if (currentLength + length <= tapeLength) {
            currentLength += length;
            maxProgramsCount++;
        }
        else {
            // �����ǰ���ȼ��ϳ��򳤶ȳ����Ŵ�����
            // ��ֹͣ����
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