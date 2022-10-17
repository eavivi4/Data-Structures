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

class PriorityNode {
public:
    int data;
    int priority;
    PriorityNode* next;

    PriorityNode(int value, int rank) {
        data = value;
        priority = rank;
        next = nullptr;
    }
};

class PriorityQueue{
    PriorityNode* front;
    PriorityNode* back;
public:
    PriorityQueue()
    {
        front = nullptr;
        back = nullptr;
    }
    int getFront() {
        return front->data;
    }

    int getBack() {
        return back->data;
    }

    void push(int value, int priority) {
        PriorityNode* newNode = new PriorityNode(value, priority);
        PriorityNode* temp = front;
        if (front == nullptr)
        {
            // If queue is empty
            front = newNode;
            back = newNode;
            return;
        }

        if (front->priority > priority)
        {
            // Insert before front
            temp = front;
            front = newNode;
            front->next = temp;

            return;
        }
        
        PriorityNode* curr = front;
        while (curr->next != nullptr)
        {
            if (curr->next->priority > priority)
            {
                // Insert before next element
                temp = curr->next;
                curr->next = newNode;
                newNode->next = temp;
                
                return;
            }
            else
            {
                // Continue to next element in queue
                curr = curr->next;
            }
        }

        // Add last element
        curr->next = newNode;
        back = newNode;
        return;
    }

    void pop() {
        
        // Pops the element with the most priority, which is in the front
        if (!front)
        {
            // List is empty
            return;
        }
        PriorityNode* curr = front;
        front = curr->next;
        delete curr;
        return;
    }

    void print() {
        PriorityNode* curr = front;
        while (curr != nullptr)
        {
            cout << "#" << curr->priority << " " << curr->data << " -> ";
            curr = curr->next;
        }
        cout << endl;
        return;
    }
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

    cout << "Priority Queue: " << endl;
    PriorityQueue* pq = new PriorityQueue();
    pq->push(1,4);
    pq->print();
    pq->push(2,3);
    pq->print();
    pq->push(3,1);
    pq->print();
    pq->push(4,2);
    pq->print();
    cout << "Front: " << pq->getFront() << " Back: " << pq->getBack() << endl;
    pq->push(5,8);
    pq->print();
    pq->push(6,6);
    pq->print();
    pq->pop();
    pq->print();
    cout << "Front: " << pq->getFront() << " Back: " << pq->getBack() << endl;
    pq->pop();
    pq->print();
    pq->push(1,1);
    pq->print();
    pq->push(2,5);
    pq->print();
    cout << "Front: " << pq->getFront() << " Back: " << pq->getBack() << endl;
    return 0;
}