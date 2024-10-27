#include <string>
#include <iostream>
#include "./tads/HashTableOpenAddressing.cpp"
#include "./models/Book.cpp"
#include "./models/Command.cpp"
#include "./funciones/io.cpp"

using namespace std;

HashTableOpenAddressing<int, Book> *library;
int total = 0;
int enabled = 0;
int disabled = 0;

unsigned int hash1(const int& value) {
    return value * 8;
}
unsigned int hash2(const int& value) {
    return value * 40;
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