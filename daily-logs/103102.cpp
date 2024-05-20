#include<iostream>
#include<stack>
#include<vector>
using namespace std;


class BinaryTreeNode {
public:
    BinaryTreeNode() { LeftChild = RightChild = 0; }
    BinaryTreeNode(const char& e) { data = e;  LeftChild = RightChild = nullptr; }
    BinaryTreeNode(const char& e, BinaryTreeNode* l, BinaryTreeNode* r) { data = e;  LeftChild = l;  RightChild = r; }


    char data;
    BinaryTreeNode* LeftChild,   // left subtree
        * RightChild;  // right subtree
};

class BinaryTree {
public:
    BinaryTreeNode *root;

    BinaryTree() { root = 0; };
    BinaryTree(BinaryTreeNode *r) {
        root = r;
    }

    ~BinaryTree() {};

    bool IsEmpty() const
    {
        return ((root) ? false : true);
    }

    

    void inOrder(const BinaryTreeNode* treeRoot) {
        if (treeRoot != NULL) {
            
            inOrder(treeRoot->LeftChild);
            cout << treeRoot->data << endl;
            inOrder(treeRoot->RightChild);
        }
   }

    void preOrder(const BinaryTreeNode* treeRoot) {
        if (treeRoot != NULL) {
            cout << treeRoot->data << endl;
            preOrder(treeRoot->LeftChild);
            preOrder(treeRoot->RightChild);
        }
    }


    
    
    int precedence(char c) {
        if (c == '=')
            return 0;
        else
            if (c=='+'||c=='-')
                return 1;
            else
                if (c == '*'  || c == '/')
                    return 2;
                
                else
                {
                    
                    return -10086;
                }
    }
   
    void calculate(stack<BinaryTreeNode*>& var, stack<char>& op) {
        
        BinaryTreeNode* a = var.top();
        var.pop();
        BinaryTreeNode* b = var.top();
        var.pop();
        char c = op.top();
        op.pop();
        
        BinaryTreeNode* newTreeNode=new BinaryTreeNode(c,b,a);
        var.push(newTreeNode);
    }

    void InfixInput(const string& InputArray) {
        stack<BinaryTreeNode*> var;
        //var存的是二叉树节点指针，因为之前定义中，二叉树节点的左右孩子也为指针

        stack<char> op ;
        for (char element : InputArray) {

            if (element >= 'a' && element <= 'z') {
                //如果当前元素是变量，将变量存入树节点，树节点存入变量栈
                BinaryTreeNode* newNode = new BinaryTreeNode(element);
                var.push(newNode);
            }
            else if (element == '+' || element == '-' || element == '*' || element == '/ ' || element == '(' || element == ')')
            {   //如果当前元素是运算符
                if (element == '(') {
                    op.push(element);
                }
                else if (element == ')') {

                    while (op.top() != '(') {
                        //把遇到左括号之前的所有变量和符号都合并入一个树节点
                        calculate(var, op);
                    }
                    op.pop();//弹出左括号

                }
                else if (op.empty() || precedence(element) > precedence(op.top())) {
                    //如果当前op数组为空或者优先级大于op数组的top,当前运算符入栈
                    op.push(element);
                }
                else if (precedence(element) <= precedence(op.top())) {
                    //如果当前运算符优先级不大于op数组的顶部，说明op数组内的所有运算都可以进行（因为当前只有加减乘除两个优先级，没有第三个优先级）
                    //,不必再考虑后面运算符的优先级对op数组内运算符的运算的影响，
                    //将op数组内的所有运算进行后再将当前运算符入栈
                    while (!op.empty()) {
                        calculate(var, op);
                    }
                    op.push(element);
                }
            }


        }

        while (!op.empty()) {
            calculate(var, op);
        }

        this->root = var.top();
        
        return ;
    }

    void Print(BinaryTreeNode* root,int floor=0) {

        if (root != NULL) {
            Print(root->RightChild, floor + 2);
            for (int i = 0; i < floor; i++)
            {
                cout << " ";
            }
            cout << root->data << endl;
            Print(root->LeftChild, floor + 2);
        }

    }

};

int main() {
    string input;
    BinaryTree infixExpression;
    input = "a+b+c*(d+e)";
    infixExpression.InfixInput(input);
    infixExpression.Print(infixExpression.root);
}