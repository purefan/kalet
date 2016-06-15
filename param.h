
#ifndef _PARAM_H_
#define _PARAM_H_
class Param {

    bool            allow_empty;

    std::string     description;
    std::string     long_form;
    std::string     str_value;


public:
    Param();
    Param(int);

    std::string getShortForm();
    std::string getLongForm();
    std::string getValue();
    std::string getDescription();

    void setDescription(std::string);
    void setLongForm(std::string);
    void setValue(std::string);
    void setValue(int);
    void setValue(bool);
    void setValue(std::string, std::string);
    void setRequires(Param);

    // By default a param does not allow empty values
    void setAllowEmpty();
    bool allowsEmpty();

};
#endif