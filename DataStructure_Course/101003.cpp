#include <iostream>
#include<vector>
using namespace std;
template<typename T>
class Chain {
public:
	T* firstNode;
	Chain() {
		firstNode = nullptr;
	}

};
class rowElement {
public:
	int col;
	int value;
	rowElement* next;
	rowElement() {
		next = nullptr;
	}
};

class headerElement {
public:
	int row;
	Chain<rowElement> rowChain;
	headerElement* next;
	headerElement() {
		rowChain.firstNode = nullptr;
		next = nullptr;
	}
	void clear() {
		rowChain.firstNode->next = nullptr;
	}
	/*void push_back(rowElement &r) {
		rowElement* curr = rowChain.firstNode;
		while (curr->next != nullptr) {
			curr = curr->next;

		}
		curr->next = &r;


	这段代码的问题
	1.生存期问题:
	在这种情况下，你将指向 rowElement r 的引用 &r 添加到链表中，但是 r 的生存期是由调用者控制的。
	如果调用者在函数返回后销毁了 r，那么链表中将包含一个无效指针，这可能导致程序崩溃或未定义的行为。

	2.风险问题:
	如果调用者在 r 被添加到链表后修改了 r，链表中的指针将指向已更改的数据，这可能破坏链表的结构或导致错误的结果。

	一种更安全的方法是动态分配内存来存储新元素，并在链表中存储指向动态分配的元素的指针。
	这样确保了元素在需要时存在，并且不会受到调用者修改的影响。
	}*/
	void push_back(rowElement& r) {
		rowElement* newRE = new rowElement();
		newRE->col = r.col;
		newRE->value = r.value;
		newRE->next = nullptr;

		if (!rowChain.firstNode) {
			rowChain.firstNode = newRE;
			return;
		}

		rowElement* curr = rowChain.firstNode;
		while (curr->next != nullptr) {
			curr = curr->next;
		}

		curr->next = newRE;
	}
};

class LinkedMatrix {
public:
	int rows, cols;
	Chain<headerElement> headerChain;
	void clear() {
		headerChain.firstNode = nullptr;
	}
	void push_back(int value, int rowNum, int colNum) {//已知该元素的行列数和value，存一下
		rowElement* newRE = new rowElement();//声明一个新rowElement存这个新元素
		newRE->col = colNum;
		newRE->value = value;

		headerElement* curr = headerChain.firstNode;
		if (!curr) {
			headerElement* newHE = new headerElement();
			newHE->row = rowNum;
			Chain<rowElement>* newRC = new Chain<rowElement>();
			newRC->firstNode = newRE;
			newHE->rowChain = *newRC;
			headerChain.firstNode = newHE;
			return;
		}
		while (curr->next != nullptr && curr->row != rowNum) {//遍历头链表，找与新元素row相同的头元素
			curr = curr->next;
		}
		if (curr->row == rowNum) {//如果能找到，对这个头pushback新元素
			curr->push_back(*newRE);
			return;
		}
		else {//如果找不到，新建一个头元素，把新元素存到这个头元素的行链表里去
			headerElement* newHE = new headerElement();
			newHE->row = rowNum;
			Chain<rowElement>* newRC = new Chain<rowElement>();
			newRC->firstNode = newRE;
			newHE->rowChain = *newRC;
			curr->next = newHE;
			return;
		}
	}
	int find(int rowNum, int colNum) {
		headerElement* curr = headerChain.firstNode;
		while (curr->next != nullptr && curr->row != rowNum) {//遍历头链表，找与元素row相同的头元素
			curr = curr->next;
		}
		if (curr->row != rowNum) {//找不到行就报错
			cout << "该元素不存在啊TnT" << endl;
			return -10086;
		}
		rowElement* curr2 = curr->rowChain.firstNode;//找到了就遍历rowChain
		while (curr2->next != nullptr && curr2->col != colNum) {
			curr2 = curr2->next;
		}
		if (curr2->col != colNum) {
			cout << "该元素不存在啊TnT" << endl;
			return -10086;
		}
		return curr2->value;
	}
	void display() {
		headerElement* currRow = headerChain.firstNode;

		while (currRow) {
			int currCol = 0;
			rowElement* currElement = currRow->rowChain.firstNode;


			while (currElement) {

				while (currCol < currElement->col) {
					cout << "0\t";
					currCol++;
				}

				cout << currElement->value << "\t";
				currCol++;
				currElement = currElement->next;
			}


			while (currCol < cols) {
				cout << "0\t";
				currCol++;
			}

			cout << endl;
			currRow = currRow->next;
		}
	}

	LinkedMatrix addMatrix(const LinkedMatrix& matrix2) {

		if (rows != matrix2.rows || cols != matrix2.cols) {
			cout << "Matrix dimension don't match for adition" << endl;
			return LinkedMatrix();
		}

		LinkedMatrix result;
		result.rows = rows;
		result.cols = cols;

		headerElement* currRow1 = headerChain.firstNode;
		headerElement* currRow2 = matrix2.headerChain.firstNode;

		while (currRow1 && currRow2) {
			int currCol = 0;
			rowElement* currElement1 = currRow1->rowChain.firstNode;
			rowElement* currElement2 = currRow2->rowChain.firstNode;

			while (currCol < cols) {
				int sum = 0;

				if (currElement1 && currElement1->col == currCol) {
					sum += currElement1->value;
					currElement1 = currElement1->next;
				}

				if (currElement2 && currElement2->col == currCol) {
					sum += currElement2->value;
					currElement2 = currElement2->next;
				}

				result.push_back(sum, currRow1->row, currCol);
				currCol++;
			}

			currRow1 = currRow1->next;
			currRow2 = currRow2->next;
		}

		return result;
	}
	//	LinkedMatrix plus(const LinkedMatrix& b) {//这是草稿
	//
	//		if (this->rows != b.rows || this->cols != b.cols) {//可行性检查
	//			cout << "Two matrix did not match!";
	//			return LinkedMatrix();//返回一个空矩阵
	//		}
	//		//结果矩阵
	//		LinkedMatrix c;
	//		c.rows = this->rows;
	//		c.cols = this->cols;
	//
	//		headerElement* headCurA = (this->headerChain.firstNode);
	//		headerElement* headCurB = (b.headerChain.firstNode);
	//		headerElement* headCurC = (c.headerChain.firstNode);
	//		rowElement* rowCurA = headCurA->rowChain.firstNode;
	//		rowElement* rowCurB = headCurB->rowChain.firstNode;
	//
	//		while (headCurA && headCurB) {
	//			rowCurA = headCurA->rowChain.firstNode;
	//			rowCurB = headCurB->rowChain.firstNode;
	//
	//			headerElement* newHE = new headerElement();
	//			headCurC = newHE;
	//			headCurC->rowChain.firstNode = nullptr;
	//			headCurC = headCurC->next;
	//			while (rowCurA && rowCurB) {
	//				if (rowCurA->col > rowCurB->col) {//如果在同一行A的迭代器比b的更靠后，col更大
	//					while (rowCurB->next && rowCurA->col != rowCurB->col) {
	//						rowCurB = rowCurB->next;
	//					}
	//					if (rowCurA->col == rowCurB->col) {
	//						rowElement newRE;
	//						newRE.col = rowCurA->col;
	//						newRE.value = rowCurA->value + rowCurB->value;
	//						newRE.next=nullptr;
	//						headCurC->push_back(newRE);
	//						rowCurA = rowCurA->next;
	//						rowCurB = rowCurB->next;
	//					}
	//					else {
	//						headCurA = headCurA->next;
	//						headCurB = headCurB->next;
	//						continue;
	//					}
	//				}
	//				else if (rowCurB->col > rowCurA->col) {//如果在同一行B的迭代器比b的更靠后，col更大
	//					while (rowCurA->next && rowCurA->col != rowCurB->col) {
	//						rowCurA = rowCurA->next;
	//					}
	//					if (rowCurA->col == rowCurB->col) {//找到了A，B可以相加的项，加完了各向本行的下面遍历
	//						rowElement newRE;
	//						newRE.col = rowCurA->col;
	//						newRE.value = rowCurA->value + rowCurB->value;
	//						headCurC->push_back(newRE);
	//						rowCurA = rowCurA->next;
	//						rowCurB = rowCurB->next;
	//					}
	//					else {//到行尾还没找到，就让行数加一，循环continue
	//						headCurA = headCurA->next;
	//						headCurB = headCurB->next;
	//						continue;
	//					}
	//				}
	//				else if (rowCurB->col == rowCurA->col) {//正好A,B目前的两个元素可以相加
	//					rowElement newRE;
	//					newRE.col = rowCurA->col;
	//					newRE.value = rowCurA->value + rowCurB->value;
	//					headCurC->push_back(newRE);
	//					rowCurA = rowCurA->next;
	//					rowCurB = rowCurB->next;
	//				}
	//			}
	//			headCurA = headCurA->next;
	//			headCurB = headCurB->next;
	//		}
	//		return c;
	//	}
	LinkedMatrix minusMatrix(const LinkedMatrix& matrix2) {

		if (rows != matrix2.rows || cols != matrix2.cols) {
			cout << "Matrix dimensions don't match for addition." << endl;
			return LinkedMatrix();
		}

		LinkedMatrix result;
		result.rows = rows;
		result.cols = cols;

		headerElement* currRow1 = headerChain.firstNode;
		headerElement* currRow2 = matrix2.headerChain.firstNode;

		while (currRow1 && currRow2) {
			int currCol = 0;
			rowElement* currElement1 = currRow1->rowChain.firstNode;
			rowElement* currElement2 = currRow2->rowChain.firstNode;

			while (currCol < cols) {
				int sum = 0;

				if (currElement1 && currElement1->col == currCol) {
					sum += currElement1->value;
					currElement1 = currElement1->next;
				}

				if (currElement2 && currElement2->col == currCol) {
					sum -= currElement2->value;
					currElement2 = currElement2->next;
				}
				if (sum != 0) {
					result.push_back(sum, currRow1->row, currCol);
				}
				currCol++;
			}

			currRow1 = currRow1->next;
			currRow2 = currRow2->next;
		}

		return result;
	}
	void findNeededRowElement(headerElement* currRow1, int i, int k, bool& foundM1, int& neededM1) {
		foundM1 = false;

		while (currRow1 && currRow1->row < i) {
			currRow1 = currRow1->next;
		}

		if (currRow1 && currRow1->row == i) {
			rowElement* curM1 = currRow1->rowChain.firstNode;
			while (curM1) {
				if (curM1->col == k) {
					foundM1 = true;
					neededM1 = curM1->value;
					return;
				}
				curM1 = curM1->next;
			}
		}
	}

	LinkedMatrix multiplyMatrix(const LinkedMatrix& matrix2) {

		if (cols != matrix2.rows) {
			cout << "不合法输入" << endl;
			return LinkedMatrix();
		}

		LinkedMatrix result;
		result.rows = rows;
		result.cols = matrix2.cols;
		vector<vector<int>> tempRes(rows, vector<int>(matrix2.cols, 0));

		for (int i = 0; i < rows; i++)
			for (int j = 0; j < matrix2.cols; j++)
			{
				tempRes[i][j] = 0;
				int product = 0;
				for (int k = 0; k < matrix2.rows; k++) {
					int neededM1, neededM2;//找M1的第i行第k列，M2的第k行第j列
					bool foundM1 = false, foundM2 = false;
					headerElement* currRow1 = this->headerChain.firstNode;
					headerElement* currRow2 = matrix2.headerChain.firstNode;
					findNeededRowElement(currRow1, i, k, foundM1, neededM1);
					findNeededRowElement(currRow2, k, j, foundM2, neededM2);


					if (foundM1 && foundM2)
						product += neededM1 * neededM2;
				}

				tempRes[i][j] += product;
			}




		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < matrix2.cols; ++j) {
				if (tempRes[i][j] != 0) {
					result.push_back(tempRes[i][j], i, j);
				}
			}
		}

		return result;
	}

};

int main() {
	cout << "测试一下push_back和find函数吧" << endl;
	LinkedMatrix matrix;

	matrix.push_back(10, 0, 0);
	matrix.push_back(20, 0, 1);
	matrix.push_back(30, 1, 0);
	matrix.push_back(40, 1, 1);

	cout << "Test data set 1:" << endl;
	cout << "Matrix after push_back:" << endl;

	matrix.display();
	cout << endl;

	int value1 = matrix.find(1, 1);
	cout << "Value at (1, 1): " << value1 << endl;
	cout << endl;

	cout << "快测试一下加法，减法函数ber" << endl;
	LinkedMatrix matrix1;
	matrix1.push_back(1, 0, 0);
	matrix1.push_back(2, 1, 1);
	matrix1.rows = 2;
	matrix1.cols = 2;

	LinkedMatrix matrix2;
	matrix2.push_back(3, 0, 1);
	matrix2.push_back(4, 1, 0);
	matrix2.rows = 2;
	matrix2.cols = 2;


	cout << "Matrix 1:" << endl;
	matrix1.display();

	cout << "Matrix 2:" << endl;
	matrix2.display();


	LinkedMatrix sumMatrix = matrix1.addMatrix(matrix2);
	cout << "Matrix Sum:" << endl;
	sumMatrix.display();

	LinkedMatrix difMatrix = matrix1.minusMatrix(matrix2);
	cout << "Matrix differance:" << endl;
	difMatrix.display();

	cout << "快测试一下乘法函数吧" << endl;
	// 输入矩阵 A
	LinkedMatrix a;
	a.push_back(1, 0, 0);
	a.push_back(2, 0, 1);
	a.push_back(3, 1,0);
	a.push_back(4,1,1);
	a.push_back(1,1,2);
	a.rows = 2;
	a.cols = 3;
	//长成：|1 2 0|
	//     |3 4 1|



	// 输入矩阵 B
	LinkedMatrix b;
	b.push_back(5, 0, 0);
	b.push_back(6,0,1);
	b.push_back(7,1,0);
	b.push_back(8,1,1);
	b.push_back(5,2,1);
	b.rows = 3;
	b.cols = 2;

	//长成：|5 6|
	//     |7 8|
	//     |0 5|


	LinkedMatrix productMatrix;
	productMatrix=a.multiplyMatrix(b);
	cout << "Matrix product:" << endl;
	productMatrix.display();
}
