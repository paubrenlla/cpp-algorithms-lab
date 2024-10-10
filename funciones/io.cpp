#include "../models/Command.cpp"

Command* loadCommands(int amount) {

    Command *commands = new Command[amount]();
    string line;
    string type = "";
    int id = 0;
    string data = "";
    for (int i = 0; i < amount; i++)
    {
        cin >> type;
        if (type == "ADD") {
            cin >> id;
            cin >> data;
        } else if (type == "FIND" || type == "TOGGLE") {
            cin >> id;
        }
        Command command(type, id, data);
        commands[i] = command;
        id = 0;
        data = "";
    }
    return commands;
}