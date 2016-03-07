#include "param.h"
#include <map>

#ifndef _OPTIONS_H_
#define _OPTIONS_H_
class Options {
    private:
        // like -v --verbose -h --help
        std::map<std::string, bool> commands;

        // like --source-file=<path>
        std::vector<Param> internal_params;

    public:
        void registerArgs(std::vector<std::string>);
        void addParam(Param);
        void printVector(std::vector<std::string>);
        void printVector(std::vector<Param>);
        void printVector(std::map<std::string, std::string>);
        void runCommands();
        bool areParamsOk();
        bool isCommand(std::string);
        bool hasCommands();
        std::map<std::string, std::string> getParts(std::string);
        void cmdHelp();
        std::string operator[](std::string);
};
#endif