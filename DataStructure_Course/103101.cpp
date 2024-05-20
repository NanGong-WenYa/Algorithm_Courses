#include<iostream>
using namespace std;


class deque {
public:

	int capacity, size, leftIndex, rightIndex;
	int* array;

	deque(int s) {
		capacity = s;
		leftIndex = 0;
		rightIndex = 0;
		size = 0;
		array = new int[s];
	}

	bool isFull() {
		if (capacity == size)
			return true;
		else
			return false;
	}

	bool isEmpty() {
		if (size == 0)
			return true;
		else
			return false;
	}

	void addLeft(int newNum) {
		if (isFull())
		{
			cout << "Deque is already full." << endl;
			return;
		}
		size++;
		if (leftIndex == 0) {
		for (int i = rightIndex; i >= 0; i--) {
				array[i + 1] = array[i];
			}
			rightIndex++;
			if (size==1)
				rightIndex = 0;
			leftIndex = 1;
		}
		leftIndex--;
		array[leftIndex] = newNum;

	}

	void addRight(int newNum) {
		if (isFull())
		{
			cout << "Deque is already full." << endl;
			return;
		}
		size++;
		if (rightIndex == size - 1) {
			for (int i = leftIndex; i < size; i++) {
				array[i - 1] = array[i];
			}
			leftIndex--;
			rightIndex = size - 2;
		}
		rightIndex++;
		array[rightIndex] = newNum;

	}

	int left() {
		if (isEmpty())
		{
			cout << "No left element is offered" << endl;
			return -10086;
		}
		return array[leftIndex];
	}

	int right() {
		if (isEmpty()) {
			cout << "No right element is offered" << endl;
			return -10086;
		}
		return array[rightIndex];
	}

	void deleteLeft() {
		if (isEmpty()) {
			cout << "No Left element left to delete";
		}
		array[leftIndex] = int();

		leftIndex++;
	}

	void deleteRight() {
		if (isEmpty()) {
			cout << "No Right element left to delete";
		}
		array[rightIndex] = int();

		rightIndex--;
	}

	void print() {
		if (isEmpty()) {
			cout << "deque is empty,so can't  print" << endl;
			return;
		}
		for (int i = leftIndex; i <= rightIndex; i++) {
			cout << array[i] << ' ';
		}
		cout << endl;
		return;
	}

};

int main() {
	deque de(10);
	int num;
	string op = "start";
	de.print();
	while (true) {
		cin >> op;
		if (op == "AddLeft") {
			cin >> num;
			de.addLeft(num);
			de.print();
		}
		else if (op == "AddRight") {
			cin >> num;
			de.addRight(num);
			de.print();
		}
		else if (op == "DeleteLeft") {
			de.deleteLeft();
			de.print();
		}
		else if (op == "DeleteRight") {
			de.deleteRight();
			de.print();
		}
		else if (op == "IsFull") {
			cout << "IsFull?:" << ' ' << de.isFull() << endl;
			de.print();
		}
		else if (op == "IsEmpty") {
			cout << "IsEmpty?:" << ' ' << de.isEmpty() << endl;
			de.print();
		}
		else if (op == "End") {
			break;
			de.print();
		}
		else {
			cout << "ERROR!" << endl;
		}
	}
	
}