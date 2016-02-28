#include "options.h"
#include <string>
#include <vector>

/**
 * @brief Stores a vector of parameters comming from command line
 * @param args vector of strings
 */
void Options::registerParams(std::vector<std::string> args){
    this->cli_params = args;
}

void Options::addParam(Param orig){}
void Options::printVector(std::vector<std::wstring> original) {
    for (std::vector<std::wstring>::iterator i = original.begin(); i != original.end(); i++) {
        std::wcout << *i << ENDL;
    }
}