#include<iostream>
using namespace std;
class MaxHeap {


public:
	int currentSize, maxSize;
	int* heap;

	MaxHeap(int maxS) {
		currentSize = 0;
		heap = new int[maxS];
		maxSize = maxS;
	}

	MaxHeap(int maxS, int maxElement, int minElement) {
		currentSize = 0;
		heap = new int[2 * maxS + 1];
		heap[0] = maxElement;
		for (int i = maxS; i < 2 * maxS + 1; i++) {
			heap[i] = minElement;
		}
	};
	int size() const {
		return currentSize;
	}

	int top() {
		if (currentSize == 0) {
			cout << "No int in the heap now!" << endl;
			return -100086;
		}
		return heap[1];

	}

	void push(const int& x) {
		if (currentSize == maxSize) {
			cout << "Heap is full now!" << endl;
			return;
		}

		currentSize++;
		heap[currentSize] = x;
		int index = currentSize;


		while (x > heap[index / 2] && index != 1) {
			heap[index] = heap[index / 2];
			index /= 2;
		}
		heap[index] = x;
	}

	void newPush(int y) {


		currentSize++;
		int index1 = currentSize;
		int index2 = currentSize / 2;
		while (y > heap[index2])//不用每次看index是否越界越过0
		{
			heap[index1] = heap[index2];
			index1 = index2;
			index2 /= 2;
		}

		heap[index1] = y;
		return;
	}

	void pop() {
		if (currentSize == 0) {
			cout << "heap is empty now!" << endl;
			return;
		}

		heap[1] = int();

		int lastElement = heap[currentSize];
		currentSize--;


		int currentNode = 1, child = 2;

		while (child <= currentSize) {
			if (child < currentSize && heap[child] < heap[child + 1]) {
				child++;
			}

			if (lastElement >= heap[child])
				break;
			heap[currentNode] = heap[child];
			currentNode = child;
			child *= 2;

		}
		heap[currentNode] = lastElement;


	};

	void newPop() {
		if (currentSize == 0) {

			cout << "heap is empty now!" << endl;

			return;

		}

		heap[1] = int();

		int y = heap[currentSize];

		heap[currentSize] = heap[maxSize];//让当前最后一个节点的值等于minElement
		//，这样就不用在循环里每次比较child是否越界了
		currentSize--;

		int currentNode = 1, child = 2;

		while (heap[child] > y) {

			if (heap[child] < heap[child + 1])
				child++;

			heap[currentNode] = heap[child];

			currentNode = child;

			child *= 2;

		}

		heap[currentNode] = y;



	}

	void show() {
		cout << "heap is showing:";
		for (int i = 1; i <= currentSize; i++) {
			cout << heap[i] << ' ';
		}
		cout << endl;
		return;
	}

};

int main() {
	clock_t t1, t2;

	int n;

	cout << "请输入数字个数n：";

	cin >> n;

	int* a = new int[n];

	int* b = new int[n];

	srand(time(NULL));

	for (int i = 1; i <= n; i++) {

		a[i] = rand() % 100;

		b[i] = a[i];

	}

	MaxHeap A(n);

	MaxHeap B(n, 100000, -100000);




	cout << endl << "测试Push方法" << endl << endl;

	t1 = clock();

	for (int i = 1; i <= n; i++)
		A.push(a[i]);

	//A.show();

	t2 = clock();

	cout << "方法一用时： " << (t2 - t1) << " CLOCKS_PER_SEC" << endl << endl;


	t1 = clock();

	for (int i = 1; i <= n; i++)
		B.newPush(a[i]);

	//B.show();

	t2 = clock();

	cout << "方法二用时： " << (t2 - t1) << " CLOCKS_PER_SEC" << endl << endl;


	cout << endl << "测试Pop方法" << endl << endl;

	t1 = clock();

	for (int i = 1; i <= n; i++)
		A.pop();

	//A.show();

	t2 = clock();

	cout << "方法一用时： " << (t2 - t1) << " CLOCKS_PER_SEC" << endl << endl;


	t1 = clock();

	for (int i = 1; i <= n; i++) {
		//B.show();
		B.newPop();
	}





	t2 = clock();

	cout << "方法二用时： " << (t2 - t1) << " CLOCKS_PER_SEC" << endl << endl;


	return 0;
}