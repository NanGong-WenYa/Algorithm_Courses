#include <iostream>

using namespace std;
//数据结构10.8日链表拆分存于原空间
// 定义双向链表节点结构
class Node {
public:
    int data;
    Node* next;
    Node* prev;
    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

// 函数用于拆分链表并在原地重组
void splitAndReorganize(Node* head) {
    if (!head || !head->next) {
        // 如果链表为空或只有一个节点，不需要拆分和重组
        cout << "No need for reorganize";
        return;
    }

    Node* oddHead = head;
    Node* evenHead = head->next;

    Node* odd = oddHead;
    Node* even = evenHead;

    // 分别迭代奇数和偶数节点，将它们串联在一起（第一节点视为0节点）
    while (even && even->next) {
        odd->next = even->next;//把当前odd节点与下一个odd节点用next链接
        even->next->prev = odd;//把下一个odd节点与当前odd节点用prev链接
        odd = odd->next;//odd节点后移
        even->next = odd->next;//把当前even节点与下一个even节点用next链接
        if (odd->next) {
            odd->next->prev = even;//把下一个even节点与当前even节点用prev链接
        }
        even = even->next;//even节点后移
    }

    // 将奇链表和偶链表的末尾节点指向nullptr
    odd->next = nullptr;
    even->next = nullptr;

    // 打印奇链表
    cout << "奇链表: ";
    while (oddHead) {
        cout << oddHead->data << " ";
        oddHead = oddHead->next;
    }
    cout << endl;

    // 打印偶链表
    cout << "偶链表: ";
    while (evenHead) {
        cout << evenHead->data << " ";
        evenHead = evenHead->next;
    }
    cout << endl;
}

int main() {
    // 创建一个双向链表
    Node* head = new Node(1);
    Node* current = head;
    for (int i = 2; i <= 22; i++) {
        current->next = new Node(i);
        current->next->prev = current;
        current = current->next;
    }

    cout << "原始链表: ";
    current = head;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;

    // 调用拆分和重组函数
    splitAndReorganize(head);

    return 0;
}