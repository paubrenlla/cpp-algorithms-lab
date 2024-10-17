#ifndef HASHTABLE_OPEN_ADDRESSING
#define HASHTABLE_OPEN_ADDRESSING
#include <stdlib.h>
#include <iostream>
#include <algorithm>
using namespace std;

template <class T, class V>
class HashTableOpenAddressing
{
private:
	class Bucket {
    public:
        T key;
        V value;
        bool empty;
        bool deleted;
    };

    int size;
    unsigned int (*hash1)(const T&);
    unsigned int (*hash2)(const T&);
    int counter;
    Bucket* table;
    bool* deleted;
public:
    HashTableOpenAddressing(
        int size, unsigned int (*hash1)(const T&), unsigned int (*hash2)(const T&)):
        size(size), hash1(hash1), hash2(hash2) {
        this->table = new Bucket[size]();
        this->deleted = new bool[size]();
        for (int i = 0; i < size; i++) {
            cout << "Table" << '\n';
            cout << "Empty " + std::string(this->table[i].empty ? "true" : "false") << '\n';
            cout << "Deleted " + std::string(this->table[i].deleted ? "true" : "false") << '\n';
            cout << "Deleted in array " + std::string(this->deleted[i] ? "true" : "false") << '\n';
        }
    }

};


#endif