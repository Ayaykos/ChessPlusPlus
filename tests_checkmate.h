#ifndef TESTS_CHECKMATE_H
#define TESTS_CHECKMATE_H
#include <iostream>
#include <string>
#include "grid.h"
#include <vector>

class testCheckMateFile {
public:
    void test() {
        Grid GridObj;
        GridObj.init("GridInputs/E1E4cm1.in");
        GridObj.print();
        Grid GridObj2;
        GridObj2.init("GridInputs/D1H8cm2.in");
        GridObj2.print();
        Grid GridObj3;
        GridObj3.init("GridInputs/E1E8cm3.in");
        GridObj3.print();
    }
    void staleMate() {
        Grid GridObj;
        GridObj.init("GridInputs/E8H1sm1.in");
        GridObj.print();
    }
};
class testCheckMate {
public:
    void testKnight() {
        Grid GridObj;
        GridObj.init();

        GridObj.removePiecesGroup("Black", "Pawn");
        GridObj.movePiece("E8", "E7");
        GridObj.movePiece("E7", "E6");
        GridObj.movePiece("E6", "E5");

        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("G1", "F3");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("F3", "G5");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("G5", "F7");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("F7", "D8");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("D8", "C6");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("C6", "B4");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("B4", "D3");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("D3", "F4");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("F4", "G6");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("G6", "F8");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("F8", "D7");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("D7", "B6");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("B6", "C4");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("E5", "E6");
        GridObj.movePiece("C4", "E5");
        GridObj.movePiece("E5", "D3");

        GridObj.movePiece("E6", "E5");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";

        GridObj.print();
    }
    void testPawn() {
        Grid GridObj;
        GridObj.init();

        GridObj.removePiecesGroup("Black", "Pawn");
        GridObj.movePiece("E8", "E7");
        GridObj.movePiece("E7", "E6");
        GridObj.movePiece("E6", "E5");

        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("D2", "D4");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("D4", "D5");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("F2", "F3");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("F3", "F4");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";

        GridObj.print();
    }
    void testRook() {
        Grid GridObj;
        GridObj.init();

        GridObj.removePiecesGroup("Black", "Pawn");
        GridObj.removePiecesGroup("White", "Pawn");
        GridObj.movePiece("E8", "E7");
        GridObj.movePiece("E7", "E6");
        GridObj.movePiece("E6", "E5");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("H1", "H4");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("H4", "H5");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("H5", "F5");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("F5", "H5");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("H5", "H6");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("A1", "A4");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("A4", "A5");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("A5", "C5");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("C5", "A5");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("A5", "A6");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("H6", "H5");
        GridObj.movePiece("A6", "A5");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("H5", "H6");
        GridObj.movePiece("A5", "A6");

        GridObj.movePiece("H6", "F6");
        GridObj.movePiece("A6", "D6");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("D6", "E6");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("E6", "D6");
        GridObj.movePiece("F6", "E6");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("D6", "D4");
        GridObj.movePiece("D4", "E4");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("E6", "F6");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";

        GridObj.print();
    }
    void testRookBlock() {
        Grid GridObj;
        GridObj.init();

        GridObj.removePiecesGroup("Black", "Pawn");
        GridObj.removePiecesGroup("White", "Pawn");
        GridObj.movePiece("E8", "E7");
        GridObj.movePiece("E7", "E6");
        GridObj.movePiece("E6", "E5");

        GridObj.movePiece("H1", "H5");
        GridObj.movePiece("A1", "A4");
        GridObj.movePiece("A4", "G4");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("G4", "G5");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("G5", "G6");

        GridObj.movePiece("D1", "G4");
        GridObj.movePiece("G4", "G5");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("G6", "G7");
        GridObj.movePiece("G7", "E7");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("G5", "F6");
        GridObj.movePiece("F6", "E6");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("H5", "H6");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.print();
    }
    void testBishop() {
        Grid GridObj;
        GridObj.init();

        GridObj.removePiecesGroup("Black", "Pawn");
        GridObj.removePiecesGroup("White", "Pawn");
        GridObj.movePiece("E8", "E7");
        GridObj.movePiece("E7", "E6");
        GridObj.movePiece("E6", "E5");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("F1", "G2");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("G2", "H3");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("C1", "B2");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("B2", "D4");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("D4", "C5");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("C5", "D6");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("D6", "C7");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("C7", "D6");
        GridObj.movePiece("D6", "E7");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("E7", "F6");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("F6", "G7");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("G7", "H6");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("H6", "F4");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";

        GridObj.print();
    }
    void testBishopBlock() {
        Grid GridObj;
        GridObj.init();

        GridObj.removePiecesGroup("Black", "Pawn");
        GridObj.removePiecesGroup("White", "Pawn");
        GridObj.movePiece("E8", "E7");
        GridObj.movePiece("E7", "E6");
        GridObj.movePiece("E6", "E5");


        GridObj.movePiece("C1", "B2");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("D1", "D4");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("D4", "D5");
        GridObj.movePiece("B2", "D4");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("D4", "C5");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("C5", "B6");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("B6", "C7");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("D5", "D6");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("D6", "E6");
        GridObj.movePiece("C7", "D6");
        GridObj.movePiece("D6", "F8");
        GridObj.movePiece("F8", "G7");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("E6", "F6");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.print();
    }
    void testQueenRook() {
        Grid GridObj;
        GridObj.init();

        GridObj.removePiecesGroup("Black", "Pawn");
        GridObj.removePiecesGroup("White", "Pawn");
        GridObj.movePiece("E8", "E7");
        GridObj.movePiece("E7", "E6");
        GridObj.movePiece("E6", "E5");

        GridObj.movePiece("H1", "H2");
        GridObj.movePiece("H2", "A2");
        GridObj.movePiece("A2", "A7");
        GridObj.movePiece("D1", "D2");
        GridObj.movePiece("D2", "H2");
        GridObj.movePiece("H2", "H1");


        GridObj.movePiece("H1", "H4");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("H4", "H5");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("H5", "F5");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("F5", "H5");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("H5", "H6");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("A1", "A4");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("A4", "A5");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("H6", "E6");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("E6", "E8");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("E8", "E7");
        GridObj.movePiece("E7", "B7");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("B7", "B5");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("B5", "C5");
        GridObj.movePiece("C5", "C4");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.print();
    }
    void testQueenBishop() {
        Grid GridObj;
        GridObj.init();

        GridObj.removePiecesGroup("Black", "Pawn");
        GridObj.removePiecesGroup("White", "Pawn");
        GridObj.movePiece("E8", "E7");
        GridObj.movePiece("E7", "E6");
        GridObj.movePiece("E6", "E5");
        GridObj.removePiece("C1");

        GridObj.movePiece("D1", "C1");
        GridObj.movePiece("C1", "B2");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("B2", "D4");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("D4", "C5");

        GridObj.movePiece("C5", "D6");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("D6", "C7");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("C7", "D6");
        GridObj.movePiece("D6", "E7");

        GridObj.movePiece("E7", "F6");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("F6", "G7");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("G7", "H6");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("H6", "F4");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.print();
    }
    void testQueenRookBlock() {
        Grid GridObj;
        GridObj.init();

        GridObj.removePiecesGroup("Black", "Pawn");
        GridObj.removePiecesGroup("White", "Pawn");
        GridObj.movePiece("E8", "E7");
        GridObj.movePiece("E7", "E6");
        GridObj.movePiece("E6", "E5");

        GridObj.movePiece("D1", "D2");
        GridObj.movePiece("D2", "A5");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("D8", "D5");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("A5", "A7");
        GridObj.movePiece("A7", "E7");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("D5", "E6");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("E7", "G5");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("E6", "F5");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("G5", "E3");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("F5", "E4");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.print();
    }
    void testQueenBishopBlock() {
        Grid GridObj;
        GridObj.init();

        GridObj.removePiecesGroup("Black", "Pawn");
        GridObj.removePiecesGroup("White", "Pawn");
        GridObj.movePiece("E8", "E7");
        GridObj.movePiece("E7", "E6");
        GridObj.movePiece("E6", "E5");
        GridObj.removePiece("C1");

        GridObj.movePiece("D1", "C1");
        GridObj.movePiece("C1", "B2");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("D8", "D1");
        GridObj.movePiece("D1", "D4");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("D4", "D5");
        GridObj.movePiece("B2", "D4");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("D4", "C5");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("C5", "B6");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("B6", "C7");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("D5", "D6");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";

        GridObj.movePiece("D6", "E6");
        GridObj.movePiece("C7", "D6");
        GridObj.movePiece("D6", "F8");
        GridObj.movePiece("F8", "G7");
        //std::cout << "1: " << GridObj.check("E5", 'B') << "\n";
        GridObj.movePiece("E6", "F6");
        //std::cout << "0: " << GridObj.check("E5", 'B') << "\n";
        GridObj.print();
    }
};

#endif