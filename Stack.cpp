#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

class Stack {
    Node* top;
public:
    Stack() {
        top = nullptr;
    }

    int getTop() {
        return top->data;
    }

    void push(int value) {
        Node* newNode = new Node(value);
        if (!top)
        {
            // If top doesn't exist, create it
            top = newNode;
            return;
        }
        
        // Replace the top
        Node* curr = top;
        top = newNode;
        top->next = curr;
        return;
    }

    void pop() {
        if (!top)
        {
            // List is empty
            return;
        }
        // Save node before changing pointer, to delete it later
        Node* curr = top;
        top = curr->next;
        delete curr;
        return;
    }

    void print() {
        Node* curr = top;
        while (curr != nullptr)
        {
            cout << curr->data << " -> ";
            curr = curr->next;
        }
        cout << endl;
        return;
    }
};

int main() {
    Stack* s = new Stack();
    s->push(1);
    s->print();
    s->push(2);
    s->print();
    s->push(3);
    s->print();
    s->push(4);
    s->print();
    cout << "Top: " << s->getTop() << endl;
    s->push(5);
    s->print();
    s->push(6);
    s->print();
    s->pop();
    s->print();
    cout << "Top: " << s->getTop() << endl;
    s->pop();
    s->print();
    s->push(1);
    s->print();
    s->push(2);
    s->print();
    cout << "Top: " << s->getTop() << endl;
    return 0;
}