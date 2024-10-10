#include <cassert>
#include <string>
#include <iostream>
#include "./tads/AVL.cpp"
#include "./models/Command.cpp"
#include "./models/Book.cpp"
#include "./funciones/io.cpp"

using namespace std;

AVL<Book> *library = new AVL<Book>();
int total = 0;
int enabled = 0;
int disabled = 0;

void add(Command command) {
    Book book(command.id, command.data, true);
    Book found = library->find(book);
    if (found.id > 0) {
        if (!found.enabled) {
            enabled++;
            disabled--;
        }
        found.title = book.title;
        found.enabled = true;
        library->insert(found);
    } else {
        library->insert(book);
        enabled++;
        total++;
    }
};

void find(Command command) {
    Book book(command.id, command.data, true);
    Book found = library->find(book);
    string response = found.id == 0 ? "libro_no_encontrado" : found.toString();
    cout << response << '\n';
};

void toggle(Command command) {
    Book book(command.id, command.data, true);
    Book found = library->find(book);
    if (found.id > 0) {
        found.enabled = !found.enabled;
        library->insert(found);

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
    int lines;
    cin >> lines;
    Command *commands = loadCommands(lines);
    Command command;
    for (int i = 0; i <= lines; i++)
    {
        command = commands[i];
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