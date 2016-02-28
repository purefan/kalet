
#ifndef _PARAM_H_
#define _PARAM_H_
class Param {

    std::wstring    str_value;
    int             int_value;
    bool            bool_value;

    std::string description, short_form, long_form;

public:
    void setDescription(std::string);
    void setShortForm(char);
    void setLongForm(std::string);
    void setType(std::string);
    void setValue(std::string);
    void requires(Param);
};
#endif