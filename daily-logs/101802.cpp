#include <iostream>
using namespace std;

template <typename T>
class Stack {
private:
    T* data;
    int size;
    int capacity;

public:
    Stack(int capacity) {
        this->capacity = capacity;
        this->size = 0;
        data = new T[capacity];
    }

    

    void push(const T& item) {
        if (size < capacity) {
            data[size++] = item;
        }
        else {
            cout << "Stack is full. Cannot push more items." << endl;
        }
    }

    T pop() {
        if (!empty()) {
            T x = this->top();
            --size;
            return x;
        }
        else {
            cout << "Stack is empty. Cannot pop." << endl;
        }
    }

    T& top() {
        if (!empty()) {
            return data[size - 1];
        }
        else {
            throw runtime_error("Stack is empty");
        }
    }

    bool empty() {
        return size == 0;
    }

    int getSize() {
        return size;
    }
    void deleteAll(T x) {
        Stack tempStack(this->capacity);
        int times = size;
        for (int i = 0; i < times; i++) {
            if (this->top() != x) {
                cout << "tempStack got " << this->top()<<endl;
                tempStack.push(this->pop());
                
                }
            else {
                cout << this->top() << "have been poped" << endl;
                this->pop();
            }

        }
        while (!tempStack.empty()) {
            this->push(tempStack.pop());
        }
        

    }
};

int main() {
    Stack<char> myStack(6);

    myStack.push('a');
    myStack.push('b');
    myStack.push('c');
    myStack.push('a');
    myStack.push('d');
    myStack.push('a');

    myStack.deleteAll('a');
    while (!myStack.empty()) {
        cout << myStack.pop() << ' ';
    }

    return 0;
}
