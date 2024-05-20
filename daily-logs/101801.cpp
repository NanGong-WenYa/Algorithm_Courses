#include <iostream>
using namespace std;

class Node {
public:
	int data;
	Node* next;

	Node(int val) : data(val), next(nullptr) {}
};

class CircLinkedList {
public:
	Node* head;
	CircLinkedList() : head(nullptr) {

		

	}

	// 在链表尾部添加节点
	void append(int val) {
		Node* newNode = new Node(val);
		if (!head) {
			head = newNode;
			head->next = head;  // 将头节点的next指向自身，形成循环
			return;
		}

		Node* tail = head;
		while (tail->next != head) {
			tail = tail->next;
		}

		tail->next = newNode;
		newNode->next = head;
	}

	// 打印链表
	void display() {
		if (!head) return;

		Node* current = head;
		do {
			cout << current->data << " ";
			current = current->next;
		} while (current != head);
		cout << endl;
	}
	void deleteNode(Node* n) {//假定输入的n都是链表里的指针

		if (head == nullptr)//如果链表为空
		{
			cout << "deleting operation can't be done" << endl;
			return;
		}
		Node* cur = head;
		if (cur == n)//如果第一个节点就是待删除节点
		{

			if (cur->next == cur) {//如果链表就一个节点
				head = nullptr;
				return;
			}

			do {
				cur = cur->next;
			} while (cur->next != head);
			head = head->next;
			cur->next = head;
			return;
		}

		do {
			cur = cur->next;
		} while (cur != head && cur->next != n);

		if (cur->next != n) {//如果找不到n节点
			cout << "deleting operation can't be done" << endl;
			return;
		}

		//现在cur的下一个节点是n
		cur->next = cur->next->next;
	}
};

int main() {
		int n, m;
		cin >> n >> m;
		//公式化
		int* a = new int[n];

		for (int i = 0; i < n; i++)

		{

			a[i] = i + 1;//标号

		}

		int cnt = n;

		int j = 0;

		while (cnt > 1)
		{
		

			for (int i = 0; i < n; i++)

			{

				if (a[i] != 0)

					j++;

				if (j == m)

				{

					j = 0;

					cout << a[i] << " ";

					a[i] = 0;

					cnt--;

				}

			}

		}

		for (int i = 0; i < n; i++)

			if (a[i] != 0)

				cout << a[i] << endl;

		delete[]a;

		//list output
		CircLinkedList jo;
		for (int i = 1; i <= n; i++) {
			jo.append(i);
		}
		jo.display();
		 cnt = 0;
		Node* cur = jo.head;
		while (jo.head != nullptr) {
			cnt++;
			if (cnt % m == 0)
			{
				cout << cur->data << ' ';
				Node* temp = cur;
				cur = cur->next;
				jo.deleteNode(temp);
				continue;
			}
			cur = cur->next;

		}

	}
