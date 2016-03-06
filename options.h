#include "param.h"

#ifndef _OPTIONS_H_
#define _OPTIONS_H_
class Options {
    private:
        std::vector<std::string> cli_params;

    public:
        bool ok = true;
        void registerParams(std::vector<std::string>);
        void addParam(Param);
        void printVector(std::vector<std::wstring>);
        void cmd_help();
        bool is_command(std::string);
        std::map<std::string, std::string> getParts(std::string);
};
#endif