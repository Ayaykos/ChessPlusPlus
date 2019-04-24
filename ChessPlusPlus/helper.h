#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <cassert>

std::string numToAlph(int xpos, int ypos) {
    return char(xpos + 65) + std::to_string(8 - ypos);
}
std::string alphToNum(std::string position_in) {
    return std::to_string(toupper(position_in[0]) - 65) +
        std::to_string((8 - (int(position_in[1]) - 48)));
}
void fillGrid(std::vector<std::vector<std::string>> &grid) {
    std::vector<std::string> minigrid;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            minigrid.push_back(char(j + 65) + std::to_string(8 - i));
        }
        grid.push_back(minigrid);
        minigrid.clear();
    }
}
void printGrid(std::vector<std::vector<std::string>> grid) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
std::string determinePosition(std::string title, char team) {
    if (title == "King") {
        if (team == 'W') { return "D1"; }
        else { return "D8"; }
    }
    else if (title == "Queen") {
        if (team == 'W') { return "E1"; }
        else { return "E8"; }
    }
}
void fillPieces(std::vector<std::vector<Piece*>> &Pieces, char team) {
    assert(Pieces.empty());
    std::vector<Piece*> kings;
    std::vector<Piece*> queens;
    std::vector<Piece*> rooks;
    std::vector<Piece*> bishops;
    std::vector<Piece*> knights;
    std::vector<Piece*> pawns;

    Piece *king = new King(team, determinePosition("King",team));
    kings.push_back(king);
    Piece *queen = new Queen(team, determinePosition("Queen", team));
    queens.push_back(queen);
    for (int i = 0; i < 2; ++i) {
        Piece *rook = new Rook(team);
        rooks.push_back(rook);
    }
    for (int i = 0; i < 2; ++i) {
        Piece *bishop = new Bishop(team);
        bishops.push_back(bishop);
    }
    if (team == 'W') {
       Piece *knight = new Knight(team, "B1");
       knights.push_back(knight);
       Piece *knight2 = new Knight(team, "G1");
       knights.push_back(knight);
    }
    else {
        Piece *knight = new Knight(team, "B8");
        knights.push_back(knight);
        Piece *knight2 = new Knight(team, "G8");
        knights.push_back(knight);
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
    //std::cout << Pieces.size() << std::endl;
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