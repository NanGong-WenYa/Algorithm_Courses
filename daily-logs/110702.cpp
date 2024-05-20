#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class BinaryTreeNode {
public:
    char data;
    int weight;
    BinaryTreeNode* LeftChild;
    BinaryTreeNode* RightChild;

    BinaryTreeNode() : data(0),weight(0), LeftChild(nullptr), RightChild(nullptr) {}
    BinaryTreeNode(const char& e,const int & w) : data(e), weight(w),LeftChild(nullptr), RightChild(nullptr) {}
    BinaryTreeNode(const char& e, const int& w,BinaryTreeNode* l, BinaryTreeNode* r) : data(e), weight(w),LeftChild(l), RightChild(r) {}
};

class BinaryTree {
public:
    BinaryTreeNode* root;

    BinaryTree() : root(nullptr) {}
    BinaryTree(BinaryTreeNode* r) : root(r) {}

    ~BinaryTree() {}

    bool IsEmpty() const {
        return root == nullptr;
    }

    void preOrder(const BinaryTreeNode* treeRoot) {
        if (treeRoot != nullptr) {
            cout << treeRoot->weight << " ";
            preOrder(treeRoot->LeftChild);
            preOrder(treeRoot->RightChild);
        }
    }


    void Print(BinaryTreeNode* root, int floor = 0) {

        if (root != NULL) {
            Print(root->RightChild, floor + 2);
            for (int i = 0; i < floor; i++)
            {
                cout << " ";
            }
            if (root->LeftChild == NULL && root->RightChild == NULL) {
                cout << root->weight << ' ' << root->data << endl;
            }
            else
            {
                cout << root->weight << endl;
            }
            Print(root->LeftChild, floor + 2);
        }

    }
};

class HuffmanNode {
public:
    BinaryTree tree;
    int weight;

    HuffmanNode() : weight(0) {}

    // 定义 HuffmanNode 的小于运算符，用于优先队列中的比较
    bool operator<(const HuffmanNode& other) const {
        return weight > other.weight; // 按权重升序排序，生成最小堆
    }
};

BinaryTreeNode* createNode(const char& data, const int &weight,BinaryTreeNode* left = nullptr, BinaryTreeNode* right = nullptr) {
    return new BinaryTreeNode(data, weight,left, right);
}

BinaryTree huffmanTree(vector<int>weight, vector<char>c,int n) {
    // 创建 Huffman 节点数组
    HuffmanNode* hNode = new HuffmanNode[n];
    for (int i = 0; i < n; i++) {
        hNode[i].weight = weight[i];
        hNode[i].tree.root = createNode(c[i],weight[i]);
    }

    priority_queue<HuffmanNode> H(hNode, hNode + n);

    while (H.size() > 1) {
        HuffmanNode x = H.top();
        H.pop();
        HuffmanNode y = H.top();
        H.pop();

        HuffmanNode z;
        z.weight = x.weight + y.weight;
        z.tree.root = createNode('/0',(x.weight + y.weight));
        z.tree.root->LeftChild = x.tree.root;
        z.tree.root->RightChild = y.tree.root;

        H.push(z);
    }

    // 返回 Huffman 树的根节点
    return H.top().tree;
}

class CodeAndChar {
public:
    vector<string>code;
    vector<char> eachChar;
    BinaryTree huff;
    CodeAndChar(vector<string>co, vector<char>ec,BinaryTree h) :code(co), eachChar(ec),huff(h) {};
};
class Package {
public:
    //getCode的初始的code要先开n个空间，nowString传入空字符串
    void getCode(BinaryTreeNode* root,vector<char>& eachChar, vector<string>& code, string nowString) {
        if (root->LeftChild == NULL && root->RightChild == NULL) {
            char c = root->data;
            auto it = find(eachChar.begin(), eachChar.end(), c);
            int index = distance(eachChar.begin(), it);
            code[index] = nowString;
            return;
	
        }
        getCode(root->LeftChild, eachChar, code, nowString + '0');
        getCode(root->RightChild, eachChar, code, nowString + '1');
    }

    CodeAndChar commpression(string str) {
        vector<int> weight;
        vector<char>eachChar;
        
        for (char c : str) {
            auto it = find(eachChar.begin(), eachChar.end(), c);
            if (it != eachChar.end()) {
                int index = distance(eachChar.begin(), it);
                weight[index]++;
            }
            else {
                weight.push_back(1);
                eachChar.push_back(c);
            }
        }
        BinaryTree huff = huffmanTree(weight, eachChar,eachChar.size());
        vector<string>code(eachChar.size(),"");
        getCode(huff.root, eachChar,code,"");
        CodeAndChar cac(code, eachChar,huff);
        return cac;
    }

    string getCommpressedString(CodeAndChar cac, string str) {
        string res = "";
        for (char c : str) {
            auto it = find(cac.eachChar.begin(), cac.eachChar.end(), c);
			
            int index = distance(cac.eachChar.begin(), it);
            
            res += cac.code[index];
            
        }
        return res;
    }


    
    string decoding(CodeAndChar cac,string str) {
        vector<string>code = cac.code;
        vector<char>eachChar = cac.eachChar;
        string res = "";
        string temp="";
        for (char c : str) {
            temp += c;
            auto it = find(code.begin(), code.end(), temp);
            if (it != code.end()) {
                int index = distance(code.begin(), it);
                res += eachChar[index];
                temp = "";
            }
	
        }
        return res;

    };

    

};
int main() {
  /*  cout << "测试建树功能:" << endl;
    vector<char> arr = { 'a','b','c','d','e'};
    vector<int>  weight = { 3,2,3,5,1};
    BinaryTree Huffman = huffmanTree(weight,arr, 5);
    Huffman.Print(Huffman.root);*/
    
    cout << "测试压缩功能:" << endl;
    string testStr = "aaabbcccddddddde";
    Package p;
    CodeAndChar cac=p.commpression(testStr);
    cac.huff.Print(cac.huff.root);
    for (int i = 0; i < cac.code.size(); i++) {
        cout << "char " << cac.eachChar[i] << ':' << cac.code[i] << endl;
    }
    string res = p.getCommpressedString(cac, testStr);
    cout << "encoded string is:" << res<<endl;
    string res2 = p.decoding(cac, res);
    cout << "decoded string is:" << res2 << endl;
    return 0;
}
