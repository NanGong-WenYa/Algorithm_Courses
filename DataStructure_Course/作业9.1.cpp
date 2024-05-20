#include<iostream>
using namespace std;

enum Color {
	red, black
};

class Node {
public:
	int data;
	Node* left, * right,*parent;
	Color color;
	Node(int key,Color c) {
		data = key;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
		color = c;

	}
	Node(int key,Color c, Node*p,Node* l, Node* r) {
		data = key;
		left = l;
		parent = p;
		right = r;
		color = c;
	}


};
class RedBlackTree {
public:
	Node* root;

	RedBlackTree() {
		root = nullptr;
	}
	Node* find(Node*,int);
	Node* insert(Node*, Node* p,char,int);
	
	void ascend(Node*);
	void correntInstructure(Node*);
	void Print(Node*,int);

	

	void erase(Node*,int);
	Node* findSuccessor(Node* node);
	void swap(Node*, Node*);
	

	void eraseFix(Node* node);
	
};
void RedBlackTree::ascend(Node* node) {
	if (node != nullptr) {
		ascend(node->right);
		cout << node->data << " ";
		ascend(node->left);
	}
	
}

void RedBlackTree::correntInstructure(Node* node) {
	//先判断函数可执行性
	if (node == nullptr || (node->left == nullptr && node->right == nullptr) ||
		(node->left != nullptr && node->left->left == nullptr && node->left->right == nullptr && node->right == nullptr) ||
		(node->left == nullptr && node->right != nullptr && node->right->left == nullptr && node->right->right == nullptr)) {
		return;
	}


	//再判断是否有结构错误
	if (node->left!=nullptr&&node->left->color == red)
		//判断左边有两个红节点
		//如果node左节点为红
	{
		if (node->left->right!=nullptr&&node->left->right->color == red) {
			//如果node左节点的右节点为红
			
			if (node->right == nullptr || node->right->color == black)
			//如果node的右节点是黑

			{	//旋转，根黑子红
				//LR型
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

				//改颜色
				C->color = A->color;
				B->color = red;
				A->color = red;

				//改父节点
				Node* Aparent = A->parent;
				if (CL != nullptr) {
					CL->parent = B;
				}
				if (CR != nullptr) {
					CR->parent = A;
				}
				B->parent = C;
				A->parent = C;
				C->parent = Aparent;
				if (Aparent == nullptr) {
					this->root = C;
				}

				//改父节点的子节点
				if (Aparent != nullptr) {
					Aparent->left = C;
				}
			}
			else {
				//node右节点为红
				//不旋转，根红子黑
				
				node->left->color = black;
				node->right->color = black;
				node->color = red;
				if (node->parent == nullptr)
					node->color = black;
			}
			

		}
		
		else if (node->left->left!=nullptr&&node->left->left->color == red)
			//node左节点的左节点为红
		{
			if (node->right==nullptr||node->right->color == black) {
				//旋转，根黑子红
				//LL型
				Node* A = node;
				Node* B = node->left;
				Node* BR = B->right;

				A->left = B->right;
				node = B;
				node->right = A;

				//改颜色
				B->color = A->color;
				A->color = red;

				//改父节点
				Node* Aparent = A->parent;
				A->parent = B;
				if (BR != nullptr) {
					BR->parent = A;
				}
				
				B->parent = Aparent;
				if (Aparent == nullptr) {
					this->root = B;
				}

				//改父节点的子节点
				if (Aparent != nullptr) {
					Aparent->left = B;
				}
			}
			else if (node->right->color == red) {
				//不旋转，根红子黑
				node->left->color = black;
				node->right->color = black;
				node->color = red;
				if (node->parent == nullptr)
					node->color = black;

			}
		}
		
	}
	

	if (node->right!=nullptr&&node->right->color == red)
		//判断右边有两个红节点
		//如果node右节点为红
	{
		if (node->right->left!=nullptr&&node->right->left->color == red) {
			//如果node右节点的左节点为红

			if (node->left == nullptr || node->left->color == black)
				//如果node的左节点是黑

			{	//旋转，根黑子红
				//RL型
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

				//改颜色
				C->color = A->color;
				B->color = red;
				A->color = red;

				//改变父节点
				Node* Aparent = A->parent;
				if (CL != nullptr) {
					CL->parent = A;
				}
				if (CR != nullptr) {
					CR->parent = B;
				}
				
				A->parent = C;
				B->parent = C;
				C->parent = Aparent;
				if (Aparent == nullptr)
				{
					this->root = C;
				}

				//改变父节点的子节点
				if (Aparent != nullptr) {
					Aparent->right = C;
				}
			}
			else {
				//node左节点为红
				//不旋转，根红子黑

				node->left->color = black;
				node->right->color = black;
				node->color = red;
				if (node->parent == nullptr)
					node->color = black;
			}


		}

		else if (node->right->right!=nullptr&&node->right->right->color == red)
			//node右节点的右节点为红
		{
			if (node->left==nullptr||node->left->color == black) {
				//旋转，根黑子红
				//RR型
				Node* A = node;
				Node* B = node->right;

				Node* BL = B->left;

				A->right = BL;
				node = B;
				node->left = A;
				/*cout << node->left->data << " " << node->right->data;*/

				//改颜色
				B->color = black;
				A->color = red;

				//改变父节点
				Node* Aparent = A->parent;
				A->parent = B;
				if (BL != nullptr) {
					BL->parent = A;
				}
				
				B->parent = Aparent;
				if (Aparent == nullptr) {
					this->root = B;
				}

				//改变父节点的子节点
				if (Aparent != nullptr) {
					Aparent->right = B;
					
					
				}
			}
			else if (node->left->color == red) {
				//不旋转，根红子黑
				node->left->color = black;
				node->right->color = black;
				node->color = red;
				if (node->parent == nullptr)
					node->color = black;
				
			}
		}

	}
	return;
}
Node* RedBlackTree::insert(Node* node, Node* p = nullptr, char c ='m', int key = -10086) {
	//在函数外另外定义一个空指针p
	// p代表根节点的父亲节点是空的
	
	if (node == nullptr) {
		Node* newNode = new Node(key, red, p, nullptr, nullptr);
		if (p == nullptr)//说明是第一次插入，是根节点
		{
			newNode->color = black;
			this->root = newNode;
		}
		else
			if (c == 'l') {
				p->left = newNode;
			}
			else
				if (c == 'r') {
					p->right = newNode;
				}
		
			
		return newNode;
	}
	else 
		if (key < node->data) {
			p = node;
			insert(node->left, p, 'l', key);
		}
		else if (key > node->data) {
			p = node;
			 insert(node->right, p,'r', key);
		}
		else {
			//既不大于node又不小于，说明待插入节点就是node，已经存在，递归停止
			return node;
		}
	correntInstructure(node);
	
	return node;
}
Node* RedBlackTree::find(Node* node,int key) {
	Node* current = node;
	while (current != nullptr && current->data != key) {
		if (key < current->data) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}
	return current; // 没找到就返回空指针
}


void RedBlackTree:: Print(Node* node, int floor = 0) {

	if (node != NULL) {
		Print(node->right, floor + 2);
		for (int i = 0; i < floor; i++)
		{
			cout << "    ";
		}

		{
			cout << node->data <<"("<<node->color<<")"<< endl;
			cout << endl;
		}
		Print(node->left, floor + 2);
	}

}
Node* RedBlackTree::findSuccessor(Node* node) {
	Node* cur = node;
	
	Node* findSuccessor = cur->right;
	while (findSuccessor->left != nullptr) {
		findSuccessor = findSuccessor->left;
	}
		
	return findSuccessor;
	
}
void RedBlackTree::swap(Node*a, Node*b)
{
	int temp = a->data;
	a->data = b->data;
	b->data = temp;
}
void RedBlackTree::erase(Node*X,int key) {
	Node* node = find(X,key); // 找到待删除节点
	
	
	if (node == nullptr) return; // 若节点不存在，直接返回

	if (node->left == nullptr && node->right == nullptr) {
		//是叶节点
		if (node == root) {
			root = nullptr;
		}
		else {
			if (node->color == black) {
				
				eraseFix(node);
			}

			if (node->parent->left == node) {
				node->parent->left = nullptr;
			}
			else {
				node->parent->right = nullptr;
			}
			
			delete node;		
			
		}

	}
	//只有一个节点，那必然是只有一个红色子节点的黑色节点
	else if (node->left == nullptr && node->right != nullptr) {
			//子节点为右节点
			Node* p = node->parent;
			if (p->right == node) {
				p->right = node->right;
			}
			else {
				p->left = node->right;
			}
			node->right->parent = p;
			node->right->color = black;
	}
	else
		if (node->left != nullptr && node->right == nullptr) {
			Node* p = node->parent;
			if (p->right == node) {
				p->right = node->left;
			}
			else {
				p->left = node->left;
			}
			node->left->parent = p;
			node->left->color = black;
		}
	else {
		//如果有两个子节点
		Node* successor = findSuccessor(node);
		swap(successor, node);
		erase(successor,successor->data);
	}

}
void RedBlackTree::eraseFix(Node* node) {
	//黑色叶子结点
	//兄弟节点为黑色
	Node* parent = node->parent;
	if (node->parent->left == node) {
		//删除节点是父节点的左节点

		Node* sibling = node->parent->right;
		if (node->parent->right->color == black) {

			if (sibling->left != nullptr && sibling->right == nullptr && sibling->left->color == red) {
				//兄弟节点只有一个左red节点


				Node* A = parent;
				Node* B = sibling;
				Node* C = sibling->left;

				C->left = A;
				C->right = B;
				A->right = nullptr;
				B->left = nullptr;
				if (A->parent->left == A) {
					A->parent->left = C;
				}
				else {
					A->parent->right = C;
				}
				C->parent = A->parent;
				A->parent = C;
				B->parent = C;

				C->color = A->color;
				A->color = black;
			}
			else if (sibling->left == nullptr && sibling->right != nullptr && sibling->right->color == red) {
				//兄弟节点只有右red节点
				Node* A = parent;
				Node* B = sibling;
				

				if (A->parent->left == A) {
					A->parent->left = B;
				}
				else {
					A->parent->right = B;
				}
				B->left = A;
				A->right = nullptr;

				B->parent = A->parent;
				A->parent = B;

				B->color = A->color;
				B->right->color = black;
				B->left->color = black;
				
			}
			else
				if (sibling->left != nullptr && sibling->right != nullptr && sibling->left->color == red &&
					sibling->right->color == red) {
					//兄弟节点有两个红子节点
					Node* A = parent;
					Node* B = sibling;
					Node* BL = B->left;
					Node* BR = B->right;

					if (A->parent->left = A) {
						A->parent = B;
					}
					else {
						A->parent->right = B;
					}
					B->parent = A->parent;
					A->parent = B;
					BL->parent = A;

					B->left = A;
					A->right = BL;

					BR->color = black;
					B->color = A->color;
					A->color = black;
					BL->color = red;

				}
				else {
					//sibling一个孩子没有
					if (parent->color == red||parent==root) {
						parent->color = black;
						sibling->color = red;
					}
					else {
						sibling->color = red;
						eraseFix(parent);
					}
				}
		}
		else {
			//兄弟节点为红色
			Node* SL = sibling->left;
			sibling->left = parent;
			parent->right = SL;

			sibling->color = black;
			parent->color = red;


			SL->parent = parent;
			sibling->parent = parent->parent;
			parent->parent = sibling;
		}


	}
	else {
		//删除节点为其父节点的右节点
		Node* sibling = node->parent->left;
		if (node->parent->right->color == black) {

			if (sibling->left != nullptr && sibling->right == nullptr && sibling->left->color == red) {
				//兄弟节点只有一个左red节点


				Node* A = parent;
				Node* B = sibling;
				

				B->right = A;
				A->left = nullptr;
				if (A->parent->left == A) {
					A->parent->left = B;
				}
				else {
					A->parent->right = B;
				}
				B->color = A->color;
				B->right->color = black;
				B->left->color = black;
				


				B->parent = A->parent;
				A->parent = B;
			}
			else if (sibling->left == nullptr && sibling->right != nullptr && sibling->right->color == red) {
				//兄弟节点只有右red节点
				Node* A = parent;
				Node* B = sibling;
				Node* C = B->right;

				if (A->parent->left == A) {
					A->parent->left = C;
				}
				else {
					A->parent->right = C;
				}
				C->left = B;
				C->right = A;
				A->left = nullptr;
				B->right = nullptr;

				C->parent = A->parent;
				B->parent = C;
				A->parent = C;

				C->color = A->color;
				A->color = red;
				B->color = red;

				
			}
			else
				if (sibling->left != nullptr && sibling->right != nullptr && sibling->left->color == red &&
					sibling->right->color == red) {
					//兄弟节点有两个红子节点
					Node* A = parent;
					Node* B = sibling;
					Node* BL = B->left;
					Node* BR = B->right;

					if (A->parent->left = A) {
						A->parent = B;
					}
					else {
						A->parent->right = B;
					}
					B->left = A;
					A->right = BL;

					B->parent = A->parent;
					A->parent = B;
					BR->parent = A;

					BR->color = black;
					B->color = A->color;
					A->color = black;
					BL->color = red;

				}
				else {
					//sibling一个孩子没有
					if (parent->color == red||parent==root) {
						parent->color = black;
						sibling->color = red;
					}
					else {
						sibling->color = red;
						
						eraseFix(parent);
					}
				}
		}
		else {
			//兄弟节点为红色
			
			Node* SR = sibling->right;
			sibling->right = parent;
			parent->left=SR;


			sibling->color = black;
			parent->color = red;


			SR->parent = parent;
			sibling->parent = parent->parent;
			parent->parent = sibling;
		}



	}

			

}

int main() {
	RedBlackTree t;
	
	t.insert(t.root,nullptr,'m', 12);
	t.insert(t.root, nullptr,'m' ,20);
	t.insert(t.root, nullptr,'m' ,38);
	t.Print(t.root);
	cout << endl;
	t.insert(t.root, nullptr,'m', 44);
	t.Print(t.root);
	cout << endl;
	t.insert(t.root, nullptr,'m', 68);
	t.insert(t.root, nullptr, 'm',37);
	t.insert(t.root, nullptr, 'm', 108);
	t.insert(t.root, nullptr, 'm', 56);
	t.insert(t.root, nullptr, 'm', 88);
	t.insert(t.root, nullptr, 'm', 124);
	t.insert(t.root, nullptr, 'm', 67);
	t.insert(t.root, nullptr, 'm', 74);
	cout << "树的最终形态：" << endl;
	t.Print(t.root);//0表示red 1表示black
	cout << "ascend函数：" << endl;
	t.ascend(t.root);
	
	
	t.erase(t.root,124);
	cout << endl;
	t.Print(t.root);
	cout << "ascend函数：" << endl;
	t.ascend(t.root);

	t.erase(t.root,68);
	cout << endl;
	t.Print(t.root);
	cout << "ascend函数：" << endl;
	t.ascend(t.root);

	t.erase(t.root, 20);
	cout << endl;
	t.Print(t.root);
	cout << "ascend函数：" << endl;
	t.ascend(t.root);

	t.erase(t.root, 38);
	cout << endl;
	t.Print(t.root);
	cout << "ascend函数：" << endl;
	t.ascend(t.root);

}