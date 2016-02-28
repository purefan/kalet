#include "param.h"

#ifndef _OPTIONS_H_
#define _OPTIONS_H_
class Options {

  public:
    bool ok = true;
    void addOption(std::string);
    void registerParams(std::vector<std::string>);
    void add_param(Param);
    void printVector(std::vector<std::wstring>);
};
#endif