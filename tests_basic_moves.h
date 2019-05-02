#ifndef TESTS_BASIC_MOVES_H
#define TESTS_BASIC_MOVES_H
#include <iostream>
#include <string>
#include "grid.h"
#include <vector>

void rookTest(Grid &GridObj) {
    std::string current = "A8", next = "A7";
    for (int i = 6; i >= 0; --i) {
        GridObj.movePiece(current, next);
        current = next;
        next = current[0] + std::to_string(i);
        std::cout << current << " " << next << "\n";
    }
    current = "A1", next = "B1";
    for (int i = 0; i < 7; ++i) {
        GridObj.movePiece(current, next);
        current = next;
        next = char(current[0] + 1) + std::to_string(1);
        std::cout << current << " " << next << "\n";
    }
    current = "H1", next = "H2";
    for (int i = 3; i < 10; ++i) {
        GridObj.movePiece(current, next);
        current = next;
        next = current[0] + std::to_string(i);
        std::cout << current << " " << next << "\n";
    }
    current = "H8", next = "G8";
    for (int i = 0; i < 7; ++i) {
        GridObj.movePiece(current, next);
        current = next;
        next = char(current[0] - 1) + std::to_string(8);
        std::cout << current << " " << next << "\n";
    }
    GridObj.movePiece("A8", "A1");
    GridObj.movePiece("A1", "H1");
    GridObj.movePiece("H1", "H8");
    GridObj.movePiece("H8", "A8");
}
void bishopTest(Grid &GridObj) {
    GridObj.movePiece("C8", "B7");
    GridObj.movePiece("B7", "C8");

    GridObj.movePiece("C8", "A6");
    GridObj.movePiece("A6", "C4");
    GridObj.movePiece("C4", "F1");
    GridObj.movePiece("F1", "H3");
    GridObj.movePiece("H3", "C8");
}

class TestKnightBasic {
public:
    void testsuccess() {
        Grid GridObj;
        GridObj.initPieces();
        GridObj.initGrid();
        GridObj.fill();
        GridObj.print();

        GridObj.movePiece("B8", "A6");
        GridObj.movePiece("A6", "B8");
        GridObj.movePiece("B8", "C6");
        GridObj.movePiece("C6", "D8");
        GridObj.movePiece("D8", "F7");
        GridObj.movePiece("F7", "H8");
        GridObj.movePiece("H8", "G6");
        GridObj.movePiece("G6", "F8");
        GridObj.movePiece("F8", "E6");
        GridObj.movePiece("E6", "D4");
        GridObj.movePiece("D4", "B3");

        GridObj.print();
        //GridObj.deleteAll();
    }
    void testfail() {
        Grid GridObj;
        GridObj.initPieces();
        GridObj.initGrid();
        GridObj.fill();
        GridObj.print();

        GridObj.movePiece("B8", "A8");
        GridObj.movePiece("B8", "C8");
        GridObj.movePiece("B8", "A7");
        GridObj.movePiece("B8", "B7");
        GridObj.movePiece("B8", "C7");
        GridObj.movePiece("B8", "D8");
        GridObj.movePiece("B8", "E8");
        GridObj.movePiece("B8", "E7");
        GridObj.movePiece("B8", "B6");
        GridObj.movePiece("B8", "D6");
        GridObj.movePiece("B8", "A5");
        GridObj.movePiece("B8", "B5");
        GridObj.movePiece("B8", "C5");
        GridObj.movePiece("B8", "D5");
        GridObj.movePiece("B8", "H8");
        GridObj.movePiece("B8", "H2");
        GridObj.movePiece("B8", "B1");
        GridObj.movePiece("B8", "A1");

        GridObj.movePiece("B8", "A6");
        GridObj.movePiece("A6", "A7");
        GridObj.movePiece("A6", "A8");
        GridObj.movePiece("A6", "A5");
        GridObj.movePiece("A6", "A4");
        GridObj.movePiece("A6", "C8");
        GridObj.movePiece("A6", "H6");
        GridObj.movePiece("A6", "B6");
        GridObj.movePiece("A6", "C6");
        GridObj.movePiece("A6", "D6");

        GridObj.print();
        //GridObj.deleteAll();
    }
};
class TestQueenBasic {
public:
    void testsuccess() {
        Grid GridObj;
        GridObj.initPieces();
        GridObj.initGrid();
        GridObj.fill();
        GridObj.print();
        //rook
        GridObj.movePiece("D8", "A8");
        rookTest(GridObj);
        GridObj.movePiece("A8", "C8");
        bishopTest(GridObj);

        GridObj.print();
        //GridObj.deleteAll();
    }
    void testfail() {
        Grid GridObj;
        GridObj.initPieces();
        GridObj.initGrid();
        GridObj.fill();
        GridObj.print();

        GridObj.movePiece("D8", "E6");
        GridObj.movePiece("D8", "E5");
        GridObj.movePiece("D8", "E4");
        GridObj.movePiece("D8", "E3");
        GridObj.movePiece("D8", "E2");
        GridObj.movePiece("D8", "E1");
        GridObj.movePiece("D8", "H5");
        GridObj.movePiece("D8", "F7");

        GridObj.print();
        //GridObj.deleteAll();
    }
};
class TestBishopBasic {
public:
    void testsuccess() {
        Grid GridObj;
        GridObj.initPieces();
        GridObj.initGrid();
        GridObj.fill();
        GridObj.print();

        bishopTest(GridObj);
        
        GridObj.print();
        //GridObj.deleteAll();
    }
    void testfail() {
        Grid GridObj;
        GridObj.initPieces();
        GridObj.initGrid();
        GridObj.fill();
        GridObj.print();

        GridObj.movePiece("C8", "D8");
        GridObj.movePiece("C8", "B8");
        GridObj.movePiece("C8", "A8");
        GridObj.movePiece("C8", "H8");
        GridObj.movePiece("C8", "C7");
        GridObj.movePiece("C8", "C1");
        GridObj.movePiece("C8", "D6");
        GridObj.movePiece("C8", "D5");
        GridObj.movePiece("C8", "D4");
        GridObj.movePiece("C8", "D3");
        GridObj.movePiece("C8", "D2");
        GridObj.movePiece("C8", "D1");
        GridObj.movePiece("C8", "H4");

        GridObj.print();
        //GridObj.deleteAll();
    }
};

class TestRookBasic {
public:
    void testsuccess() {
        Grid GridObj;
        GridObj.initPieces();
        GridObj.initGrid();
        GridObj.fill();
        GridObj.print();


        rookTest(GridObj);

        GridObj.print();

        //GridObj.deleteAll();
    }
    void testfail() {
        Grid GridObj;
        GridObj.initPieces();
        GridObj.initGrid();
        GridObj.fill();
        GridObj.print();

        GridObj.movePiece("A8", "B7");
        GridObj.movePiece("A8", "B6");
        GridObj.movePiece("A8", "H1");

        //GridObj.deleteAll();
    }
    
};
class TestKingBasic {
public:
    void test() {
        Grid GridObj;
        GridObj.initPieces();
        GridObj.initGrid();
        GridObj.fill();
        GridObj.print();

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

        //GridObj.deleteAll();
    }
};
#endif