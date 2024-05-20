#include <iostream>
using namespace std;
//最终提交，把代码的while循环换成for循环
class Term {
public:
    int row, col;
    int value;
};

class SpareMatrix {
public:
    int rows, cols, numbersOfTerms;
    Term* terms;


    SpareMatrix(int rows, int cols, int numbersOfTerms) : rows(rows), cols(cols), numbersOfTerms(numbersOfTerms) {
        terms = new Term[numbersOfTerms];
    }


    ~SpareMatrix() {
        delete[] terms;
    }

    void clear(int numberOfTerms) {
        for (int i = 0; i < numberOfTerms; i++) {
            terms[i].col = 0;
            terms[i].row = 0;
            terms[i].value = 0;
        }
    }

    void multiply(SpareMatrix& b, SpareMatrix& c) {
        // 检验相容性
        if (cols != b.rows) {
            cout << "ERROR!" << endl;
            return;
        }

        // 设置结果矩阵c的特征
        c.rows = rows;
        c.cols = b.cols;
        c.numbersOfTerms = c.rows * c.cols;
        c.terms = new Term[c.numbersOfTerms];
        c.clear(c.numbersOfTerms);

        int cSize = 0;

        for (int i = 0; i < numbersOfTerms; i++) {
            for (int j = 0; j < b.numbersOfTerms; j++) {
                if (terms[i].col == b.terms[j].row) {
                    // 寻找c中匹配项
                    bool isMatched = false;
                    for (int k = 0; k < cSize; k++) {
                        if (c.terms[k].col == b.terms[j].col && c.terms[k].row == terms[i].row) {
                            c.terms[k].value += terms[i].value * b.terms[j].value;
                            isMatched = true;
                            break;
                        }
                    }
                    if (!isMatched) {
                        c.terms[cSize].value = terms[i].value * b.terms[j].value;
                        c.terms[cSize].row = terms[i].row;
                        c.terms[cSize].col = b.terms[j].col;
                        cSize++;
                    }
                }
            }
        }

        for (int i = 0; i < cSize; i++) {
            cout << c.terms[i].row << ' ' << c.terms[i].col << ' ' << c.terms[i].value << endl;
        }
        c.numbersOfTerms = cSize;
    }
};

int main() {
    /*int rowsA, colsA, numTermsA, rowsB, colsB, numTermsB;
    cin >> rowsA >> colsA >> numTermsA;
    SpareMatrix a(rowsA, colsA, numTermsA);

    for (int i = 0; i < numTermsA; i++) {
        cin >> a.terms[i].row >> a.terms[i].col >> a.terms[i].value;
    }

    cin >> rowsB >> colsB >> numTermsB;
    SpareMatrix b(rowsB, colsB, numTermsB);

    for (int i = 0; i < numTermsB; i++) {
        cin >> b.terms[i].row >> b.terms[i].col >> b.terms[i].value;
    }

    SpareMatrix c(0, 0, 0);
    a.multiply(b, c);

    
    return 0;*/////测试数据
    // 输入矩阵 A
    SpareMatrix a(2, 3, 5);
    a.terms[0] = { 0,0,1 };
    a.terms[1] = { 0,1,2 };
    a.terms[2] = { 1,0,3 };
    a.terms[3] = { 1,1,4 };
    a.terms[4] = { 1,2,1 };
    //长成：|1 2 0|
    //     |3 4 1|
    


    // 输入矩阵 B
    SpareMatrix b(3, 2, 5);
    b.terms[0] = { 0,0,5 };
    b.terms[1] = { 0,1,6 };
    b.terms[2] = { 1,0,7 };
    b.terms[3] = {1,1,8 };
    b.terms[4] = { 2,1,5 };
    //长成：|5 6|
    //     |7 8|
    //     |0 5|


    SpareMatrix c(0, 0, 0);
    a.multiply(b, c);
   
   return 0;


}
