#include "../models/Command.cpp"

Command* loadCommands(int lines) {

    Command *commands = new Command[lines]();
    string line;

    int i = 0;
    while (getline(cin, line))
    {
        Command command(line);
        commands[i] = command;
        i++;
    }
    return commands;
}