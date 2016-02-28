#include "options.h"
#include <string>
#include <vector>

void Options::addOption(std::string a){}
void Options::registerParams(std::vector<std::string> args){}
void Options::add_param(Param orig){}
void Options::printVector(std::vector<std::wstring> original) {
    for (std::vector<std::wstring>::iterator i = original.begin(); i != original.end(); i++) {
        std::wcout << *i << ENDL;
    }
}