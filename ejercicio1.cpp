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


int main()
{
    AVL<Book> *library = new AVL<Book>();

    int lines;
    cin >> lines;
    Command *commands = loadCommands(lines);
    Command command;
    for (int i = 0; i <= lines; i++)
    {
        command = commands[i];
      if (command.type == "ADD") {
        Book book(command.id, command.data, true);
        library->insert(book);
      } else if (command.type == "FIND") {
          cout << "FIND" << '\n';
      } else if (command.type == "TOGGLE") {
          cout << "TOGGLE" << '\n';
      } else if (command.type == "COUNT") {
          cout << "COUNT" << '\n';
      } else {
        cout << "Command not handled" << '\n';
      }
    }


    return 0;
}