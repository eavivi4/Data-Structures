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

class LinkedList {
    Node* head;
public:
    LinkedList() {
        head = nullptr;
    }

    void insert(int element)
    {
        Node* newNode = new Node(element);
        if (head)
        {
            // If head exists, add from the end
            Node* curr = head;
            while (curr->next != nullptr)
            {
                curr = curr->next;
            }
            curr->next = newNode;
        }
        else
        {
            // Have a new head
            head = newNode;
        }
        return;
    }

    void remove(int element) {

        // If node is head, remove from the start and set new head
        if (head->data == element)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        // Otherwise
        Node* curr = head;
        while (curr->next != nullptr)
        {
            Node* nextNode = curr->next;
            if (nextNode->data == element && nextNode->next != nullptr)
            {
                curr->next = nextNode->next;
                delete nextNode;
                return;
            }
            else if (nextNode->next == nullptr)
            {
                // If node is at the end
                curr->next = nullptr;
                delete nextNode;
                return;
            }
            curr = nextNode;
        }
        return;
    }

    void reverse() {

        // Base case, no need to reverse
        if (head->next == nullptr)
        {
            return;
        }
        Node* curr = head;
        Node* nextNode = curr->next;
        while (nextNode != nullptr)
        {
            // Switch the direction of the next pointer
            Node* saveNext = nextNode->next;
            nextNode->next = curr;
            curr = nextNode;
            nextNode = saveNext;

        }

        // Switch the head
        head->next = nullptr;
        head = curr;
    }

    void print() {
        Node* curr = head;
        while (curr != nullptr)
        {
            cout << curr->data << " -> ";
            curr = curr->next;
        }
        cout << endl;
        return;
    }
};

class DoublyNode {
public:
    int data;
    DoublyNode* next;
    DoublyNode* prev;

    DoublyNode(int value) {
        data = value;
        next = nullptr;
        prev = nullptr;
    }
};

class DoublyLinkedList {
    DoublyNode* head;
    DoublyNode* tail;
public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    void insert(int element)
    {
        DoublyNode* newNode = new DoublyNode(element);
        if (head)
        {
            // If head exists, add from the end
            DoublyNode* curr = head;
            while (curr->next != nullptr)
            {
                curr = curr->next;
            }
            curr->next = newNode;
            newNode->prev = curr;
            tail = newNode;
        }
        else
        {
            // New head and tail, pointing to same node
            head = newNode;
            tail = newNode;
        }
        return;
    }

    void remove(int element) {

        // If node is head
        if (head->data == element)
        {
            DoublyNode* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        // Otherwise
        DoublyNode* curr = head;
        while (curr->next != nullptr)
        {
            DoublyNode* nextNode = curr->next;
            if (nextNode->data == element && nextNode->next != nullptr)
            {
                DoublyNode* newNext = nextNode->next;
                curr->next = newNext;
                newNext->prev = curr;
                delete nextNode;
                return;
            }
            curr = nextNode;
        }

        if (curr->data == element)
        {
            // If the node to delete is the tail
            tail = curr->prev;
            curr->prev->next = nullptr;
            delete curr;
        }
        
        return;
    }

    void print() {
        DoublyNode* curr = head;
        while (curr != tail)
        {
            cout << curr->data << " <-> ";
            curr = curr->next;
        }
        cout << tail->data << " -> " << endl;
        return;
    }

    void printReverse() {
        cout << "<- " << tail->data;
        DoublyNode* curr = tail;
        while (curr != head)
        {
            cout << " <-> " << curr->data;
            curr = curr->prev;
        }
        cout << " <-> " << head->data << endl;
        return;
    }
};

int main() {
    cout << "Linked List: " << endl;
    LinkedList* list = new LinkedList();
    list->insert(1);
    list->print();
    list->insert(8);
    list->print();
    list->insert(68);
    list->print();
    list->insert(33);
    list->print();
    list->insert(4);
    list->print();
    list->insert(92);
    list->print();
    // Remove from start
    list->remove(1);
    list->print();
    // Remove from end
    list->remove(92);
    list->print();
    // Remove from middle
    list->remove(33);
    list->print();
    list->insert(55);
    list->print();
    list->reverse();
    list->print();

    cout << "Doubly Linked List: " << endl;
    DoublyLinkedList* Dlist = new DoublyLinkedList();
    Dlist->insert(78);
    Dlist->print();
    Dlist->insert(100);
    Dlist->print();
    Dlist->insert(22);
    Dlist->print();
    Dlist->insert(3);
    Dlist->print();
    Dlist->insert(0);
    Dlist->print();
    Dlist->insert(6);
    Dlist->print();
    // Remove from end
    Dlist->remove(6);
    Dlist->print();
    // Remove from middle
    Dlist->remove(3);
    Dlist->print();
    // Remove from start
    Dlist->remove(78);
    Dlist->print();
    Dlist->printReverse();
    return 0;
}