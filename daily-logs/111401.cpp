#include<iostream>
#include<queue>
using namespace std;

int max(int a, int b) {
	return (a >= b) ? a : b;
}

class Node {
public:
	Node* left;
	Node* right;
	int height;
	int value;
	Node(int data, Node* l, Node* r) {
		left = l;
		right = r;
		this ->value = data;
	}
	Node(int data) {
		left = nullptr;
		right = nullptr;
		this->value = data;
		height = 1;
	}


};

class AVLTree {
public:
	Node* root;

	AVLTree() {
		root = nullptr;
	}

	int getHeight(Node* node) {
		if (node == NULL) {
			return 0;
		}
		return node->height;
	}

	void UpdateNodeHeight(Node* node) {
		if (node != NULL) {
			node->height = 1 + max(getHeight(node->left), getHeight(node->right));
		}
	}

	int  getBalanceFactor(Node* node) {
		if (node->left == NULL)
		{
			return -(node->right->height);
		}
		if (node->right == NULL) {
			return node->left->height;
		}
		else {
			return node->left->height - node->right->height;
		}
	}

	int closestLeafValue(Node* node) {
		if (node == nullptr) {
			return -10086;
		}
		queue<Node*> nodes;
		nodes.push(node);
		while (!nodes.empty()) {
			Node* currentNode = nodes.front();
			nodes.pop();

			if (currentNode->left == nullptr && currentNode->right == nullptr) {
				return currentNode->value;
			}

			else if (currentNode->left != nullptr)
			{
				nodes.push(currentNode->left);
			}
			else if (currentNode->right != nullptr) {
				nodes.push(currentNode->right);
			}
			else {
				return -10086;
			}

		}
	}
	



	Node* insert(Node* node,int key) {//传进去的node是root
		if (node == nullptr) {
			return new Node(key);
		}

		if (key < node->value) {
			node->left = insert(node->left, key);
		}
		else if (key > node->value) {
			node->right = insert(node->right, key);
		}
		else {
			return node;
			//如果遍历找到相同值，不插入，提前结束递归
		}

		UpdateNodeHeight(node);

		int bf = getBalanceFactor(node);

		//LL型不平衡
		if (bf == 2 && key < node->left->value) {
			Node* A = node;
			Node* B = node->left;
			A->left = B->right;
			node = B;
			node->right = A;

		}
		//LR型不平衡
		if (bf == 2 && key > node->left->value) {
			Node* C = node->left->right;
			Node* B = node->left;
			Node* A = node;
			Node* CL = C->left;
			Node* CR = C->right;

			node = C;
			C->left = B;
			C->right = A;

			A->right = CR;
			B->right = CL;
		}

		//RR型不平衡
		if (bf == -2 && key > node->right->value) {
			Node* A = node;
			Node* B = node->right;
			
			Node* BL = B->left;

			A->right = BL;
			node = B;
			node->left = A;
		}
		//RL型不平衡

		if (bf == -2 && key < node->right->value) {
			Node* A = node;
			Node* B = node->right;
			Node* C = B->left;
			Node* CL = C->left;
			Node* CR = C->right;

			A->right = CL;
			B->left = CR;
			node = C;
			node->left = A;
			node->right = B;

		}
		return node;


	}

	void Print(Node* root, int floor = 0) {

		if (root != NULL) {
			Print(root->right, floor + 2);
			for (int i = 0; i < floor; i++)
			{
				cout << " ";
			}

			{
				cout << root->value << endl;
			}
			Print(root->left, floor + 2);
		}

	}
	
};

int main() {
	AVLTree avl;
	avl.root=avl.insert(avl.root, 12);
	avl.root=avl.insert(avl.root, 24);
	avl.root = avl.insert(avl.root, 5);
	avl.root = avl.insert(avl.root, 8);
	avl.root = avl.insert(avl.root, 34);
	avl.root = avl.insert(avl.root, 17);
	avl.root = avl.insert(avl.root, 35);
	avl.root = avl.insert(avl.root, 56);
	//avl.root = avl.insert(avl.root, 14);
	//avl.root = avl.insert(avl.root, 66);
	//avl.root = avl.insert(avl.root, 78);
	//avl.root = avl.insert(avl.root, 43);
	//avl.root = avl.insert(avl.root, 65);
	//avl.root = avl.insert(avl.root, 11);
	//avl.root = avl.insert(avl.root, 70);
	
	avl.Print(avl.root);

	//求树高
	cout << "Tree Height:" << avl.getHeight(avl.root) << endl;

	//求最近叶节点值
	cout << "closest Leaf Value:" << avl.closestLeafValue(avl.root) << endl;

}