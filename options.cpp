#include "options.h"
#include <string>
#include <vector>
#include <map>
/**
 * @brief Stores a vector of parameters comming from command line
 * @param args vector of strings
 */
void Options::registerArgs(std::vector<std::string> args){
    std::map<std::string, std::string> parts;
    std::map<std::string, std::string> commands;
    for(std::vector<Param>::iterator param_ite = this->internal_params.begin(); param_ite != this->internal_params.end(); param_ite++) {
        for (std::vector<std::string>::iterator args_ite = args.begin(); args_ite != args.end(); args_ite++) {
            parts = this->getParts( (*args_ite));
            if (this->is_command(parts.begin()->first)) {
                commands[parts.begin()->first] = parts.begin()->second;
            } else {
                // The Param ignores invalid assignments
                (*param_ite).setValue(parts.begin()->first, parts.begin()->second);
            }
        }
    }

    // This might fail when there are more than one command
    this->run_command(commands);
}

bool Options::is_command(std::string value) {
    bool is_command = false;
    if (value.find("help") != std::string::npos) {
        is_command = true;
    }
    return is_command;
}

void Options::addParam(Param orig){}
void Options::printVector(std::vector<std::wstring> original) {
    for (std::vector<std::wstring>::iterator i = original.begin(); i != original.end(); i++) {
        std::wcout << *i << ENDL;
    }
}