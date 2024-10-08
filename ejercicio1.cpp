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

    for (int i = 0; i <= lines; i++)
    {
      if (commands[i].type == "ADD") {
          cout << "ADD" << '\n';
      } else if (commands[i].type == "FIND") {
          cout << "FIND" << '\n';
      } else if (commands[i].type == "TOGGLE") {
          cout << "TOGGLE" << '\n';
      } else if (commands[i].type == "COUNT") {
          cout << "COUNT" << '\n';
      } else {
        cout << "Command not handled" << '\n';
      }
    }


    return 0;
}