#include<iostream>
using namespace std;
//稀疏矩阵乘法
//这个是第一遍写的，有很多失误
class Term {
public:
	int row, col;
	int value;

};
class SpareMatrix {
public:
	int rows, cols, numbersOfTerms;
	Term* terms = new Term[numbersOfTerms];
	void clear() {
		for (int i = 0; i < numbersOfTerms; i++) {
			terms[i].col = 0;
			terms[i].row = 0;
			terms[i].value = 0;
		}
	}
	void multiple(SpareMatrix& b, SpareMatrix& c) {//c是结果矩阵，b是后被乘矩阵
		//检验相容性
		if (rows != b.rows || cols != b.cols) {
			cout << "ERROR!" << endl;
		}
		//设置结果矩阵c的特征
		c.rows = this->rows;
		c.cols = b.cols;
		c.numbersOfTerms = c.rows * c.cols;
		c.clear();
		int cSize = 0;

		int it = 0;
		while (it <= this->numbersOfTerms - 1) {

			int ib = 0;
			Term tb;
			tb.col = 0;
			tb.row = 0;
			tb.value = 0;
			while (ib <= b.numbersOfTerms - 1 && (tb.col != this->terms[it].row || tb.row != this->terms[it].col)) {
				tb = b.terms[ib];
				ib++;
			}
			ib--;
			if (tb.col != this->terms[it].row || tb.row != this->terms[it].col)
				continue;
			int ic = 0;
			bool isMatched = false;
			for (; ic < cSize; ic++) {
				if (c.terms[ic].col == b.terms[ib].col && c.terms[ic].row == this->terms[it].row)
				{
					isMatched = true;
					break;
				}

			}
			if (isMatched) {
				c.terms[ic].value += (b.terms[ib].value) * (this->terms[it].value);
			}
			else {
				c.terms[++cSize - 1].value = (b.terms[ib].value) * (this->terms[it].value);
				c.terms[cSize - 1].row = this->terms[it].row;
				c.terms[cSize - 1].col = b.terms[it].col;

			}
			it++;
		}
		for (int i = 0; i < cSize; i++) {
			cout << c.terms[i].row << ' ' << c.terms[i].col << ' ' << c.terms[i].value << endl;
		}

	}

};
int main() {
	SpareMatrix a, b, c;

	cin >> a.rows >> a.cols >> a.numbersOfTerms;
	for (int i = 0; i < a.numbersOfTerms; i++) {
		cin >> a.terms[i].row >> a.terms[i].col >> a.terms[i].value;
	}
	cin >> b.rows >> b.cols >> b.numbersOfTerms;
	for (int i = 0; i < b.numbersOfTerms; i++) {
		cin >> b.terms[i].row >> b.terms[i].col >> b.terms[i].value;
	}
	a.multiple(b, c);
	return 0;
}