#include <iostream>

#include "teachable_dictionary.hpp"
#include "hash_table.hpp"

static int execute ();
static int command_handler (const std::string& command, my_containers::hash_table<std::string, dictionary::teachable_dictionary>& dictionaries);
static int execute_run(my_containers::hash_table<std::string, dictionary::teachable_dictionary>& dictionaries);
enum {
    WITHOUT_MISTAKES, 
    ERROR
};

int main(int argc, char **argv) {
    std::cout << "teachable dictionary manager executing" << std::endl;
    std::cout << "input command (h -- for help, q -- for exit)" << std::endl;

    return execute ();
}

int execute ()
{
    my_containers::hash_table<std::string, dictionary::teachable_dictionary> dictionaries;

    std::string command {};
    std::cin >> command;

    while (command != "q" && command != "quit")
    {
        command_handler (command, dictionaries);

        std::cin >> command;
    }

    return 1;
}   

int command_handler (const std::string& command, my_containers::hash_table<std::string, dictionary::teachable_dictionary>& dictionaries)
{
    if (command == "h" || command == "help")
    {
        std::cout << "dictionary manager help menu" << std::endl;
    }
    else if (command == "r" || command == "run")
    {
        if (!execute_run(dictionaries))
        {
            return ERROR;
        }
    }

    else
    {
        std::cout << "unknown command \"" << command << "\", please try again" << std::endl;
    }

    return WITHOUT_MISTAKES;
}

int execute_run(my_containers::hash_table<std::string, dictionary::teachable_dictionary>& dictionaries)
{
    std::string dic_name {};
    std::cin >> dic_name;
}

