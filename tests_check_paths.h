#ifndef TESTS_CHECK_PATHS_H
#define TESTS_CHECK_PATHS_H
#include <iostream>
#include <string>
#include "grid.h"
#include <vector>

class TestRookPath {
public:
    void test() {
        Grid GridObj;
        GridObj.initPieces();
        GridObj.initGrid();
        GridObj.fill();

        GridObj.movePiece("A8", "A6");
        GridObj.movePiece("A8", "A5");
        GridObj.movePiece("A8", "A4");
        GridObj.movePiece("A8", "A3");
        GridObj.movePiece("A8", "A2");
        GridObj.movePiece("A8", "A1");

        GridObj.movePiece("A8", "B8");

        GridObj.removePiece("A7");
        GridObj.movePiece("A8", "A7");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("A7", "A8");
        std::cout << "\tAssert: Not blocked." << std::endl;
        
        GridObj.movePiece("A8", "A6");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("A6", "A8");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("A8", "A5");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("A5", "A8");
        std::cout << "\tAssert: Not blocked." << std::endl;

        GridObj.movePiece("A8", "A2");
        GridObj.removePiece("B8");
        GridObj.movePiece("A8", "B8");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("B8", "A8");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("A8", "C8");

        GridObj.print();

        //GridObj.deleteAll();
    }
};

#endif