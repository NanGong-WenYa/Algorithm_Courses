#include<iostream>
using namespace std;
//下三角矩阵转置
class UpperTriangularMatrix {
public:
	int n;
	int* element = new int[n * (n + 1) / 2];
	void set(int i, int j, const int& newValue) {
		//检验i，j是否合法（ij分别从1开始）
		if (i < 1 || j < 1 || i<n || j>n) {
			cout << "Inputed i and j are illegal!" << endl;
		}
		//在上三角，当且仅当i<=j
		if (i <= j)
		{
			element[(2*n-i)*(i-1)+j-1] = newValue;
		}
		else
			if (newValue != 0)
			{
				cout << "Inputed i and j are illegal!" << endl;
			}
	}

	void display() {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++)
			{
				if (i <= j) {
					cout << element[(2 * n - i) * (i - 1) + j - 1]<<' ';
				}
				else {
					cout << '0' << ' ';
				}
			}
			cout << endl;
		}
	}

};

class LowerTriangularMatrix {
public:
	int n;
	int* element = new int[n * (n + 1) / 2];
	void set(int i, int j, const int& newValue) {
		//检验i，j是否合法（ij分别从1开始）
		if (i < 1 || j < 1 || i<n || j>n) {
			cout << "Inputed i and j are illegal!" << endl;
		}
		//在下三角，当且仅当i>.=j
		if (i >= j)
		{
			element[i * (i - 1) / 2 + j - 1] = newValue;
		}
		else
			if (newValue != 0)
			{
				cout << "Inputed i and j are illegal!" << endl;
			}
	}

	UpperTriangularMatrix  transposition() {
		UpperTriangularMatrix res;
		res.n = this->n;
		for (int i = 1; i <= this->n; i++)//j是UTM的列
		{
			for (int j = 1; j <= i ; j++) {//i是UTM的行
				res.element[(2 * this->n - j) * (j - 1) + i - 1] = this->element[i * (i - 1) / 2 + j - 1];
				cout << "UTM的（" << j << ',' << i << "）为" << res.element[(2 * this->n - j) * (j - 1) + i - 1] << endl;
			}
		}
		return res;
		//时间复杂度是O(n)
	}

	
};
    

	int main() {
		int n;
		LowerTriangularMatrix inp;
		UpperTriangularMatrix outp;
		cin>> n;
		inp.n = n;
		outp.n = n;
		
		for (int i = 0; i <= n * (n + 1) / 2 - 1; i++) {
			int temp;
			cin >> temp;
			inp.element[i] = temp;
		}
		outp = inp.transposition();
		outp.display();
		return 0;

}
