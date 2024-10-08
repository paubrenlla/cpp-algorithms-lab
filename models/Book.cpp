#ifndef BOOK
#define BOOK
using namespace std;

class Book
{
public:
    int id = 0;
    string title = "";
    bool enabled = false;
    Book(int id, string title, bool enabled)
    {
        this->id = id;
        this->title = title;
        this->enabled = enabled;
    }
    Book(){}
    string toString() {
        string status = this->enabled ? "H" : "D";
        return this->title + " " + status;
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

#endif