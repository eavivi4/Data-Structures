#include <iostream>

// Change into my queue later
#include <queue>

using namespace std;

class BinaryNode {
public:
    int data;
    BinaryNode* left;
    BinaryNode* right;

    BinaryNode(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

class BinaryTree {
    BinaryNode* root;
public:
    BinaryTree() {
        root = nullptr;
    }

    void insert(int element) {
        BinaryNode* newNode = new BinaryNode(element);
        if(!root)
        {
            // If root does not exist, make current node the root
            root = newNode;
            return;
        }

        // Have a queue to keep track of children
        queue<BinaryNode*> q;
        q.push(root);
        while(!q.empty())
        {
            BinaryNode* curr = q.front();
            q.pop();
            if (curr->left == nullptr)
            {
                // Insert from the left first
                curr->left = newNode;
                return;
            }
            else if (curr->right == nullptr)
            {
                // Insert from the right next
                curr->right = newNode;
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
        return;
    }

    void remove(int element) {
        if (root == nullptr)
        {
                return;
        }

        // Base case, if the element is the root
        if (root->data == element)
        {
            BinaryNode* saveRoot = root;
            if (root->right == nullptr)
            {
                // Right side is empty
                root = root->left;
            }
            else if (root->left == nullptr)
            {
                // Left side is empty
                root = root->right;
            }
            
            // If root has two children
            BinaryNode* iterate = root;
            while (iterate->right != nullptr)
            {
                iterate = iterate->right;
            }
            iterate->right = saveRoot->right;
            // CONTINUE?
            return;
        }

        // Have a queue to keep track of children
        queue<BinaryNode*> q;
        q.push(root);
        while(!q.empty())
        {
            BinaryNode* curr = q.front();
            q.pop();

            // Traverse until element is found
            if (curr->left != nullptr)
            {
                if (curr->left->data == element)
                {
                    // Remove left child
                    BinaryNode* child = curr->left;
                    if(!child->left && !child->right)
                    {
                        delete child;
                        return;
                    }
                    // CONTINUE? with function?
                    return;
                }
                q.push(curr->left);
            }
            if (curr->right != nullptr)
            {
                if (curr->right->data == element)
                {
                    // Remove right child
                    BinaryNode* child = curr->right;
                    if(!child->left && !child->right)
                    {
                        delete child;
                        return;
                    }
                    // CONTINUE? with function?
                    return;
                }
                q.push(curr->right);
            }
        }
    }

    bool lookUpRec(BinaryNode* curr, int element) {
        bool left, right;
        // Pre order traversal recursion
        if(curr->data == element)
        {
            return true;
        }
        if (curr->left)
        {
            left = lookUpRec(curr->left, element);
        }
        if (curr->right)
        {
            right = lookUpRec(curr->right, element);
        }
    
        // If the elements exists in one of the branches
        if (left || right)
        {
            return true;
        }
        return false;
    }

    bool lookup(int element) {
        if(root->data == element)
        {
            // If element is the root
            return true;
        }
        // Recurse on the root;
        return lookUpRec(root, element);
    }

    void printRec(BinaryNode* curr) {
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

class BinarySearchTree {
    BinaryNode* root;
public:
    BinarySearchTree() {
        root = nullptr;
    }

    void insert(int element) {
        BinaryNode* newNode = new BinaryNode(element);
        if(!root)
        {
            // If root does not exist, make current node the root
            root = newNode;
            return;
        }

        // Insert node in appropriate place
        BinaryNode* curr = root;
        while (curr != nullptr)
        {
            if (element > curr->data  && curr->right == nullptr)
            {
                curr->right = newNode;
                return;
            }
            else if (element < curr->data && curr->left == nullptr)
            {
                curr->left = newNode;
                return;
            }
            else if (element > curr->data)
            {
                curr = curr->right;
            }
            else
            {
                curr = curr->left;
            }
        }
        return;
        
    }

    void removeWithTwoChild(BinaryNode* curr, BinaryNode* parent)
    {
        if (parent == nullptr)
        {
            // Remove root
            //CONINUE?
            return;
        }
    }

    void removeCases(char side, BinaryNode* curr, BinaryNode* parent) {
        
        if (curr->right == nullptr)
        {
            // No right child, see which side of parent to connect
            switch(side)
            {
                case 'L':
                    parent->left = curr->left;
                    break;
                case 'R':
                    parent->right = curr->left;
                    break;
            }
            delete curr;
        }
        else if (curr->left == nullptr)
        {
            // No left child, see which side of parent to connect
            switch(side)
            {
                case 'L':
                    parent->left = curr->right;
                    break;
                case 'R':
                    parent->right = curr->right;
                    break;
            }
            delete curr;
        }
        else
        {
            // Two children
            removeWithTwoChild(curr, parent);
        }
        return;
    }

    void remove(int element) {
        if (root->data == element)
        {
            // Remove root
            removeWithTwoChild(root, nullptr);
            return;
        }
        BinaryNode* curr = root;
        BinaryNode* parent = root;
        while (curr != nullptr && curr->data != element)
        {
            if (element > curr->data)
            {
                parent = curr;
                curr = curr->right;
            }
            else
            {
                parent = curr;
                curr = curr->left;
            }
        }
            
        // Remove element by checking which case it is
        if (curr->right == nullptr && curr->left == nullptr)
        {
            // If not children, delete node
            delete curr;
        }
        else if (curr == parent->left)
        {
            removeCases('L', curr, parent);
        }
        else
        {
            removeCases('R', curr, parent);
        }

        return;

    }

    bool lookup(int element) {

        if(root->data == element)
        {
            // Base case, check the root
            return true;
        }

        // Iterative Binary Search Tree lookup
        BinaryNode* curr = root;
        while (curr != nullptr)
        {
            if (element > curr->data)
            {
                // If element is greater than current node, go right
                curr = curr->right;
            }
            else if (element < curr->data)
            {
                // If element is smaller than current node, go left
                curr = curr->left;
            }
            else if (element == curr->data)
            {
                return true;
            }
        }

        // Element not found in tree
        return false;
    }

    void printRec(BinaryNode* curr) {
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

class Trie {

};

class BTree {

};

int main() {
    cout << "Binary Tree: " << endl;
    BinaryTree* bintree = new BinaryTree();
    bintree->insert(1);
    bintree->print();
    bintree->insert(2);
    bintree->print();
    bintree->insert(3);
    bintree->print();
    bintree->insert(40);
    bintree->print();
    bintree->insert(0);
    bintree->print();
    bintree->insert(9);
    bintree->print();
    bintree->insert(7);
    bintree->print();
    bintree->insert(11);
    bintree->print();
    // Remove leaf
    // bintree->remove(11);
    // // Remove in the middle
    // bintree->remove(3);
    // // Remove root
    // bintree->remove(1);

    // FIX THIS SO IT SAYS TRUE OR FALSE INSTEAD OF 1 OR 0
    cout << "Eleven is in the tree: " << bintree->lookup(11) << endl;
    cout << "One is in the tree: " << bintree->lookup(1) << endl;
    cout << "Four is in the tree: " << bintree->lookup(4) << endl;

    cout << "Binary Search Tree: " << endl;
    BinarySearchTree* bstree = new BinarySearchTree();
    bstree->insert(9);
    bstree->print();
    bstree->insert(7);
    bstree->print();
    bstree->insert(1);
    bstree->print();
    bstree->insert(2);
    bstree->print();
    bstree->insert(3);
    bstree->print();
    bstree->insert(40);
    bstree->print();
    bstree->insert(0);
    bstree->print();
    bstree->insert(11);
    bstree->print();
    // // Remove leaf
    // bstree->remove(11);
    // // Remove in the middle with one leaf
    // // Left
    // bstree->remove(7);
    // // Right
    // bstree->remove(2);
    // // Remove in the middle with two leafs
    // bstree->remove(1);
    // // Remove root
    // bstree->remove(9);

    // FIX THIS SO IT SAYS TRUE OR FALSE INSTEAD OF 1 OR 0
    cout << "Twelve is in the tree: " << bstree->lookup(12) << endl;
    cout << "Zero is in the tree: " << bstree->lookup(0) << endl;
    cout << "Nine is in the tree: " << bstree->lookup(9) << endl;
    return 0;
}