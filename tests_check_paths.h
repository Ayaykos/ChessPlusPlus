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
        GridObj.init();

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
    void testOvertake() {
        Grid GridObj;
        GridObj.init();

        GridObj.removePiecesGroup("Black", "Pawn");
        GridObj.movePiece("A8", "A2");
        GridObj.printCaptured();
        GridObj.movePiece("A2", "B2");
        GridObj.printCaptured();
        GridObj.movePiece("B2", "B1");
        GridObj.movePiece("B1", "A1");
        GridObj.printCaptured();

        GridObj.print();
    }
};
class TestBishopPath {
public:
    void test() {
        Grid GridObj;
        GridObj.init();

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
    void testOvertake() {
        Grid GridObj;
        GridObj.init();

        GridObj.removePiecesGroup("Black", "Pawn");
        GridObj.movePiece("C8", "A6");
        GridObj.movePiece("A6", "E2");
        GridObj.printCaptured();
        GridObj.movePiece("E2", "D1");
        GridObj.printCaptured();
        GridObj.movePiece("D1", "C2");
        GridObj.printCaptured();
        GridObj.movePiece("C2", "B3");
        GridObj.movePiece("B3", "D5");
        GridObj.movePiece("D5", "H1");
        GridObj.printCaptured();
        GridObj.movePiece("D5", "G8");
        GridObj.printCaptured();

        GridObj.print();
    }
};
class TestKingPath {
public:
    void test() {
        Grid GridObj;
        GridObj.init();

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
        GridObj.init();

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
        GridObj.movePiece("E2", "E1");
        GridObj.printCaptured();
        GridObj.movePiece("E1", "D1");
        GridObj.movePiece("D1", "C2");
        GridObj.movePiece("C2", "D2");
        GridObj.movePiece("D2", "C1");
        GridObj.printCaptured();

        GridObj.print();
    }
};
class TestQueenPath {
public:
    void test() {
        Grid GridObj;
        GridObj.init();

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
    void testOvertake() {
        Grid GridObj;
        GridObj.init();

        //bishop
        GridObj.movePiece("D8", "C8");
        GridObj.removePiece("C8");
        GridObj.movePiece("D8", "C8");
        GridObj.removePiecesGroup("Black", "Pawn");
        GridObj.movePiece("C8", "A6");
        GridObj.movePiece("A6", "E2");
        GridObj.movePiece("E2", "D1");
        GridObj.movePiece("D1", "C2");
        GridObj.movePiece("C2", "B3");
        GridObj.movePiece("B3", "D5");
        GridObj.movePiece("D5", "H1");
        GridObj.movePiece("D5", "G8");
        GridObj.restoreGrid();
        std::cout << "Rook testing\n";
        //rook
        GridObj.removePiece("C8");
        GridObj.removePiece("B8");
        GridObj.removePiece("A8");
        GridObj.movePiece("D8", "A8");

        
        GridObj.removePiecesGroup("Black", "Pawn");
        GridObj.movePiece("A8", "A2");
        GridObj.printCaptured();
        GridObj.movePiece("A2", "B2");
        GridObj.printCaptured();
        GridObj.movePiece("B2", "B1");
        GridObj.movePiece("B1", "A1");
        GridObj.printCaptured();

        GridObj.print();
    }
};
class TestKnightPath {
public:
    void test() {
        Grid GridObj;
        GridObj.init();
        GridObj.movePiece("B8", "C6");
        GridObj.movePiece("C6", "E7");
        GridObj.movePiece("C6", "D4");
        GridObj.movePiece("D4", "C2");
        GridObj.printCaptured();
        GridObj.movePiece("C2", "A1");
        GridObj.printCaptured();
        GridObj.movePiece("A1", "C2");
        GridObj.movePiece("C2", "E1");
        GridObj.printCaptured();

        //white move
        GridObj.movePiece("G1", "F3");
        GridObj.movePiece("F3", "E5");
        GridObj.movePiece("E5", "F7");
        GridObj.printCaptured();
        GridObj.movePiece("F7", "E5");
        GridObj.movePiece("E5", "D7");
        GridObj.printCaptured();

        GridObj.print();
    }
    void testOvertake() {

    }
};
class TestPawnPath {
public:
    void test() {
        Grid GridObj;
        GridObj.init();

        GridObj.movePiece("C7", "C6");
        GridObj.movePiece("C6", "C5");
        GridObj.movePiece("C5", "C3");
        GridObj.movePiece("C5", "D5");
        GridObj.movePiece("C5", "B5");
        GridObj.movePiece("C5", "D4");
        GridObj.movePiece("C5", "B4");
        GridObj.movePiece("C5", "B3");
        GridObj.movePiece("C5", "C3");
        GridObj.movePiece("C5", "D3");
        //backward
        GridObj.movePiece("C5", "B6");
        GridObj.movePiece("C5", "C6");
        GridObj.movePiece("C5", "D6");
        GridObj.movePiece("C5", "C7");

        GridObj.print();
        //newpawn
        GridObj.movePiece("F7", "F5");
        GridObj.movePiece("F5", "F3");
        GridObj.movePiece("F5", "E3");
        GridObj.movePiece("F5", "G3");
        GridObj.movePiece("F5", "E4");
        GridObj.movePiece("F5", "G4");
        GridObj.movePiece("F5", "G5");
        GridObj.movePiece("F5", "E5");
        //backward
        GridObj.movePiece("F5", "E6");
        GridObj.movePiece("F5", "F6");
        GridObj.movePiece("F5", "G6");
        GridObj.movePiece("F5", "F7");

        GridObj.print();

        //team block
        GridObj.movePiece("E7", "E6");
        GridObj.movePiece("E6", "F5");
        GridObj.movePiece("E6", "E5");
        GridObj.movePiece("E5", "F5");
        GridObj.movePiece("E5", "E4");
        GridObj.movePiece("E4", "F5");


        GridObj.movePiece("D7", "D6");
        GridObj.movePiece("D6", "C5");
        GridObj.movePiece("D6", "D5");
        GridObj.movePiece("D5", "C5");
        GridObj.movePiece("D5", "D4");
        GridObj.movePiece("D4", "C5");

        GridObj.print();
    }
    void testOvertake() {
        Grid GridObj;
        GridObj.init();

        GridObj.movePiece("C7", "C6");
        GridObj.movePiece("C6", "C5");
        GridObj.movePiece("C5", "C4");
        GridObj.movePiece("C4", "B2");
        GridObj.movePiece("C4", "C2");
        GridObj.movePiece("C4", "D2");
        GridObj.movePiece("C4", "C3");
        GridObj.movePiece("C3", "C2");
        GridObj.movePiece("C3", "B1");
        GridObj.movePiece("C3", "C1");
        GridObj.movePiece("C3", "D1");
        GridObj.movePiece("C3", "D2");
        GridObj.movePiece("D2", "D1");
        GridObj.movePiece("D2", "C2");
        GridObj.movePiece("D2", "E2");
        GridObj.movePiece("D2", "C3");
        GridObj.movePiece("D2", "D3");
        GridObj.movePiece("D2", "E3");
        GridObj.movePiece("D2", "C1");

        //opposite
        GridObj.movePiece("F2", "F4");
        GridObj.movePiece("F4", "F5");
        GridObj.movePiece("F5", "E6");
        GridObj.movePiece("F5", "G6");
        GridObj.movePiece("F5", "E7");
        GridObj.movePiece("F5", "F7");
        GridObj.movePiece("F5", "G7");
        GridObj.movePiece("F5", "F6");
        GridObj.movePiece("F6", "F7");
        GridObj.movePiece("F6", "E7");
        GridObj.movePiece("E7", "D7");
        GridObj.movePiece("E7", "E8");
        GridObj.movePiece("E7", "F7");
        GridObj.movePiece("E7", "D6");
        GridObj.movePiece("E7", "E6");
        GridObj.movePiece("E7", "F6");
        GridObj.movePiece("E7", "F8");
        GridObj.movePiece("F8", "F7");
        GridObj.movePiece("F8", "G7");

        GridObj.print();
    }
    void testEP() {
        Grid GridObj;
        GridObj.init();

        GridObj.movePiece("F2", "E3");
        GridObj.movePiece("F2", "G3");
        GridObj.movePiece("F2", "F4");
        GridObj.movePiece("F4", "E4");
        GridObj.movePiece("F4", "E5");
        GridObj.movePiece("F4", "G5");
        GridObj.movePiece("F4", "G4");
        GridObj.movePiece("F4", "F5");

        GridObj.movePiece("F7", "F6");
        GridObj.movePiece("F5", "E6");
        GridObj.movePiece("F5", "F6");
        GridObj.movePiece("F5", "G6");
        GridObj.movePiece("F5", "E5");
        GridObj.movePiece("F5", "G5");

        GridObj.movePiece("E7", "E6");
        GridObj.movePiece("E6", "E5");
        GridObj.movePiece("F5", "E6");

        GridObj.movePiece("G7", "G5");
        GridObj.movePiece("F5", "G6");


        
        GridObj.movePiece("D7", "D5");
        GridObj.movePiece("D5", "D4");
        GridObj.movePiece("D4", "D3");
        GridObj.movePiece("E2", "E3");
        GridObj.movePiece("E3", "D4");

        std::cout << "---------\n";
        GridObj.printTurnHistory(1);

        GridObj.movePiece("B2", "B4");
        GridObj.movePiece("A7", "A5");
        GridObj.movePiece("A5", "A4");
        GridObj.movePiece("B4", "A5");

        //
        GridObj.movePiece("B7", "B5");

        GridObj.movePiece("C2", "C3");
        GridObj.movePiece("C3", "C4");
        GridObj.movePiece("C4", "C5");
        GridObj.print();

        GridObj.movePiece("C5", "B6");

        GridObj.printTurnHistory(7);
    }
    void testEPcapturedcheck() {
        Grid GridObj;
        GridObj.init();

        GridObj.movePiece("D7", "D5");
        GridObj.movePiece("D5", "D4");
        GridObj.movePiece("E2", "E4");
        GridObj.movePiece("D4", "E3");
        GridObj.printCaptured();


        GridObj.print();
    }
    void testEPbothpawns() {
        Grid GridObj;
        GridObj.init();

        GridObj.removePiecesGroup("White", "Pawn");
        GridObj.movePiece("D1", "G4");
        GridObj.movePiece("F7", "F5");
        GridObj.movePiece("F5", "F4");
        GridObj.movePiece("F4", "G3");

        GridObj.printTurnHistory(1);
        
        GridObj.restoreGrid();
    }
};
#endif