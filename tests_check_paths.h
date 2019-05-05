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
        GridObj.removePiece("B8");
        GridObj.movePiece("A8", "B8");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("B8", "B7");
        GridObj.movePiece("B8", "B2");
        GridObj.removePiece("B7");
        GridObj.movePiece("B8", "B2");
        GridObj.movePiece("B8", "B3");
        std::cout << "\tAssert: Not blocked." << std::endl;

        GridObj.restoreGrid();

        GridObj.print();

        //GridObj.deleteAll();
    }
};
class TestBishopPath {
public:
    void test() {
        Grid GridObj;
        GridObj.initPieces();
        GridObj.initGrid();
        GridObj.fill();

        GridObj.movePiece("C8", "B7");
        GridObj.movePiece("C8", "A6");
        GridObj.movePiece("C8", "D7");
        GridObj.movePiece("C8", "E6");

        GridObj.removePiecesGroup("Black", "Pawn");
        GridObj.movePiece("C8", "B7");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("B7", "C8");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("C8", "A6");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("A6", "C8");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("C8", "D7");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("D7", "C8");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("C8", "H3");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("H3", "E6");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("E6", "C4");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("C4", "A6");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("A6", "C8");
        std::cout << "\tAssert: Not blocked." << std::endl;

        GridObj.print();
    }
};
class TestKingPath {
public:
    void test() {
        Grid GridObj;
        GridObj.initPieces();
        GridObj.initGrid();
        GridObj.fill();

        GridObj.movePiece("E8", "D8");
        GridObj.movePiece("E8", "D7");
        GridObj.movePiece("E8", "E7");
        GridObj.movePiece("E8", "F7");
        GridObj.movePiece("E8", "F8");

        GridObj.removePiecesGroup("Black", "Pawn");
        GridObj.movePiece("E8", "D7");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("D7", "E8");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("E8", "E7");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("E7", "E8");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("E8", "F7");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("F7", "E8");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("E8", "F7");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("F7", "F6");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("F6", "F5");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("F5", "F6");
        std::cout << "\tAssert: Not blocked." << std::endl;

        GridObj.print();
    }
    void testOvertake() {
        Grid GridObj;
        GridObj.initPieces();
        GridObj.initGrid();
        GridObj.fill();

        GridObj.removePiece("E7");
        GridObj.movePiece("E8", "E7");
        GridObj.movePiece("E7", "E6");
        GridObj.movePiece("E6", "E5");
        GridObj.movePiece("E5", "E4");
        GridObj.movePiece("E4", "E3");

        GridObj.print();
        GridObj.movePiece("E3", "E2");
        GridObj.print();
        GridObj.printCaptured();
    }
};
class TestQueenPath {
public:
    void test() {
        Grid GridObj;
        GridObj.initPieces();
        GridObj.initGrid();
        GridObj.fill();

        //blocked
        GridObj.movePiece("D8", "C8");
        GridObj.movePiece("D8", "C7");
        GridObj.movePiece("D8", "D7");
        GridObj.movePiece("D8", "E7");
        GridObj.movePiece("D8", "E8");

        //not blocked
        GridObj.removePiecesGroup("Black", "Pawn");
        GridObj.movePiece("D8", "D7");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("D7", "D8");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("D8", "D3");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("D3", "A3");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("A3", "A7");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("A7", "H7");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("H7", "H3");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("H3", "D3");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("D3", "D8");
        std::cout << "\tAssert: Not blocked." << std::endl;

        GridObj.movePiece("D8", "E7");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("E7", "D8");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("D8", "C7");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("C7", "D8");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("D8", "A5");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("A5", "C3");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("C3", "F6");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("F6", "D8");
        std::cout << "\tAssert: Not blocked." << std::endl;

        GridObj.movePiece("D8", "D2");
        GridObj.movePiece("D8", "A5");
        std::cout << "\tAssert: Not blocked." << std::endl;
        GridObj.movePiece("A5", "D2");

        GridObj.print();
    }
};
#endif