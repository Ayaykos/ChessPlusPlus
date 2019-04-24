#include <iostream>
#include <string>
#include "gamesample.h"
#include "helper.h"
#include <vector>
using namespace std;


int main() {

    vector<vector<Piece*>>WhitePieces;
    fillPieces(WhitePieces,'B');
    printPieces(WhitePieces);
    deletePieces(WhitePieces);


    return 0;
}