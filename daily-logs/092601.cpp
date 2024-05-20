#include <iostream>

using namespace std; 
//交替融合链表
class Node {
public:
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
    Node():data(-1),next(nullptr){}
};

Node* melt(Node* head1, Node* head2) {
    if (!head1) return head2;
    if (!head2) return head1;

    Node* mergedHead = head1; 
    cout << "插入1list的" << head1->data << endl;
    head1 = head1->next;
    Node* current = mergedHead;
    
    while (head1 && head2) {
       
        current->next = head2;
        cout << "插入2list的" << head2->data<<endl;
        head2 = head2->next;
        current = current->next;
        

        current->next = head1;
        cout << "插入1list的" << head1->data<<endl;
        head1 = head1->next;
        current = current->next;
    }

    
    if (head1) {
        current->next = head1;
        cout << "插入1list的" << head1->data <<"and后面的数据" << endl;
    }
    if (head2) {
        current->next = head2;
        cout << "插入2list的" << head2->data <<"and后面的数据"<< endl;
    }

   
    Node* result = mergedHead;
    
    return result;
}

void printList(Node* head) {
    while (head) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    Node* head1 = new Node();
    Node* head2 = new Node();
    Node* cur1 = head1;
    Node* cur2 = head2;
    int n1, n2;
    cin >> n1 >> n2;
    for (int i = 0; i < n1; i++)
    {
        int num;
        cin >> num;
        cur1->data = num;
        if (i != n1 - 1) {
            Node* temp = new Node();
            cur1->next = temp;
            cur1 = cur1->next;
        }
    }
    
    for (int i = 0; i < n2; i++)
    {
        int num;
          cin >> num;
        cur2->data = num;
        if (i != n2 - 1) {
            Node* temp = new Node();
            cur2->next = temp;
            cur2 = cur2->next;
        }
    }
    printList(head1);
    printList(head2);
    Node* mergedHead = melt(head1, head2);
    
    printList(mergedHead);

    return 0;
}
