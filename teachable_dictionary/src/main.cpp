#include <iostream>

#include "teachable_dictionary.hpp"

static int execute ();
static int command_handler (const std::string& command);

int main(int argc, char **argv) {
    std::cout << "teachable dictionary manager executing" << std::endl;
    std::cout << "input command (h -- for help, q -- for exit)" << std::endl;

    return execute ();
}

int execute ()
{
    std::string command {};

    std::cin >> command;

    while ((command != "q") && (command != "quit"))
    {
        command_handler (command);

        std::cin >> command;
    }

    return 1;
}   

int command_handler (const std::string& command)
{
    if (command == "help")
    {
        std::cout << "dictionary manager help menu" << std::endl;
    }

    else
    {
        std::cout << "unknown command \"" << command << "\", please try again" << std::endl;
    }

    return 1;
}

