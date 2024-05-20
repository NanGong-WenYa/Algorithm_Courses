#include <iostream>
#include <algorithm>
#include<vector>

using namespace std;
class Node {
public:
    int key;
    Node* left;
    Node* right;
    int height;
};

class AVLTree {
public:
   

    Node* root;

    int getHeight(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int getBalance(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    void updateHeight(Node* node) {
        if (node != nullptr) {
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        }
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* insertNode(Node* node, int key) {
        if (node == nullptr) {
            Node* newNode = new Node;
            newNode->key = key;
            newNode->left = nullptr;
            newNode->right = nullptr;
            newNode->height = 1;
            return newNode;
        }

        if (key < node->key) {
            node->left = insertNode(node->left, key);
        }
        else if (key > node->key) {
            node->right = insertNode(node->right, key);
        }
        else {
            return node;
        }

        updateHeight(node);

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key) {
            return rightRotate(node);
        }
        if (balance < -1 && key > node->right->key) {
            return leftRotate(node);
        }
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inOrderTraversal(Node* node) {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            cout << node->key << " ";
            inOrderTraversal(node->right);
        }
    }


    AVLTree() : root(nullptr) {}

    void insert(int key) {
        root = insertNode(root, key);
    }

    void inOrder() {
        inOrderTraversal(root);
    }
    //作业函数1
    void traversalForHeight(Node* root,int height,int& heightOfAll) {
        if (root == NULL)
            return;
        else if (root->left == NULL && root->right == NULL) {
            if (height > heightOfAll)
                heightOfAll = height;
            return;
        }
        traversalForHeight(root->left, height+1, heightOfAll);
        traversalForHeight(root->right, height + 1, heightOfAll);
        
    }
    //作业函数2
    void  traversalForNearestLeaf(Node* root, int height, int& keyOfThatLeaf,int& smallestHeight) {

        if (root == NULL)
            return;
        
        else if (root->left == NULL && root->right == NULL) {
            
            if (height <smallestHeight){
                smallestHeight = height;
                keyOfThatLeaf = root->key;
            }
               
            return;
        }
        traversalForNearestLeaf(root->left, height + 1, keyOfThatLeaf, smallestHeight);
        traversalForNearestLeaf(root->right, height + 1, keyOfThatLeaf, smallestHeight);

    }
    void Print(Node* root, int floor = 0) {

        if (root != NULL) {
            Print(root->right, floor + 2);
            for (int i = 0; i < floor; i++)
            {
                cout << " ";
            }
           
            {
                cout << root->key<< endl;
            }
            Print(root->left, floor + 2);
        }

    }
};

int main() {
    AVLTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);
    tree.insert(98);
    tree.insert(178);
    tree.insert(12);

    cout << "AVL 树中序遍历结果："<<endl;
    tree.Print(tree.root);
    cout << endl;

    int height = 0;
    tree.traversalForHeight(tree.root, 1, height);
    cout << "height is:" << height << endl;

    int keyOfTheNearestLeaf = 0;
    int smallestHeight = 10000000;
    tree.traversalForNearestLeaf(tree.root, 1, keyOfTheNearestLeaf, smallestHeight);
    cout << "the key of the nearest leaf:" << keyOfTheNearestLeaf << endl;
    return 0;
}
