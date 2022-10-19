#include <iostream>
#include <vector>

using namespace std;
class HashPair {
public:
    int key;
    string value;
    HashPair(int k, string v)
    {
        key = k;
        value = v;
    }
};

class HashTable {
    int length;
    vector<HashPair*>* data;
public:
    HashTable(int size) {
        length = size;
        data = new vector<HashPair*>[length];
    }

    int hash(int key) {
        return key % length;
    }

    void set(int key, string value) {
        // Put element into the bucket address
        int address = hash(key);
        HashPair* hp = new HashPair(key, value);
        data[address].push_back(hp);
        return;
    }

    string getValue(int key)
    {
        int address = hash(key);
        // Find the value that fits the key, inside bucket address
        for (int i = 0; i < data[address].size(); i++)
        {
            if (data[address][i]->key == key)
            {
                return data[address][i]->value;
            }
        }

        // If not found, return message that it is not
        return "not in hash table.";
    }

    void print() {
        for (int i = 0; i < length; i++)
        {
            // i is each bucket, j is each hash pair within the bucket
            cout << "Element " << i << " : ";
            for (int j = 0; j < data[i].size(); j++)
            {
                if(data[i][j])
                {
                    cout << data[i][j]->key << " : " << data[i][j]->value << " ";
                }
            }
            cout  << endl;
        }
    }
};

int main() {
    HashTable* hashTable = new HashTable(5);
    hashTable->set(10, "why");
    hashTable->print();
    hashTable->set(4, "where");
    hashTable->print();
    hashTable->set(1, "how");
    hashTable->print();
    hashTable->set(88, "who");
    hashTable->print();
    hashTable->set(7, "what");
    hashTable->print();
    // Have more than one value inside a bucket
    hashTable->set(2, "would");
    hashTable->print();
    cout << "Value of one is " << hashTable->getValue(1) << endl;;
    cout << "Value of ten is " << hashTable->getValue(10) << endl;
    cout << "Value of two is " << hashTable->getValue(2) << endl;
    cout << "Value of seven is " << hashTable->getValue(7) << endl;
    cout << "Value of three is " << hashTable->getValue(3) << endl;
}