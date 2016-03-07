#include "options.h"
#include <string>
#include <vector>
#include <map>
#include <boost/algorithm/string.hpp>

/**
 * @brief Stores a vector of parameters comming from command line
 * @param args vector of strings
 */
void Options::registerArgs(std::vector<std::string> args){
    std::map<std::string, std::string> parts;
    for(std::vector<Param>::iterator param_ite = this->internal_params.begin(); param_ite != this->internal_params.end(); param_ite++) {
        for (std::vector<std::string>::iterator args_ite = args.begin(); args_ite != args.end(); args_ite++) {
            parts = this->getParts( (*args_ite));
            if (this->isCommand(parts.begin()->first)) {
                this->commands[parts.begin()->first] = true; //parts.begin()->second;
            } else {
                // The Param ignores invalid assignments
                (*param_ite).setValue(parts.begin()->first, parts.begin()->second);
            }
        }
    }

}

bool Options::isCommand(std::string value) {
    bool is_command = false;
    if (value.find("help") != std::string::npos) {
        is_command = true;
    }
    return is_command;
}

void Options::runCommands() {
    for(std::map<std::string, bool>::iterator command_ite = this->commands.begin(); command_ite != this->commands.end(); command_ite++) {
        if ((*command_ite).first == "help") {
            this->cmdHelp();
        } else {
            std::cerr << "This command is invalid: " << (*command_ite).first << ENDL;
        }
    }

    // this->printVector(command);
}

bool Options::hasCommands() {
    return this->commands.size() > 0;
}

void Options::cmdHelp() {
    std::cout << "[ This is the cmd_help ]" << ENDL;
    for(std::vector<Param>::iterator param_ite = this->internal_params.begin(); param_ite != this->internal_params.end(); param_ite++) {
        std::cout << "-" << (*param_ite).getShortForm() << ENDL;
        std::cout << "  --" << (*param_ite).getLongForm() << "\t\t" << (*param_ite).getDescription() << ENDL;
    }
}

/**
 * @brief Splits cli arguments
 * @details from "--name=value" to [name] = value
 * or "--something" to [something] = ""
 *
 * @param value A cli argument in the form "-s", "--long" or "--short=val"
 * @return [description]
 */
std::map<std::string, std::string> Options::getParts(std::string value) {
    std::map <std::string, std::string> out;
    // Remove leading dashes
    do {
        value = value.substr(1);
    } while ( value.substr(0,1) == "-");

    // Split by =
    int pos_eq = value.find('=');
    if (pos_eq != std::string::npos) {
        std::string name = value.substr(0, pos_eq);
        value = value.substr(pos_eq + 1);
        out[name] = value;
    } else {
        // Or just store an empty right hand value
        out[value] = "";
    }

    return out;
}

void Options::addParam(Param orig){
    this->internal_params.push_back(orig);
}

void Options::printVector(std::vector<std::string> original) {
    for (std::vector<std::string>::iterator i = original.begin(); i != original.end(); i++) {
        std::cout << *i << ENDL;
    }
}
void Options::printVector(std::vector<Param> original) {
    for (std::vector<Param>::iterator i = original.begin(); i != original.end(); i++) {
        std::cout << (*i).getLongForm() << " = " << (*i).getValue() << ENDL;
    }
}

void Options::printVector(std::map<std::string, std::string> original) {
    for (std::map<std::string, std::string>::iterator i = original.begin(); i != original.end(); i++) {
        std::cout << (*i).first << " = " << (*i).second << ENDL;
    }
}

bool Options::areParamsOk() {
    // 1. Check that there are params to check
    // 2.0 Check if any of the params has a dependency
    // 2.1 Check if they fulfill the dependency

    std::cout << "internal_params:" << ENDL;
    this->printVector(this->internal_params);
    return true;
}

std::string Options::operator[](std::string param) {
    param = this->canonicalizeString(param);
    std::string temp_long_name;
    for(std::vector<Param>::iterator param_ite = this->internal_params.begin(); param_ite != this->internal_params.end(); param_ite++) {
        temp_long_name = (*param_ite).getLongForm();
        temp_long_name = this->canonicalizeString(temp_long_name);
        if (temp_long_name == param) {
            return (*param_ite).getValue();
        }
    }
    return "";
}

std::string Options::canonicalizeString(std::string original) {
    original = boost::to_lower_copy<std::string>(original);
    int dash_pos = original.find("-");
    if (dash_pos != std::string::npos) {
        original.replace(dash_pos, 1, "");
    }
    int underline_pos = original.find("_");
    if (underline_pos != std::string::npos) {
        original.replace(underline_pos, 1, "");
    }
    return original;
}