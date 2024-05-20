#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void genSubUtil(int index, string currentSubset, const vector<char>& elements,vector<string>&res) {
    if (index == elements.size()) {

        res.push_back(currentSubset);
        return;
    }

    // 产生含当前元素的子集
    genSubUtil(index + 1, currentSubset + elements[index] + " ", elements, res);

    // 产生不包含当前元素的子集
    genSubUtil(index + 1, currentSubset, elements, res);
}

void genSubsets(int n, vector<string>&res) {
    if (n < 1 || n > 26) {
        cout << "WRONG" << endl;
        return;
    }

    vector<char> elements;
    for (int i = 0; i < n; i++) {
        elements.push_back('a' + i);
    }

    
    
    genSubUtil(0, "", elements, res);
    cout << endl;

    
}

int main() {
    int n;
   ifstream inputFile("data.txt");
    if (!inputFile.is_open()) {
        cout << "WRONG" << endl;
        return 0;
    }

    inputFile >> n;
    inputFile.close();

    vector<string>res;
    genSubsets(n,res);
    for (string s : res) {
        cout<< s << endl;
    }

    return 0;
}
