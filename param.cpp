#include "param.h"
#include <vector>
#include <string>

void Param::setDescription(std::string value) {
    this->description = value;
}

std::string Param::getDescription() {
    return this->description;
}

Param::Param() {
    this->allow_empty = true;
}

void Param::requires(Param requireds) {}

void Param::setShortForm(char short_form) {
    this->short_form = short_form;
}

void Param::setLongForm(std::string long_form) {
    this->long_form = long_form;
}

void Param::setValue(std::string value) {
    std::cout << "1. Setting value " << value << ENDL;
    // get short form from value
    int pos_eq = value.find('=');
    std::string name = value.substr(1, pos_eq - 1);
    value = value.substr(pos_eq + 1);
    std::cout << "name: " << name << " and value: " << value << ENDL;
    this->str_value = value;
}

void Param::setValue(int value) {
    std::cout << "2. Setting value " << value << ENDL;
    this->str_value = std::to_string(value);
}

void Param::setValue(bool value) {
    std::cout << "3. Setting value " << value << ENDL;
    this->str_value = std::to_string(value);
}

void Param::setValue(std::string name, std::string value) {
    if (name == this->getShortForm() || name == this->getLongForm()) {
        this->str_value = value;
    }
}

std::string Param::getLongForm() {
    return this->long_form;
}

std::string Param::getShortForm() {
    std::string out;
    out.push_back(this->short_form);
    return out;
}

std::string Param::getValue() {
    return this->str_value;
}

void Param::require_not_empty() {
    this->allow_empty = false;
}