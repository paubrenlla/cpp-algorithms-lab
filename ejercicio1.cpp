#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "./tads/AVL.cpp"

using namespace std;

class Book
{
public:
    int id;
    string title;
    bool enabled;
    Book(int id, string title, bool enabled)
    {
        this->id = id;
        this->title = title;
        this->enabled = enabled;
    }

    bool operator<(const Book& other) const
    {
      return this->id < other.id;
    }
    bool operator>(const Book& other) const
    {
        return this->id > other.id;
    }
    bool operator==(const Book& other)
    {
        return this->id == other.id;
    }
};

int main()
{
  AVL<Book> *library = new AVL<Book>();

    int lines;
    cin >> lines;

    string *vec = new string[lines];
    string line;
    int i = 0;
    while (getline(cin, line))
    {
        vec[i] = line;
        i++;
    }


    for (int i = 0; i < lines; i++)
    {
        cout << vec[i] << '\n';
    }


    return 0;
}