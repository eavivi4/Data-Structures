#include <iostream>
#include <queue>
#include <vector>

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

class Tree {
protected:
    BinaryNode* root;
public:
    Tree() {
        root = nullptr;
    }

    void removeWithTwoChild(BinaryNode* curr)
    {
        if (!curr)
        {
            return;
        }
        bool left = false;
        // Go to leftmost node in right subtree
        BinaryNode* replacement = curr->right;
        BinaryNode* p_replace = curr;

        // Right node is predecessor, save it's right children (not a leaf node)
        if (replacement->left == nullptr)
        {
            curr->data = replacement->data;
            curr->right = replacement->right;
            return;
        }
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
        return;
    }
};

class BinaryTree : public Tree {
public:

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

        // If no tree, no need to remove
        if (root == nullptr)
        {
            return;
        }

        // Base case, if the element is the root
        if (root->data == element)
        {
            // Remove root
            removeWithTwoChild(root);
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
                        // Remove node with no children
                        delete child;
                        curr->left = nullptr;
                        return;
                    }
                    if (!child->left)
                    {
                        // Remove node with right child
                        curr->left = child->right;
                        delete child;
                        return;
                    }
                    if (!child->right)
                    {
                        // Remove node with left child
                        curr->left = child->left;
                        delete child;
                        return;
                    }
                    else
                    {
                        // Remove node with two children
                        removeWithTwoChild(child);
                        return;
                    }
                    
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
                        // Remove node with no children
                        curr->right = nullptr;
                        delete child;
                        return;
                    }
                    else if (!child->left)
                    {
                        // Remove node with right child
                        curr->right = child->right;
                        delete child;
                        return;
                    }
                    else if (!child->right)
                    {
                        // Remove node with left child
                        curr->right = child->left;
                        delete child;
                        return;
                    }
                    else
                    {
                        // Remove node with two children
                        removeWithTwoChild(child);
                        return;
                    }
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

class BinarySearchTree : public Tree {
public:

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
            removeWithTwoChild(curr);
        }
        return;
    }

    void remove(int element) {
        if (root->data == element)
        {
            // Remove root
            removeWithTwoChild(root);
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
            // If not children, delete node, NOT DELETING?
            if(parent->left == curr)
            {
                parent->left = nullptr;
            }
            else
            {
                parent->right = nullptr;
            }
            delete curr;
            // cout << "HERE" << curr->data << endl;
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

class TrieNode {
public:
    bool isComplete;
    TrieNode* children[];
    TrieNode() {
        isComplete = false;
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};

class Trie {
    TrieNode* root;
public:
    Trie() {
        // Not used, just a starting point
        root = new TrieNode();
    }
    void insert(string word) {
        TrieNode* curr = root;
        cout << word.size() << endl;
        for (int i = 0; i < word.size(); i++)
        {
            char letter = word[i];
            // If word is not a child of current, make it
            if (curr->children[letter - 'a'] == nullptr) {

                //PROBLEM HERE?
                cout << letter - 'a' << endl;
                curr->children[letter - 'a'] = new TrieNode();
                cout << letter - 'a' << endl;
            }
            
            // Move to that child to continue with inserting characters anyways
            curr = curr->children[letter - 'a'];
            cout << "YO" << endl;
        }
        cout << word.size() << endl;
        // Set the completion of the word
        curr->isComplete = true;
        //NOT RETURNING?
    }

    bool search(string word) {
        TrieNode* curr = root;
        for (int i = 0; i < word.size(); i++)
        {
            // If current char does not exist, return false
            if (!curr->children[word[i] - 'a'])
            {
                return false;
            }
            // Move to that child to continue with search if the character does exist in Trie
            curr = curr->children[word[i] - 'a'];
        }
        if (curr->isComplete)
        {
            return true;
        }
        return false;
    }

    bool startsWith(string prefix) {
        TrieNode* curr = root;
        for (int i = 0; i < prefix.size(); i++)
        {
            // If current char does not exist, return false
            if (!curr->children[prefix[i] - 'a'])
            {
                return false;
            }
            // Move to that child to continue with search if the character does exist in Trie
            curr = curr->children[prefix[i] - 'a'];
        }
        
        // Does not need to check if char is complete
        return true;
    }
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
    bintree->remove(11);
    bintree->print();
    // Remove in the middle
    bintree->remove(3);
    bintree->print();
    // Remove root
    bintree->remove(1);
    bintree->print();

    // Remove with one child

    // Left
    bintree->insert(6);
    bintree->print();
    bintree->remove(7);
    bintree->print();

    // Right (removing 40 to have only one child)
    bintree->remove(40);
    bintree->remove(0);
    bintree->print(); 

    // FIX THIS SO IT SAYS TRUE OR FALSE INSTEAD OF 1 OR 0
    string b = "false";
    if (bintree->lookup(11))
    {
        b = "true";
    }
    cout << "Eleven is in the tree: " <<  b << endl;
    b = "false";
    if (bintree->lookup(9))
    {
        b = "true";
    }
    cout << "Nine is in the tree: " << b << endl;
    b = "false";
    if (bintree->lookup(4))
    {
        b = "true";
    }
    cout << "Four is in the tree: " << b << endl;

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
    bstree->remove(11);
    bstree->print();
    // Remove in the middle with one leaf
    // Left
    bstree->remove(7);
    bstree->print();
    // Right
    bstree->remove(2);
    bstree->print();
    // Remove in the middle with two leafs
    bstree->remove(1);
    bstree->print();
    // Remove root
    bstree->remove(9);
    bstree->print();

    // CHANGE TO FUNCTION?
    b = "false";
    if (bstree->lookup(12))
    {
        b = "true";
    }
    cout << "Twelve is in the tree: " << b << endl;
    b = "false";
    if(bstree->lookup(0))
    {
        b = "true";
    }
    cout << "Zero is in the tree: " << b << endl;
    b = "false";
    if(bstree->lookup(9))
    {
        b = "true";
    }
    cout << "Nine is in the tree: " << b << endl;


    // cout << "Trie: " << endl;
    // Trie* tr = new Trie();
    // tr->insert("bpel");
    // cout << "END" << endl;
    // trie->search("apple");   // return True
    // trie->search("app");     // return False
    // trie->startsWith("app"); // return True
    // trie->insert("app");
    // trie->search("app");     // return True

    return 0;
}