#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include <sstream>
#include "./tads/AVL.cpp"
#include "./models/Command.cpp"
#include "./models/Book.cpp"
#include "./funciones/io.cpp"

using namespace std;

AVL<Book> *library = new AVL<Book>();

void add(Command command) {
    Book book(command.id, command.data, true);
    library->insert(book);
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
        found = library->find(book);
    } else {
        cout << "libro_no_encontrado" << '\n';
    }
};


int main()
{
    int lines;
    cin >> lines;
    Command *commands = loadCommands(lines);
    Command command;
    for (int i = 1; i <= lines; i++)
    {
        command = commands[i];
      if (command.type == "ADD") {
          add(command);
      } else if (command.type == "FIND") {
          find(command);
      } else if (command.type == "TOGGLE") {
          toggle(command);
      } else if (command.type == "COUNT") {
          cout << "COUNT" << '\n';
      } else {
        cout << "Command not handled" << '\n';
      }
    }


    return 0;
}