#ifndef CONVERSIONS_H
#define CONVERSIONS_H
#include <iostream>
#include <string>
#include <cmath>   


int alphToNumX(std::string position_in) {
    return toupper(position_in[0]) - 65;
}
int alphToNumY(std::string position_in) {
    return 8 - (int(position_in[1]) - 48);
}

std::string numToAlph(int xpos, int ypos) {
    return char(xpos + 65) + std::to_string(8 - ypos);
}
std::string alphToNum(std::string position_in) {
    return std::to_string(toupper(position_in[0]) - 65) +
        std::to_string((8 - (int(position_in[1]) - 48)));
}

std::string alphaNumUpper(std::string position_in) {
    std::string temp = "";
    temp += toupper(position_in[0]);
    return temp + position_in[1];
}

#endif