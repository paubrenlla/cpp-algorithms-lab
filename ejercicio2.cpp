#include <string>
#include <iostream>
#include "./tads/HashTableOpenAddressing.cpp"
#include "./models/Book.cpp"

using namespace std;

unsigned int hash1(const std::string& str) {
    unsigned int hash = 0;
    for (int i = 0; i < str.length(); ++i) {
        hash = hash * 31 + str[i];
    }
    return hash;
}
unsigned int hash2(const std::string& str) {
    unsigned int hash = 0;
    for (int i = 0; i < str.length(); ++i) {
        hash = hash * 31 + str[i];
    }
    return hash;
}

int main()
{
    int size;
    cin >> size;
    HashTableOpenAddressing<std::string, int> library(size, hash1, hash2);
    return 0;
}