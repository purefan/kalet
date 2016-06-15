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
    this->allow_empty = false;
}

Param::Param(int value) {
    this->allow_empty = false;
    this->setValue(value);
}

void Param::setRequires(Param requireds) {}

void Param::setLongForm(std::string long_form) {
    this->long_form = long_form;
}

void Param::setValue(std::string value) {
    std::cout << "1. Setting value " << value << ENDL;
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
    if (name == this->getLongForm()) {
        this->str_value = value;
    }
}

std::string Param::getLongForm() {
    return this->long_form;
}

std::string Param::getValue() {
    return this->str_value;
}

void Param::setAllowEmpty() {
    this->allow_empty = true;
}

bool Param::allowsEmpty() {
    return this->allow_empty;
}