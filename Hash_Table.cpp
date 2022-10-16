#include <iostream>

using namespace std;

class HashTable {
    int length;
    string data[];
public:
    HashTable(int size) {
        length = size;

        // Change?
        data[length];
    }

    int hash(int key) {
        return key % length;
    }

    int set(int key, string value) {
        int address = hash(key);
        // Continue
    }

    string getValue(int key)
    {
        int address = hash(key);
        // Change?
        return data[address];
    }
};

int main() {
    HashTable* hashTable = new HashTable(3);
    hashTable->set(10, "why");
    hashTable->set(4, "where");
    hashTable->set(1, "how");
    hashTable->set(88, "who");
    hashTable->getValue(1);
    hashTable->getValue(10);
}