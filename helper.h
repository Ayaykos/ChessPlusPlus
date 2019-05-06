#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <cassert>
#include "conversions.h"

void updateGrid(int position1x, int position1y,
    int position2x, int position2y,
    std::vector<std::vector<Piece*>> &grid) {

    grid[position2x][position2y] = grid[position1x][position1y];
    grid[position1x][position1y] = nullptr;
}

void fillPieces(std::vector<std::vector<Piece*>> &Pieces, char team) {
    assert(Pieces.empty());
    std::vector<Piece*> kings;
    std::vector<Piece*> queens;
    std::vector<Piece*> rooks;
    std::vector<Piece*> bishops;
    std::vector<Piece*> knights;
    std::vector<Piece*> pawns;

    if (team == 'W') {
        Piece *king = new King(team, "E1");
        kings.push_back(king);
        Piece *queen = new Queen(team, "D1");
        queens.push_back(queen);

        Piece *knight = new Knight(team, "B1");
        knights.push_back(knight);
        Piece *knight2 = new Knight(team, "G1");
        knights.push_back(knight2);

        Piece *bishop = new Bishop(team, "C1");
        bishops.push_back(bishop);
        Piece *bishop2 = new Bishop(team, "F1");
        bishops.push_back(bishop2);


        Piece *rook = new Rook(team, "A1");
        rooks.push_back(rook);
        Piece *rook2 = new Rook(team, "H1");
        rooks.push_back(rook2);
    }
    else {
        Piece *king = new King(team, "E8");
        kings.push_back(king);
        Piece *queen = new Queen(team, "D8");
        queens.push_back(queen);

        Piece *knight = new Knight(team, "B8");
        knights.push_back(knight);
        Piece *knight2 = new Knight(team, "G8");
        knights.push_back(knight2);

        Piece *bishop = new Bishop(team, "C8");
        bishops.push_back(bishop);
        Piece *bishop2 = new Bishop(team, "F8");
        bishops.push_back(bishop2);

        Piece *rook = new Rook(team, "A8");
        rooks.push_back(rook);
        Piece *rook2 = new Rook(team, "H8");
        rooks.push_back(rook2);
    }
    for (int i = 0; i < 8; ++i) {
        if (team == 'W') {
            Piece *pawn = new Pawn(team, std::string() + char(i + 65) + "2");
            pawns.push_back(pawn);
        }
        else {
            Piece *pawn = new Pawn(team, std::string() + char(i + 65) + "7");
            pawns.push_back(pawn);
        }
    }
    Pieces.push_back(kings);
    Pieces.push_back(queens);
    Pieces.push_back(rooks);
    Pieces.push_back(bishops);
    Pieces.push_back(knights);
    Pieces.push_back(pawns);
    kings.clear();
    queens.clear();
    rooks.clear();
    bishops.clear();
    knights.clear();
    pawns.clear();
}
void deletePieces(std::vector<std::vector<Piece*>>Pieces) {
    assert(Pieces.size() == 6);
    //std::cout << Pieces.size() << "\n";
    for (size_t i = 0; i < Pieces.size(); ++i) {
        for (size_t j = 0; j < Pieces[i].size(); ++j) {
            delete Pieces[i][j];
        }
    }
}
void printPieces(std::vector<std::vector<Piece*>>Pieces) {
    for (size_t i = 0; i < Pieces.size(); ++i) {
        for (size_t j = 0; j < Pieces[i].size(); ++j) {
            Pieces[i][j]->print_details();
        }
    }
}
#endif