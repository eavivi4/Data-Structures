#include <iostream>
#include <queue>
using namespace std;

class BinaryHeapNode {
public:
    int data;
    BinaryHeapNode* left;
    BinaryHeapNode* right;
    BinaryHeapNode* parent;

    BinaryHeapNode(int value) {
        data = value;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }
};

// Heap using Binary Tree implementation
class Heap {
protected:
    BinaryHeapNode* root;
public:
    Heap() {
        root = nullptr;
    }
    BinaryHeapNode* removeWithTwoChild(BinaryHeapNode* curr)
    {
        if (!curr)
        {
            return nullptr;
        }
        bool left = false;
        // Go to leftmost node in right subtree
        BinaryHeapNode* replacement = curr->right;
        BinaryHeapNode* p_replace = curr;
        while (replacement->left != nullptr)
        {
            left = true;
            p_replace = replacement;
            replacement = replacement->left;
        }
        // Put contents of replacement node into 
        curr->data = replacement->data;
        
        if(left)
        {
            p_replace->left = nullptr;
        }
        else
        {
            p_replace->right = nullptr;
        }

        
        delete replacement;
        replacement = nullptr;
        return p_replace;
    }

    void printRec(BinaryHeapNode* curr) {
        // Pre order traversal print
        if (curr)
        {
            cout << curr->data << " ";
        }
        if (curr->left)
        {
            // Print left tree
            printRec(curr->left);
        }
        if (curr->right)
        {
            // Print right tree
            printRec(curr->right);
        }
        return;
    }

    void print() {
        // Print recursively
        printRec(root);
        cout << endl;
        return;
    }
};

class MinHeap : public Heap {
    BinaryHeapNode* min;
public:
    MinHeap() {
        min = root;
    }

    void heapSortMin(BinaryHeapNode* curr) {
        // Start from newly inserted node and bubble up until root to balance
        while (curr->parent != nullptr)
        {
            if (curr->data < curr->parent->data)
            {
                // Bubble up the min value
                int temp = curr->data;
                curr->data = curr->parent->data;
                curr->parent->data = temp;
            }
            curr = curr->parent;
        }
        return;
        
    }

    void insert(int element) {
        BinaryHeapNode* newNode = new BinaryHeapNode(element);
        if(!root)
        {
            // If root does not exist, make current node the root
            root = newNode;
            return;
        }

        // Have a queue to keep track of children
        queue<BinaryHeapNode*> q;
        q.push(root);
        while(!q.empty())
        {
            BinaryHeapNode* curr = q.front();
            q.pop();
            if (curr->left == nullptr)
            {
                // Insert from the left first
                curr->left = newNode;
                newNode->parent = curr;
                heapSortMin(newNode);
                return;
            }
            else if (curr->right == nullptr)
            {
                // Insert from the right next
                curr->right = newNode;
                newNode->parent = curr;
                heapSortMin(newNode);
                return;
            }

            // Add to queue to look at later
            if (curr->left != nullptr)
            {
                q.push(curr->left);
            }
            if (curr->right != nullptr)
            {
                q.push(curr->right);
            }
        }

        heapSortMin(newNode);
        return;

    }

    int getMin() {
        return min->data;
    }

    // void remove(int element) {

    //     // If no tree, no need to remove
    //     if (root == nullptr)
    //     {
    //         return;
    //     }

    //     // Base case, if the element is the root
    //     if (root->data == element)
    //     {
    //         // Remove root
    //         BinaryHeapNode* balance = removeWithTwoChild(root);
    //         heapSortMin(balance);
    //         return;
    //     }

    //     // Have a queue to keep track of children
    //     queue<BinaryHeapNode*> q;
    //     q.push(root);
    //     while(!q.empty())
    //     {
    //         BinaryHeapNode* curr = q.front();
    //         q.pop();

    //         // Traverse until element is found
    //         if (curr->left != nullptr)
    //         {
    //             if (curr->left->data == element)
    //             {
    //                 // Remove left child
    //                 BinaryHeapNode* child = curr->left;
    //                 if(!child->left && !child->right)
    //                 {
    //                     // Remove node with no children
    //                     delete child;
    //                     curr->left = nullptr;
    //                     heapSortMin(curr);
    //                     return;
    //                 }
    //                 else if (!child->left)
    //                 {
    //                     // Remove node with right child
    //                     curr->left = child->right;
    //                     delete child;
    //                     heapSortMin(curr);
    //                     return;
    //                 }
    //                 else if (!child->right)
    //                 {
    //                     // Remove node with left child
    //                     curr->left = child->left;
    //                     delete child;
    //                     heapSortMin(curr);
    //                     return;
    //                 }
    //                 else
    //                 {
    //                     // Remove node with two children
    //                     removeWithTwoChild(child);
    //                     heapSortMin(curr);
    //                     return;
    //                 }
                    
    //             }
    //             q.push(curr->left);
    //         }
    //         if (curr->right != nullptr)
    //         {
    //             if (curr->right->data == element)
    //             {
    //                 // Remove right child
    //                 BinaryHeapNode* child = curr->right;
    //                 if(!child->left && !child->right)
    //                 {
    //                     // Remove node with no children
    //                     curr->right = nullptr;
    //                     delete child;
    //                     heapSortMin(curr);
    //                     return;
    //                 }
    //                 else if (!child->left)
    //                 {
    //                     // Remove node with right child
    //                     curr->right = child->right;
    //                     delete child;
    //                     heapSortMin(curr);
    //                     return;
    //                 }
    //                 else if (!child->right)
    //                 {
    //                     // Remove node with left child
    //                     curr->right = child->left;
    //                     delete child;
    //                     heapSortMin(curr);
    //                     return;
    //                 }
    //                 else
    //                 {
    //                     // Remove node with two children
    //                     removeWithTwoChild(child);
    //                     heapSortMin(curr);
    //                     return;
    //                 }
    //             }
    //             q.push(curr->right);
    //         }
    //     }
    // }
};

class MaxHeap : public Heap {
    BinaryHeapNode* max;
public:
    MaxHeap() {
        max = root;
    }

    void heapSortMax(BinaryHeapNode* curr) {
        // Start from newly inserted node and bubble up until root to balance
        while (curr->parent != nullptr)
        {
            if (curr->data > curr->parent->data)
            {
                // Bubble up the max value
                int temp = curr->data;
                curr->data = curr->parent->data;
                curr->parent->data = temp;
            }
            curr = curr->parent;
        }
        return;
    }

    void insert(int element) {
        BinaryHeapNode* newNode = new BinaryHeapNode(element);
        if(!root)
        {
            // If root does not exist, make current node the root
            root = newNode;
            return;
        }

        // Have a queue to keep track of children
        queue<BinaryHeapNode*> q;
        q.push(root);
        while(!q.empty())
        {
            BinaryHeapNode* curr = q.front();
            q.pop();
            if (curr->left == nullptr)
            {
                // Insert from the left first
                curr->left = newNode;
                newNode->parent = curr;
                heapSortMax(newNode);
                return;
            }
            else if (curr->right == nullptr)
            {
                // Insert from the right next
                curr->right = newNode;
                newNode->parent = curr;
                heapSortMax(newNode);
                return;
            }

            // Add to queue to look at later
            if (curr->left != nullptr)
            {
                q.push(curr->left);
            }
            if (curr->right != nullptr)
            {
                q.push(curr->right);
            }
        }

        heapSortMax(newNode);
        return;

    }

    int getMax() {
        return max->data;
    }
    
    // void remove(int element) {

    //     // If no tree, no need to remove
    //     if (root == nullptr)
    //     {
    //         return;
    //     }

    //     // Base case, if the element is the root
    //     if (root->data == element)
    //     {
    //         // Remove root
    //         BinaryHeapNode* balance = removeWithTwoChild(root);
    //         heapSortMax(balance);
    //         return;
    //     }

    //     // Have a queue to keep track of children
    //     queue<BinaryHeapNode*> q;
    //     q.push(root);
    //     while(!q.empty())
    //     {
    //         BinaryHeapNode* curr = q.front();
    //         q.pop();

    //         // Traverse until element is found
    //         if (curr->left != nullptr)
    //         {
    //             if (curr->left->data == element)
    //             {
    //                 // Remove left child
    //                 BinaryHeapNode* child = curr->left;
    //                 if(!child->left && !child->right)
    //                 {
    //                     // Remove node with no children
    //                     delete child;
    //                     curr->left = nullptr;
    //                     heapSortMax(curr);
    //                     return;
    //                 }
    //                 else if (!child->left)
    //                 {
    //                     // Remove node with right child
    //                     curr->left = child->right;
    //                     delete child;
    //                     heapSortMax(curr);
    //                     return;
    //                 }
    //                 else if (!child->right)
    //                 {
    //                     // Remove node with left child
    //                     curr->left = child->left;
    //                     delete child;
    //                     heapSortMax(curr);
    //                     return;
    //                 }
    //                 else
    //                 {
    //                     // Remove node with two children
    //                     removeWithTwoChild(child);
    //                     heapSortMax(curr);
    //                     return;
    //                 }
                    
    //             }
    //             q.push(curr->left);
    //         }
    //         if (curr->right != nullptr)
    //         {
    //             if (curr->right->data == element)
    //             {
    //                 // Remove right child
    //                 BinaryHeapNode* child = curr->right;
    //                 if(!child->left && !child->right)
    //                 {
    //                     // Remove node with no children
    //                     curr->right = nullptr;
    //                     delete child;
    //                     heapSortMax(curr);
    //                     return;
    //                 }
    //                 else if (!child->left)
    //                 {
    //                     // Remove node with right child
    //                     curr->right = child->right;
    //                     delete child;
    //                     heapSortMax(curr);
    //                     return;
    //                 }
    //                 else if (!child->right)
    //                 {
    //                     // Remove node with left child
    //                     curr->right = child->left;
    //                     delete child;
    //                     heapSortMax(curr);
    //                     return;
    //                 }
    //                 else
    //                 {
    //                     // Remove node with two children
    //                     removeWithTwoChild(child);
    //                     heapSortMax(curr);
    //                     return;
    //                 }
    //             }
    //             q.push(curr->right);
    //         }
    //     }
    // }
};

int main() {
    cout << "Min Heap: " << endl;
    MinHeap* minh = new MinHeap();
    minh->insert(9);
    minh->print();
    minh->insert(7);
    minh->print();
    minh->insert(1);
    minh->print();
    minh->insert(2);
    minh->print();
    minh->insert(3);
    minh->print();
    minh->insert(40);
    minh->print();
    minh->insert(0);
    minh->print();
    minh->insert(11);
    minh->print();
    // Remove min
    // minh->remove(0);


    cout << "Max Heap: " << endl;
    MaxHeap* maxh = new MaxHeap();
    maxh->insert(9);
    maxh->print();
    maxh->insert(7);
    maxh->print();
    maxh->insert(1);
    maxh->print();
    maxh->insert(2);
    maxh->print();
    maxh->insert(3);
    maxh->print();
    maxh->insert(40);
    maxh->print();
    maxh->insert(0);
    maxh->print();
    maxh->insert(11);
    maxh->print();
    return 0;
}