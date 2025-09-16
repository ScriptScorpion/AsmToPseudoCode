#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <array>
constexpr std::array commands {
    "xor",
    "and",
    "or",
    "not",
    "shr",
    "sar",
    "shl",
    "mov",
    "add",
    "sub",
    "mul",
    "imul",
};
std::string search1(const std::string word) {
    std::string result = "";
    int i = 0;
    for (; word[i] != ' '; ++i) {
        // just adjust counter to position
    }
    ++i; // + 1 because right now cursor at space position
    for (; std::isalnum(word[i]); ++i) {
        result += word[i];
    }
    return result;
}

std::string search2(const std::string word) {
    std::string result = ""; 
    int i = 0;
    for (; word[i] != ' '; ++i) {
        // just adjust counter to position
    }
    ++i; // + 1 because right now cursor at space position
    for (; word[i] != ' '; ++i) {
        // adjust counter for second position
    }
    ++i; // + 1 because right now cursor at space position
    for (; std::isalnum(word[i]); ++i) {
        result += word[i];
    }
    return result;
}


void setcommand(std::string word, std::string &which_command) { 
    std::string com = "";
    int i = 0;
    while (word[i] == ' ') {
        // adjust position
        ++i;
    }
    for (; i < word.length(); ++i) {
        if (std::isalpha(word[i])) {
            com += word[i];
        }
        else {
            break;
        }
    }
    for (auto cm : commands) {
        if (com == cm) {
            which_command = std::string(cm);
        }
    }
}
void change(std::string &word, std::string &new_word, std::string &which_command) {
    setcommand(word, which_command);
    std::string first_op = search1(word);
    std::string second_op = search2(word);
    if (first_op.empty()) {
        std::cerr << "Error: cannot be less then 1 argument in command" << std::endl;
        std::exit(1);
    }

    if (which_command == "add") {
        new_word = first_op + ' ' + '=' + ' ' + first_op + ' ' + '+' + ' ' + second_op;
    }
    else if (which_command == "sub") {
        new_word = first_op + ' ' + '=' + ' ' + first_op + ' ' + '-' + ' ' + second_op;
    }
    else if (which_command == "mul" || which_command == "imul") {
        new_word = first_op + ' ' + '=' + ' ' + first_op + ' ' + '*' + ' ' + second_op;
    }
    else if (which_command == "mov") {
        new_word = first_op + ' ' + '=' + ' ' + second_op;
    }
    else if (which_command == "xor") {
        new_word = first_op + ' ' + '=' + ' ' + first_op + ' ' + '^' + ' ' + second_op;
    }
    else if (which_command == "and") {
        new_word = first_op + ' ' + '=' + ' ' + first_op + ' ' + '&' + ' ' + second_op;
    }
    else if (which_command == "or") {
        new_word = first_op + ' ' + '=' + ' ' + first_op + ' ' + '|' + ' ' +  second_op;
    }
    else if (which_command == "not") {
        new_word = first_op + ' ' + '=' + ' ' + '!' + first_op;
    }
    else if (which_command == "shr" || which_command == "sar") {
        new_word = first_op + ' ' + '=' + ' ' + first_op + ' ' + '>' + '>' + ' ' + second_op;
    }
    else if (which_command == "shl") {
        new_word = first_op + ' ' + '=' + ' ' + first_op + ' ' + '<' + '<' + ' ' + second_op;
    }
    else {
        new_word = "";
    }
}

std::string lower(std::string str) {
    for (char &x : str) {
        x = std::tolower(x);
    }
    return str;
}
int main(int argc, char *argv[]) {
    if (argc == 1) {
        std::cout << "Usage: " << argv[0] << " <assembly_file>" << std::endl;
        return 0;
    }
    else if (argc > 2) {
        std::cerr << "Error: you cannot have more then 1 assembler file as a argument" << std::endl;
        return 0;
    }
    std::filesystem::path p(argv[1]);
    if (!std::filesystem::exists(argv[1])) {
        std::cerr << "Error: file don't exists" << std::endl;
        return 0;
    }
    else if ((lower(std::string(p.extension()))) != ".s" && p.extension() != ".asm") { // if extension of file not .s and not .asm then exit 
        std::cerr << "Error: not supported extensions of file" << std::endl;
        return 0;
    }
    std::string newfile = p.replace_extension("").string() + ".psc";
    std::ifstream read(argv[1]);
    std::ofstream write(newfile);
    std::string insiders = "";
    std::string word = "";
    std::string new_word = "";
    std::string which_command = "";
    char c = '\0';
    while(read.get(c)) {
        if (std::isalnum(c) || c == ' ') { 
            word += c;
        }
        else if (c == '\n') {
            change(word, new_word, which_command);
            insiders += new_word;
            insiders += '\n';
            word = "";
        }
        
    }
    read.close();
    for (char x : insiders) {
        write.put(x);
    }
    write.close();

}
