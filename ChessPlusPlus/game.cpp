#include <iostream>
#include <string>
#include "game.h"
#include "helper.h"
#include <vector>
using namespace std;


int main() {

    vector<vector<Piece*>>WhitePieces;
    fillPieces(WhitePieces,'W');
    vector<vector<Piece*>>BlackPieces;
    fillPieces(BlackPieces, 'B');


    vector<vector<Piece*>> grid;
    fillGridInit(grid);
    fillGrid(WhitePieces,BlackPieces,grid);

    printGrid(grid);





    deletePieces(WhitePieces);
    deletePieces(BlackPieces);

    return 0;
}