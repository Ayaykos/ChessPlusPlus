#ifndef TESTS_MISC_H
#define TESTS_MISC_H
#include <iostream>
#include <string>
#include "grid.h"
#include <vector>

class General {
public:
    void KingMoveCount() {
        Grid GridObj;
        GridObj.init();

        GridObj.removePiecesGroup("Black", "Pawn");
        assert(GridObj["E8"]->getMoveCount() == 0);
        GridObj.movePiece("E8", "E7");
        assert(GridObj["E7"]->getMoveCount() == 1);
        GridObj.movePiece("E7", "D6");
        assert(GridObj["D6"]->getMoveCount() == 2);

        GridObj.print();
    }
    void promoteInputTest() {
        Grid GridObj;
        GridObj.init();
        GridObj.removePiecesGroup("Black", "Pawn");
        GridObj.removePiecesGroup("Black", "Bishop");
        GridObj.movePiece("C2", "C4");
        GridObj.movePiece("C4", "C5");
        GridObj.movePiece("C5", "C6");
        GridObj.movePiece("C6", "C7");
        GridObj.movePiece("C7", "C8");

        GridObj.print();
        GridObj.restoreGrid();
        GridObj.removePiecesGroup("White", "Pawn");
        GridObj.removePiecesGroup("White", "Bishop");        
        GridObj.movePiece("C7", "C5");
        GridObj.movePiece("C5", "C4");
        GridObj.movePiece("C4", "C3");
        GridObj.movePiece("C3", "C2");
        GridObj.movePiece("C2", "C1");

        GridObj.print();
        //promoteInput();
    }
    void movePieceTest() {
        Grid GridObj;
        GridObj.init();
        GridObj.movePieceTest("A7", "A5");
        GridObj.print();

    }
};


#endif