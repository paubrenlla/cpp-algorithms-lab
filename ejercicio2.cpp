#include <cassert>
#include <string>
#include <iostream>
#include <limits>
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
    HashTableOpenAddressing<std::string, int> library(10, hash1, hash2);
    return 0;
}