#include <string>
#include <iostream>
#include "./tads/HashTableOpenAddressing.cpp"
#include "./models/Book.cpp"
#include "./models/Command.cpp"
#include "./funciones/io.cpp"
#define MAX_SIZE 10000001ll

using namespace std;

HashTableOpenAddressing<int, Book> *library;
int total = 0;
int enabled = 0;
int disabled = 0;
bitset<MAX_SIZE> isPrime;
int PRIME;

void setSieveEratosthenes(){
    isPrime[0] = isPrime[1] = 1;
    for(long long i = 2; i*i <= MAX_SIZE; i++) {
        if(isPrime[i] == 0) {
            for(long long j = i*i; j <= MAX_SIZE; j += i) {
                isPrime[j] = 1;
            }
        }
    }
}

int hash1(const int& value) {
    return value;
}
int hash2(const int& value) {
    return PRIME - (value % PRIME);
}

void add(Command command) {
    Book book(command.id, command.data, true);
    Book found = library->get(book.id);
    if (found.id > 0) {
        if (!found.enabled) {
            enabled++;
            disabled--;
        }
        found.title = book.title;
        found.enabled = true;
        library->insert(found.id, found);
    } else {
        library->insert(book.id, book);
        enabled++;
        total++;
    }
};

void find(Command command) {
    Book found = library->get(command.id);
    string response = found.id == 0 ? "libro_no_encontrado" : found.toString();
    cout << response << '\n';
};

void toggle(Command command) {
    Book found = library->get(command.id);
    if (found.id > 0) {
        found.enabled = !found.enabled;
        library->insert(found.id, found);

        if (found.enabled) {
            enabled++;
            disabled--;
        } else {
            enabled--;
            disabled++;
        }
    } else {
        cout << "libro_no_encontrado" << '\n';
    }
};

void count() {
    cout << std::to_string(total) + " " + std::to_string(enabled) + " " + std::to_string(disabled) << '\n';
}

int main()
{
    int size;
    cin >> size;

    PRIME = size - 1;
    while(isPrime[PRIME] == 1) {
        PRIME--;
    }

    library = new HashTableOpenAddressing<int, Book>(size, hash1, hash2);
    const Command *commands = loadCommands(size);
    for (int i = 0; i <= size; i++)
    {
        Command command = commands[i];
        if (command.type == "ADD") {
            add(command);
        } else if (command.type == "FIND") {
            find(command);
        } else if (command.type == "TOGGLE") {
            toggle(command);
        } else if (command.type == "COUNT") {
            count();
        }
    }
    return 0;
}