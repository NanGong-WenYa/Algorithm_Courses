#include <iostream>
using namespace std;
//双向链表重新开空间拆
class Node {
public:
    int data; 
    Node* prev;
    Node* next;

    Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
public:
    Node* head;
    Node* tail;
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    void addToFront(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void addToEnd(int value) {
        Node* newNode = new Node(value);
        if (!tail) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void display() const {
        Node* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
    void split(DoublyLinkedList& a, DoublyLinkedList& b) {
        Node* cur = this->head;
        int index = 1;
        while(cur!=NULL){
            if (index % 2 != 0) {
                a.addToEnd(cur->data);
                index++;
                cur = cur->next;
            }
            else {
                b.addToEnd(cur->data);
                index++;
                cur = cur->next;
            }
        }
    }
    
};

int main() {
    DoublyLinkedList c,a,b;
    int n;
    cin >> n;
   
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        c.addToEnd(m);
    }
    c.split(a, b);

    
    a.display();
    b.display();


    return 0;
}
