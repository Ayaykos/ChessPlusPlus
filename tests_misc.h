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
};

#endif