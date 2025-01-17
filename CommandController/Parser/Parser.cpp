#include "Parser.hpp"

#include <cctype>     // std::isalpha
#include <stdexcept> // std::runtime_error
#include <string>
#include <utility> // std::move

Parser::Parser(std::istream& input)
: input_{input}
{
}

std::stringstream Parser::inputCommand() {
    std::string command;
    getline(input_, command); // TK: This should be done in the controller, reading command line from input is not part of parsing, parser hav to parse whatever already fetched
    return std::stringstream(command);
}

CommandPtr Parser::parseCommand() {

    std::stringstream stream = inputCommand(); // With this approach you can't call your parser from GUI app, inputCommand() is part of Controller, parsers input istream will be this 

    std::string token;
    OperandType op;

    stream >> token;

    CommandPtr commandPtr = commandRegistry_.findCommand(token);
    if(!commandPtr)
        throw std::runtime_error("invalid command!");

    while(stream >> token) {

        char c;
        stream >> c;
        stream.putback(c);
        if(std::isalpha(c)) {
            std::string str;
            stream >> str;
            op = str;
        } else {
            int num;
            stream >> num;
            op = num;
        }
        token.erase(token.begin());
        commandPtr->addOperand(token, op);
    }
    return commandPtr;
}
