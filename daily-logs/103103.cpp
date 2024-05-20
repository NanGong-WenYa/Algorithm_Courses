
#include<iostream>
#include<stack>
#include<vector>
#include<queue>
using namespace std;


class BinaryTreeNode {
public:
    BinaryTreeNode() { LeftChild = RightChild = 0; }
    BinaryTreeNode(const char& e) { data = e;  LeftChild = RightChild = nullptr; }
    BinaryTreeNode(const char& e, BinaryTreeNode* l, BinaryTreeNode* r) { data = e;  LeftChild = l;  RightChild = r; }


    char data;
    BinaryTreeNode* LeftChild,
        * RightChild;
};

class BinaryTree {
public:
    BinaryTreeNode* root;

    BinaryTree() { root = 0; };
    BinaryTree(BinaryTreeNode* r) {
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
            if (c == '+' || c == '-')
                return 1;
            else
                if (c == '*' || c == '/')
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

        BinaryTreeNode* newTreeNode = new BinaryTreeNode(c, b, a);
        var.push(newTreeNode);
    }

    void InfixInput(const string& InputArray) {
        stack<BinaryTreeNode*> var;
        //var存的是二叉树节点指针，因为之前定义中，二叉树节点的左右孩子也为指针

        stack<char> op;
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

        return;
    }

    void Print(BinaryTreeNode* root, int floor = 0) {

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

    void countNodeNum(int& cnt, BinaryTreeNode* node) {
        if (node->LeftChild == NULL&&node->RightChild==NULL) {
            cnt++;
            return;
        }
        

       
        /*cout << "this->Node is " << node->data << ", and cnt is now" << cnt << endl;*/
        countNodeNum(cnt, node->LeftChild);
        countNodeNum(cnt, node->RightChild);

    }

    void swapLeftAndRightChild(BinaryTreeNode* node) {


        if (node != NULL) {
            swapLeftAndRightChild(node->LeftChild);

            swapLeftAndRightChild(node->RightChild);

            BinaryTreeNode* temp = node->LeftChild;
            node->LeftChild = node->RightChild;
            node->RightChild = temp;
            return;
        }
        else
            return;
    }

    void traversalByLayers(BinaryTreeNode* node) {
        queue<BinaryTreeNode*> temp;
        temp.push(node);
        while (!temp.empty()) {
            while (!temp.empty() && temp.front() == NULL)
            {
                temp.pop();
            }
            if (temp.empty())
                break;
            cout << temp.front()->data << ' ';
            temp.push(temp.front()->LeftChild);
            temp.push(temp.front()->RightChild);
            temp.pop();
        }
        cout << endl;
    }

    void countSizeOfEachLayer(BinaryTreeNode* treeRoot,
        vector<int>& cnt, int indexOfLayer) {
        if (treeRoot == NULL)
            return;

        if (cnt.size() < indexOfLayer + 1) {
            cnt.push_back(1);
        }
        else {
            cnt[indexOfLayer]++;
        }
        countSizeOfEachLayer(treeRoot->LeftChild, cnt, indexOfLayer + 1);
        countSizeOfEachLayer(treeRoot->RightChild, cnt, indexOfLayer + 1);
    }

    int getMaxSizeOfLayers() {
        vector<int> cnt;
        countSizeOfEachLayer(this->root, cnt, 0);
        int maxSize = 0;
        for (int n : cnt) {
            if (n > maxSize) {
                maxSize = n;
            }
        }
        return maxSize;
    }
};

int main() {
    string input;
    BinaryTree infixExpression;
    input = "a+b+c*(d+e)";

    //中缀表达式输入和展示
    infixExpression.InfixInput(input);
    infixExpression.Print(infixExpression.root);

    //计数
    int cnt = 0;
    infixExpression.countNodeNum(cnt, infixExpression.root);
    cout << cnt << endl;

    //按层遍历
    infixExpression.traversalByLayers(infixExpression.root);
    cout << endl;

    //找到size最大的层的索引
    cout << "The max size of layer is " << infixExpression.getMaxSizeOfLayers() << endl;

    //交换左右子树
    infixExpression.swapLeftAndRightChild(infixExpression.root);
    infixExpression.Print(infixExpression.root);



}