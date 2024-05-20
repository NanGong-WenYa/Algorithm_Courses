#include<iostream>
using namespace std;
template<class E, class K>
class HashTable {
public:
    HashTable(int divisor = 11);
    ~HashTable() { delete[] ht;  delete[] empty; }
    bool Search(const K& k, E& e) const;
    HashTable<E, K>& Insert(const E& e);
    void Output();// output the hash table
    bool deleteKey(const K&);
    bool fullUsed();
    bool deleteKit(const K& );

    int hSearch(const K& k) const;
    int m; // hash function divisor
    E* ht; // hash table array
    bool* empty; // 1D array
    bool* neverUsed;

};

template<class E, class K>
HashTable<E, K>::HashTable(int divisor)
{// Constructor.
    m = divisor;

    // allocate hash table arrays
    ht = new E[m];
    empty = new bool[m];
    neverUsed = new bool[m];

    // set all buckets to empty
    for (int i = 0; i < m; i++)
    {
        neverUsed[i] = true;
        empty[i] = true;
    }
}
template<class E, class K>
int HashTable<E, K>::hSearch(const K& k) const
{// Search an open addressed table.
 // Return location of k if present.
 // Otherwise return insert point if there is space.
    int i = k % m; // home bucket
    int j = i;     // start at home bucket
    do {
        if (empty[j] || ht[j] == k) return j;
        j = (j + 1) % m;  // next bucket
    } while (j != i); // returned to home?

    return j;  // table full
}
template<class E, class K>
bool HashTable<E, K>::Search(const K& k, E& e) const
{// Put element that matches k in e.
 // Return false if no match.
    int b = hSearch(k);
    if (empty[b] || ht[b] != k) return false;
    e = ht[b];
    return true;
}

template<class E, class K>
HashTable<E, K>& HashTable<E, K>::Insert(const E& e)
{// Hash table insert
    K k = e; // extract key
    int b = hSearch(k);

    // check if insert is to be done
    if (empty[b]) {
        empty[b] = false;
        neverUsed[b] = false;
        ht[b] = e;
        return *this;
    }

    // no insert, check if duplicate or full
    if (ht[b] == e) cout << "这个元素已经插入过了" << endl; // duplicate
    
    return *this;  // Visual C++ needs this line
}

template<class E, class K>
bool HashTable<E, K>::fullUsed() {
    K cnt = 0;
    for (int i = 0; i < m; i++) {
        if (neverUsed[i] == false)
            cnt++;
    }
    if (cnt > (0.6 * m))return true;
    else return false;
}
// template<class E,class K>
// bool HashTable<E, K>:: deleteKit(const K& key) {
    // int index = key % m;
    // while (ht[index] != key&&ht[index]!=NULL) {
        // index++;
    // }
    // if (ht[index] == NULL || ht[index] != key)
    // {
        // cout << "deleting" << ' ' << key << ' ' << "can't be done" << endl;
        // return false;
    // }
    // ht[index] =NULL;
    // empty[index] = true;
// }

template<class E, class K>
bool HashTable<E, K>::deleteKey(const K& k) {
    int index = hSearch(k);
    if (empty[index] || ht[index] != k) {
        cout << "Deleting " << k << " cannot be done. It does not exist in the table." << endl;
        return false;
    }

    ht[index] = E();
    empty[index] = true;

    // 检查是否需要重新分配空间
    if (fullUsed()) {
        int oldSize = m;
        m = m * 2;  // 分配两倍的空间

        E* oldHt = ht;
        bool* oldEmpty = empty;

        // 分配新空间
        ht = new E[m];
        empty = new bool[m];
        neverUsed = new bool[m];

        // 初始化neverUsed和empty数组
        for (int i = 0; i < m; i++) {
            neverUsed[i] = true;
            empty[i] = true;
        }

        //重新插入所有e类型元素
        for (int i = 0; i < oldSize; i++) {
            if (!oldEmpty[i] && oldHt[i] != E()) {
                Insert(oldHt[i]);
            }
        }

        delete[] oldHt;
        delete[] oldEmpty;
    }

    return true;
}


int main() {
    HashTable<int, int> myHashTable(11);

    // 插入一些元素
    for (int i = 1; i <= 15; i++) {
        myHashTable.Insert(i * 10);
    }

    // 输出哈希表
    cout << "Hash Table after insertions:" << endl;
    for (int i = 0; i < myHashTable.m; i++) {
        if (!myHashTable.empty[i]) {
            cout << "Index " << i << ": " << myHashTable.ht[i] << endl;
        }
    }
    

    // // 查找元素
    // int value;
    // if (myHashTable.Search(50, value)) {
        // cout << "Found element 50 at index, value = " << value << endl;
    // }
    // else {
        // cout << "Element 50 not found." << endl;
    // }

    // 删除元素
    if (myHashTable.deleteKey(50)) {
        cout << "Deleted element 50." << endl;
    }
    else {
        cout << "Failed to delete element 50." << endl;
    }

    // 输出哈希表
    cout << "Hash Table after deletion:" << endl;
    for (int i = 0; i < myHashTable.m; i++) {
        if (!myHashTable.empty[i]) {
            cout << "Index " << i << ": " << myHashTable.ht[i] << endl;
        }
    }
    cout << myHashTable.empty[myHashTable.hSearch(10)];
    return 0;
}

