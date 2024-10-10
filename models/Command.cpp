#ifndef COMMAND
#define COMMAND
using namespace std;

class Command
{
public:
    int id = 0;
    string type = "";
    string data = "";
    Command(string type, int id, string data){
        this->id = id;
        this->type = type;
        this->data = data;
    }
    Command(){}
    string toString() {
        return this->type + " " + std::to_string(this->id) + " " + this->data;
    }
};

#endif