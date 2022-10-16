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

class Queue {
    Node* front;
    Node* back;
public:
    Queue() {
        front = nullptr;
        back = nullptr;
    }

    int getFront() {
        return front->data;
    }

    int getBack() {
        return back->data;
    }

    void push(int value) {
        Node* newNode = new Node(value);
        if (!front)
        {
            // If front doesn't exist, create it and back
            front = newNode;
            back = newNode;
            return;
        }
        
        // Add in the back of the queue
        Node* curr = front;
        while (curr->next != nullptr)
        {
            curr = curr->next;
        }
        curr->next = newNode;
        back = newNode;
        return;
    }

    void pop() {
        if (!front)
        {
            // List is empty
            return;
        }
        Node* curr = front;
        front = curr->next;
        delete curr;
        return;
    }

    void print() {
        Node* curr = front;
        while (curr != nullptr)
        {
            cout << curr->data << " -> ";
            curr = curr->next;
        }
        cout << endl;
        return;
    }
};

class PriorityQueue{

};

int main() {
    cout << "Regular Queue: " << endl;
    Queue* q = new Queue();
    q->push(1);
    q->print();
    q->push(2);
    q->print();
    q->push(3);
    q->print();
    q->push(4);
    q->print();
    cout << "Front: " << q->getFront() << " Back: " << q->getBack() << endl;
    q->push(5);
    q->print();
    q->push(6);
    q->print();
    q->pop();
    q->print();
    cout << "Front: " << q->getFront() << " Back: " << q->getBack() << endl;
    q->pop();
    q->print();
    q->push(1);
    q->print();
    q->push(2);
    q->print();
    cout << "Front: " << q->getFront() << " Back: " << q->getBack() << endl;
    return 0;
}