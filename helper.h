#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <cassert>
#include "conversions.h"
#include "path.h"

void fillGridInit(std::vector<std::vector<Piece*>> &grid) {

    std::vector<Piece*> minigrid;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            //minigrid.push_back(char(j + 65) + std::to_string(8 - i));
            minigrid.push_back(nullptr);
        }
        grid.push_back(minigrid);
        minigrid.clear();
    }
    
}
void fillGrid(std::vector<std::vector<Piece*>>WhitePieces,
    std::vector<std::vector<Piece*>>BlackPieces,
    std::vector<std::vector<Piece*>> &grid) {
    for (size_t i = 0; i < WhitePieces.size(); ++i) {
        for (size_t j = 0; j < WhitePieces[i].size(); ++j) {
            grid[WhitePieces[i][j]->getXPos()][WhitePieces[i][j]->getYPos()] =
                WhitePieces[i][j];
        }
    }
    for (size_t i = 0; i < BlackPieces.size(); ++i) {
        for (size_t j = 0; j < BlackPieces[i].size(); ++j) {
            grid[BlackPieces[i][j]->getXPos()][BlackPieces[i][j]->getYPos()] =
                BlackPieces[i][j];
        }
    }
}
void updateGrid(int position1x,int position1y, 
    int position2x, int position2y,
    std::vector<std::vector<Piece*>> &grid) {

    grid[position2x][position2y] = grid[position1x][position1y];
    grid[position1x][position1y] = nullptr;
}

bool checkMove(int p1x, int p1y,
    int p2x, int p2y,
    std::vector<std::vector<Piece*>> &grid) {

    if (grid[p2x][p2y] != nullptr){
        if (grid[p1x][p1y]->getTeam() ==
            grid[p2x][p2y]->getTeam()) {
            std::cout << "\tBlocked by " << grid[p2x][p2y]->getFullTeam() << " " 
                << grid[p2x][p2y]->getTitle() << " in place on " << 
                numToAlph(p2x, p2y) << "\n";
            return false;
        }
    }
    if (grid[p1x][p1y]->getTitleChar() == 'R') {
        return checkRookPath(p1x, p1y, p2x, p2y, grid);
    }
    if (grid[p1x][p1y]->getTitleChar() == 'B') {
        return checkBishopPath(p1x, p1y, p2x, p2y, grid);
    }
    if (grid[p1x][p1y]->getTitleChar() == 'K') {
        //nullptr check already done??
        return checkKingPath(p1x, p1y, p2x, p2y, grid);
    }
    if (grid[p1x][p1y]->getTitleChar() == 'Q') {
        return checkQueenPath(p1x, p1y, p2x, p2y, grid);
    }
    //use polymorphism similar to move function to determine
    //whether specific piece can make the travel
    return true;
}
void printGrid(std::vector<std::vector<Piece*>> grid) {
    for (size_t i = 0; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid.size(); ++j) {
            //std::cout << "|__";
            if (grid[j][i] != nullptr) {
                std::cout << "|_" << grid[j][i]->getTitleChar() << "_";
            }
            else {
                std::cout << "|___";
            }
        }
        std::cout << "\n";
    }
    /*
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << "\n";
    }*/
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