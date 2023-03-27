#include <iostream>

#include "teachable_dictionary.hpp"
#include "hash_table.hpp"

static int execute();
static int command_handler(const std::string &command,
                           my_containers::hash_table<std::string, dictionary::teachable_dictionary> &dictionaries);
static int execute_run(my_containers::hash_table<std::string, dictionary::teachable_dictionary> &dictionaries,
                       const bool is_byte);
static int execute_read(my_containers::hash_table<std::string, dictionary::teachable_dictionary> &dictionaries);
static int execute_correct(my_containers::hash_table<std::string, dictionary::teachable_dictionary> &dictionaries);

enum { WITHOUT_ERRORS, ERROR };

int main(int argc, char **argv)
{
    std::cout << "teachable dictionary manager executing" << std::endl;
    std::cout << "input command (h -- for help, q -- for exit)" << std::endl;

    return execute();
}

int execute()
{
    my_containers::hash_table<std::string, dictionary::teachable_dictionary> dictionaries;

    std::string command {};
    std::cin >> command;

    while (command != "q" && command != "quit") {
        command_handler(command, dictionaries);

        std::cin >> command;
    }

    return 1;
}

int command_handler(const std::string &command,
                    my_containers::hash_table<std::string, dictionary::teachable_dictionary> &dictionaries)
{
    if (command == "h" || command == "help") {
        std::cout << "dictionary manager help menu" << std::endl;
    } else if (command == "r" || command == "run") {
        if (!execute_run(dictionaries, false)) {
            return ERROR;
        }
    } else if (command == "rb" || command == "runb") {
        if (!execute_run(dictionaries, true)) {
            return ERROR;
        }
    } else if (command == "read_text") {
        if (!execute_read(dictionaries)) {
            return ERROR;
        }
    } else if (command == "correct_text") {
        if (!execute_correct(dictionaries)) {
            return ERROR;
        }
    }

    else {
        std::cout << "unknown command \"" << command << "\", please try again" << std::endl;
    }

    return WITHOUT_ERRORS;
}

int execute_run(my_containers::hash_table<std::string, dictionary::teachable_dictionary> &dictionaries,
                const bool is_byte)
{
    std::string dic_name {};
    std::cin >> dic_name;
    std::string data_path {};
    std::cin >> data_path;

    if (dictionaries.find(dic_name) != dictionaries.end()) {
        std::cout << "dictionary already opened" << std::endl;
        return WITHOUT_ERRORS;
    }

    dictionaries.emplace(dic_name,
                         dictionary::teachable_dictionary {PROJECT_DIR_PATH + std::string {"/"} + data_path, is_byte});

    return WITHOUT_ERRORS;
}

int execute_read(my_containers::hash_table<std::string, dictionary::teachable_dictionary> &dictionaries)
{
    std::string dic_name {};
    std::cin >> dic_name;
    std::string text_path {};
    std::cin >> text_path;

    auto dictionary_itr = dictionaries.find(dic_name);
    if (dictionary_itr == dictionaries.end()) {
        std::cout << "unknown dictionary: " << dic_name << std::endl;
        return WITHOUT_ERRORS;
    }

    if (!dictionary_itr->second.read_text(PROJECT_DIR_PATH + text_path.insert(0, 1, '/'))) {
        return ERROR;
    }

    return WITHOUT_ERRORS;
}

int execute_correct(my_containers::hash_table<std::string, dictionary::teachable_dictionary> &dictionaries)
{
    std::string dic_name {};
    std::cin >> dic_name;
    std::string text_path {};
    std::cin >> text_path;

    auto dictionary_itr = dictionaries.find(dic_name);
    if (dictionary_itr == dictionaries.end()) {
        std::cout << "unknown dictionary: " << dic_name << std::endl;
        return WITHOUT_ERRORS;
    }

    if (!dictionary_itr->second.correct_text(PROJECT_DIR_PATH + text_path.insert(0, 1, '/'))) {
        return ERROR;
    }

    return WITHOUT_ERRORS;
}
