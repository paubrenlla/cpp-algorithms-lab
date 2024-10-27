#include "Table.h"
#ifndef HASHTABLE_OPEN_ADDRESSING
#define HASHTABLE_OPEN_ADDRESSING
#include <string>
using namespace std;

template <class K, class V>
class HashTableOpenAddressing : public Table<K, V>
{
private:
	class Bucket {
    public:
        K key;
        V value;
        bool empty;
        bool deleted;
    };

    int size;
    int (*hash1)(const K&);
    int (*hash2)(const K&);
    int counter;
    Bucket* table;
    bool* deleted;

    bool isFull () {
        return counter == size;
    }

    int getBucketIndex(K key, int retry) {
        return abs((hash1(key) + retry * hash2(key))) % size;
    }

    void insertInBucket(K key, V value, int retry) {
        int index = this->getBucketIndex(key, retry);
        if (this->table[index].empty) {
            this->table[index].key = key;
            this->table[index].value = value;
            this->table[index].empty = false;
        } else if (this->table[index].key == key) {
            this->table[index].value = value;
        } else {
            this->insertInBucket(key, value, ++retry);
        }
    }

    V getInBucket(K key, int retry) {
        V value;
        int index = this->getBucketIndex(key, retry);
        Bucket bucket = this->table[index];
        if (bucket.key == key)
        {
            value = bucket.value;
        } else if(!bucket.empty) {
            value = getInBucket(key, ++retry);
        }

        return value;
    }

public:
    HashTableOpenAddressing(
        int size, int (*hash1)(const K&), int (*hash2)(const K&)):
        size(size), hash1(hash1), hash2(hash2) {
        this->table = new Bucket[size]();
        this->deleted = new bool[size]();
        this->counter = 0;
        for (int i = 0; i < size; ++i) {
            this->table[i].empty = true;
        }
    }

    ~HashTableOpenAddressing() {
        delete[] this->table;
        delete[] this->deleted;
    }

    void insert(K key, V value) override {
        assert(!this->isFull());
        int retry = 0;
        this->insertInBucket(key, value, retry);
    }

    V get(K key) override {
        V value;
        int retry = 0;
        return this->getInBucket(key, retry);
    }

    bool exists(K key) override {
        return false;
    }

    void remove(K key) override {}

};

#endif
