#ifndef COMMAND
#define COMMAND
#include <stdlib.h>
#include <iostream>
using namespace std;

class Command
{
public:
    int id = 0;
    string type = "";
    string data = "";
    Command(string params)
    {
        stringstream source(params);
        string param;
        int i = 0;
        while (getline(source, param, ' ')) {
            switch (i) {
                case 0:
                    this->type = param;
                break;
                case 1:
                    this->id = std::stoi( param );
                break;
                case 2:
                    this->data = param;
                break;
            }
            i++;
        }
    }
    Command(){}
    string toString() {
        return this->type + " " + std::to_string(this->id) + " " + this->data;
    }
};

#endif