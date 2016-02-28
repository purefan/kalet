
#ifndef _PARAM_H_
#define _PARAM_H_
class Param {

    std::wstring    str_value;
    int             int_value;
    bool            bool_value;

    std::string description, short_form, long_form;

public:
    void set_description(std::string);
    void set_short_form(char);
    void set_long_form(std::string);
    void set_type(std::string);
    void set_value(std::string);
    void requires(Param);
};
#endif