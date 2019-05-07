#ifndef TESTS_GRID_H
#define TESTS_GRID_H
#include <iostream>
#include <string>
#include "grid.h"
#include <vector>

class GridTest {
public:
    void testHistory() {
        Grid GridObj;
        GridObj.init();
        GridObj.updateHistory();

        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                GridObj.indexHistory(0, j, i);
            }
        }
    }
    void testID() {
        Grid GridObj;
        GridObj.init();
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (GridObj[numToAlph(j, i)] != nullptr) {
                    std::cout << GridObj[numToAlph(j, i)]->getID() << " ";
                }
                else std::cout << "null ";
            }
            std::cout << "\n";
        }
        GridObj.movePiece("A7", "A6");
        GridObj.movePiece("A6", "A5");
        GridObj.printTurnHistory();
    }
};

#endif