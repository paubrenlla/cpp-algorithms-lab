#ifndef BOOK
#define BOOK
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

#endif