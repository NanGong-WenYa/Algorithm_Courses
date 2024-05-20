#include <iostream>
using namespace std;
template <typename T, typename KeyType>
class ListNode {
public:
    T data;
    ListNode* next;

    ListNode(T val) : data(val), next(nullptr) {}
};

template <typename T, typename KeyType>
class hashChainsWithTail {
public:

	int size;
    ListNode<T, KeyType>** table;
	
    hashChainsWithTail(int tableSize);
   

    void insert(const T& value, const KeyType& key);
    bool remove(const KeyType& key);
    void display();


    

    // 辅助函数，查找链表中的尾节点
    ListNode<T, KeyType>* findTail(ListNode<T, KeyType>* head);

    // 哈希函数，根据关键字返回哈希桶索引
    int hash(const KeyType& key);
};

template <typename T, typename KeyType>
hashChainsWithTail<T, KeyType>::hashChainsWithTail(int tableSize) : size(tableSize) {
    table = new ListNode<T, KeyType>* [size]();
}


template <typename T, typename KeyType>
void hashChainsWithTail<T, KeyType>::insert(const T& value, const KeyType& key) {
    int index = hash(key);

    if (!table[index]) {
        // 如果哈希桶为空，创建新节点
        table[index] = new ListNode<T, KeyType>(value);
    }
    else {
        // 否则，在链表尾部插入新节点
        ListNode<T, KeyType>* tail = findTail(table[index]);
        tail->next = new ListNode<T, KeyType>(value);
    }
}

template <typename T, typename KeyType>
bool hashChainsWithTail<T, KeyType>::remove(const KeyType& key) {
    int index = hash(key);
    ListNode<T, KeyType>* current = table[index];
    ListNode<T, KeyType>* prev = nullptr;

    while (current) {
        if (current->data == key) {
            if (prev) {
                prev->next = current->next;
            }
            else {
                // 如果要删除的节点是链表的头节点
                table[index] = current->next;
            }
            delete current;
            return true;
        }

        prev = current;
        current = current->next;
    }

    return false;
}

template <typename T, typename KeyType>
void hashChainsWithTail<T, KeyType>::display() {
    for (int i = 0; i < size; i++) {
        ListNode<T, KeyType>* current = table[i];
        cout << "Bucket " << i << ": ";
        while (current) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "nullptr" << std::endl;
    }
}

template <typename T, typename KeyType>
ListNode<T, KeyType>* hashChainsWithTail<T, KeyType>::findTail(ListNode<T, KeyType>* head) {
    if (!head) return nullptr;

    ListNode<T, KeyType>* tail = head;
    while (tail->next) {
        tail = tail->next;
    }

    return tail;
}

template <typename T, typename KeyType>
int hashChainsWithTail<T, KeyType>::hash(const KeyType& key) {
    // 简单的取余哈希函数
    return key % size;
}

int main() {
    hashChainsWithTail<int, int> hashTable(10);

    // 插入一些元素
    hashTable.insert(10, 10);
    hashTable.insert(20, 20);
    hashTable.insert(30, 10);
    hashTable.insert(40, 5);

    // 显示哈希表
    hashTable.display();

    // 删除元素
    hashTable.remove(10);

    // 显示更新后的哈希表
    hashTable.display();

    return 0;
}
