#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <cassert>

std::string numToAlph(int xpos, int ypos) {
    return char(xpos + 65) + std::to_string(8 - ypos);
}
std::string alphToNum(std::string position_in) {
    return std::to_string(toupper(position_in[0]) - 65) +
        std::to_string((8 - (int(position_in[1]) - 48)));
}

#endif