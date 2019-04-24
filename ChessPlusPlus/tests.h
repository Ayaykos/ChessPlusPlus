#ifndef TESTS_H
#define TESTS_H
#include <iostream>
#include <string>
#include "grid.h"
#include <vector>

class TestKing {
public:
    void test() {
        Grid GridObj;
        GridObj.initPieces();
        GridObj.initGrid();
        GridObj.fill();
        GridObj.print();
        GridObj["D1"]->print_details();

        GridObj.movePiece("E8", "D7");
        GridObj.movePiece("D7", "D6");
        GridObj.movePiece("D6", "D5");


        GridObj.movePiece("D5", "D6");
        GridObj.movePiece("D6", "D5");

        GridObj.movePiece("D5", "D4");
        GridObj.movePiece("D4", "D5");

        GridObj.movePiece("D5", "E4");
        GridObj.movePiece("E4", "D5");

        GridObj.movePiece("D5", "C4");
        GridObj.movePiece("C4", "D5");

        GridObj.movePiece("D5", "E6");
        GridObj.movePiece("E6", "D5");

        GridObj.movePiece("D5", "C6");
        GridObj.movePiece("C6", "D5");

        GridObj.movePiece("D5", "E5");
        GridObj.movePiece("E5", "D5");

        GridObj.movePiece("D5", "C5");
        GridObj.movePiece("C5", "D5");

        GridObj.movePiece("D5", "F6");
        GridObj.movePiece("D5", "F7");
        GridObj.movePiece("D5", "C7");
        GridObj.movePiece("D5", "D7");
        GridObj.movePiece("D5", "E7");
        GridObj.movePiece("D5", "B7");
        GridObj.movePiece("D5", "B6");
        GridObj.movePiece("D5", "B5");
        GridObj.movePiece("D5", "B4");
        GridObj.movePiece("D5", "B3");
        GridObj.movePiece("D5", "C3");
        GridObj.movePiece("D5", "D3");
        GridObj.movePiece("D5", "E3");
        GridObj.movePiece("D5", "F3");
        GridObj.movePiece("D5", "F4");
        GridObj.movePiece("D5", "F5");

        GridObj.print();

        GridObj.deleteAll();
    }
};
#endif