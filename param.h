
#ifndef _PARAM_H_
#define _PARAM_H_
class Param {


    std::string     description;
    std::string     long_form;
    std::string     str_value;

public:
    std::string getShortForm();
    std::string getLongForm();
    std::string getValue();
    std::string getDescription();
    void setDescription(std::string);
    void setShortForm(char);
    void setLongForm(std::string);
    void setValue(std::string);
    void setValue(int);
    void setValue(bool);
    void setValue(std::string, std::string);
    void requires(Param);
};
#endif