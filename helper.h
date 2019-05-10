#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include "conversions.h"

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
        king->initID(0);
        kings.push_back(king);
        Piece *queen = new Queen(team, "D1");
        queen->initID(1);
        queens.push_back(queen);

        Piece *rook = new Rook(team, "A1");
        rook->initID(2);
        rooks.push_back(rook);
        
        Piece *rook2 = new Rook(team, "H1");
        rook2->initID(3);
        rooks.push_back(rook2);

        Piece *bishop = new Bishop(team, "C1");
        bishop->initID(4);
        bishops.push_back(bishop);
        Piece *bishop2 = new Bishop(team, "F1");
        bishop2->initID(5);
        bishops.push_back(bishop2);

        Piece *knight = new Knight(team, "B1");
        knight->initID(6);
        knights.push_back(knight);
        Piece *knight2 = new Knight(team, "G1");
        knight2->initID(7);
        knights.push_back(knight2);
    }
    else {
        Piece *king = new King(team, "E8");
        king->initID(16);
        kings.push_back(king);
        Piece *queen = new Queen(team, "D8");
        queen->initID(17);
        queens.push_back(queen);

        Piece *rook = new Rook(team, "A8");
        rook->initID(18);
        rooks.push_back(rook);
        Piece *rook2 = new Rook(team, "H8");
        rook2->initID(19);
        rooks.push_back(rook2);

        Piece *bishop = new Bishop(team, "C8");
        bishop->initID(20);
        bishops.push_back(bishop);
        Piece *bishop2 = new Bishop(team, "F8");
        bishop2->initID(21);
        bishops.push_back(bishop2);

        Piece *knight = new Knight(team, "B8");
        knight->initID(22);
        knights.push_back(knight);
        Piece *knight2 = new Knight(team, "G8");
        knight2->initID(23);
        knights.push_back(knight2);
    }
    for (int i = 0; i < 8; ++i) {
        if (team == 'W') {
            Piece *pawn = new Pawn(team, std::string() + char(i + 65) + "2");
            pawn->initID(i + 8);
            pawns.push_back(pawn);
        }
        else {
            Piece *pawn = new Pawn(team, std::string() + char(i + 65) + "7");
            pawn->initID(i + 24);
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
void fillPieces(std::string fileName, 
    std::vector<std::vector<Piece*>> &Pieces, char team) {
    assert(Pieces.empty());
    std::ifstream fin;
    fin.open(fileName);
    if (!fin.is_open()) {
        std::cout << "Error opening " << fileName << std::endl;
    }
    char titleChar;
    std::vector<Piece*> kings;
    std::vector<Piece*> queens;
    std::vector<Piece*> rooks;
    std::vector<Piece*> bishops;
    std::vector<Piece*> knights;
    std::vector<Piece*> pawns;

    int rookCountW = 0, bishopCountW = 0, knightCountW = 0, pawnCountW = 0;
    int rookCountB = 0, bishopCountB = 0, knightCountB = 0, pawnCountB = 0;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            fin >> titleChar;
            if (titleChar == 'K') {
                Piece *king = new King('W', numToAlph(j, i));
                king->initID(0);
                kings.push_back(king);
            }
            else if (titleChar == 'k') {
                Piece *king = new King('B', numToAlph(j, i));
                king->initID(16);
                kings.push_back(king);
            }
            else if (titleChar == 'Q') {
                Piece *queen = new Queen('W', numToAlph(j, i));
                queen->initID(1);
                queens.push_back(queen);
            }     
            else if (titleChar == 'q') {
                Piece *queen = new Queen('B', numToAlph(j, i));
                queen->initID(17);
                queens.push_back(queen);
            }
            else if (titleChar == 'R') {
                Piece *rook = new Rook('W', numToAlph(j, i));
                rook->initID(2 + rookCountW);
                ++rookCountW;
                rooks.push_back(rook);
            }
            else if (titleChar == 'r') {
                Piece *rook = new Rook('B', numToAlph(j, i));
                rook->initID(18 + rookCountB);
                ++rookCountB;
                rooks.push_back(rook);
            }
            else if (titleChar == 'B') {
                Piece *bishop = new Bishop('W', numToAlph(j, i));
                bishop->initID(4 + bishopCountW);
                ++bishopCountW;
                bishops.push_back(bishop);
            }
            else if (titleChar == 'b') {
                Piece *bishop = new Bishop('B', numToAlph(j, i));
                bishop->initID(20 + bishopCountB);
                ++bishopCountB;
                bishops.push_back(bishop);
            }
            else if (titleChar == 'N') {
                Piece *knight = new Knight('W', numToAlph(j, i));
                knight->initID(6 + knightCountW);
                ++knightCountW;
                knights.push_back(knight);
            }
            else if (titleChar == 'n') {
                Piece *knight = new Knight('B', numToAlph(j, i));
                knight->initID(22 + knightCountB);
                ++knightCountB;
                knights.push_back(knight);
            }
            else if (titleChar == 'P') {
                Piece *pawn = new Pawn('W' , numToAlph(j, i));
                pawn->initID(8 + pawnCountW);
                ++pawnCountW;
                pawns.push_back(pawn);
            }
            else if (titleChar == 'p') {
                Piece *pawn = new Pawn('B', numToAlph(j, i));
                pawn->initID(24 + pawnCountB);
                ++pawnCountB;
                pawns.push_back(pawn);
            }
            //std::cout << titleChar << " at " << numToAlph(j,i) << "\n";
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
void deletePromotedPieces(std::pair<std::vector<Piece*>,
    std::vector<Piece*>>PiecePair) {
    for (size_t i = 0; i < PiecePair.first.size(); ++i) {
        delete PiecePair.first[i];
    }
    for (size_t i = 0; i < PiecePair.second.size(); ++i) {
        delete PiecePair.second[i];
    }
}
void printPieces(std::vector<std::vector<Piece*>>Pieces) {
    for (size_t i = 0; i < Pieces.size(); ++i) {
        for (size_t j = 0; j < Pieces[i].size(); ++j) {
            Pieces[i][j]->print_details();
        }
    }
}
std::string promoteInput() {
    std::string in;
    bool validInput = false;
    while (validInput == false) {
        std::cout << "\nChoose piece to promote pawn to: ";
        std::cin >> in;
        if (in.size() <= 0) {
            std::cout << "Error. Re-enter.";
            continue;
        }
        if (toupper(in[0]) == 'Q') {
            if (in.size() > 1) {
                for (auto & i : in) i = toupper(i);
                if (in.size() != 5 || in != "QUEEN") {
                    std::cout << "Error. Re-enter.";
                    continue;
                }
                return "Queen";
                validInput = true;
            }
            else {
                return "Queen";
                validInput = true;
            }
            continue;
        }
        else if (toupper(in[0]) == 'R') {
            if (in.size() > 1) {
                for (auto & i : in) i = toupper(i);
                if (in.size() != 4 || in != "ROOK") {
                    std::cout << "Error. Re-enter.";
                    continue;
                }
                return "Rook";
                validInput = true;
            }
            else {
                return "Rook";
                validInput = true;
            }
            continue;
        }
        else if (toupper(in[0]) == 'B') {
            if (in.size() > 1) {
                for (auto & i : in) i = toupper(i);
                if (in.size() != 6 || in != "BISHOP") {
                    std::cout << "Error. Re-enter.";
                    continue;
                }
                return "Bishop";
                validInput = true;
            }
            else {
                return "Bishop";
                validInput = true;
            }     
            continue;
        }
        else if (toupper(in[0]) == 'K') {
            if (in.size() > 1) {
                for (auto & i : in) i = toupper(i);
                if (in == "KING") {
                    std::cout << "Cannot promote to King.";
                    continue;
                }
                if (in.size() != 6 || in != "KNIGHT") {
                    std::cout << "Error. Re-enter.";
                    continue;
                }
                return "Knight";
                validInput = true;
            }
            else {
                return "Knight";
                validInput = true;
            }      
            continue;
        }
        else if (toupper(in[0]) == 'P') {
            if (in.size() > 1) {
                for (auto & i : in) i = toupper(i);
                if (in == "PAWN") {
                    std::cout << "Must promote to non-pawn piece.";
                    continue;
                }
                std::cout << "Error. Re-enter.";
                continue;
            }
            else {
                std::cout << "Must promote to non-pawn piece.";
            }
            continue;
        }
        else {
            std::cout << "Error. Re-enter.";
        }
    }
    std::cout << "Error in promoteInput\n";
    assert(false);
    return "error";
}
bool checkKnight(std::vector<std::vector<Piece*>>grid, 
    std::string kingLocation, char kingTeam) {
    int p1x = alphToNumX(kingLocation), p1y = alphToNumY(kingLocation);
    if (p1x - 1 >= 0 && p1y - 2 >= 0) {
        if (grid[p1x - 1][p1y - 2] != nullptr) {
            if (grid[p1x - 1][p1y - 2]->getTeam() != kingTeam &&
                grid[p1x - 1][p1y - 2]->getTitleChar() == 'k') {
                return true;
            }
        }
    }
    if (p1x + 1 < 8 && p1y - 2 >= 0) {
        if (grid[p1x + 1][p1y - 2] != nullptr) {
            if (grid[p1x + 1][p1y - 2]->getTeam() != kingTeam &&
                grid[p1x + 1][p1y - 2]->getTitleChar() == 'k') {
                return true;
            }
        }
    }
    if (p1x + 2 < 8 && p1y - 1 >= 0) {
        if (grid[p1x + 2][p1y - 1] != nullptr) {
            if (grid[p1x + 2][p1y - 1]->getTeam() != kingTeam &&
                grid[p1x + 2][p1y - 1]->getTitleChar() == 'k') {
                return true;
            }
        }
    }
    if (p1x + 2 < 8 && p1y + 1 < 8) {
        if (grid[p1x + 2][p1y + 1] != nullptr) {
            if (grid[p1x + 2][p1y + 1]->getTeam() != kingTeam &&
                grid[p1x + 2][p1y + 1]->getTitleChar() == 'k') {
                return true;
            }
        }
    }
    if (p1x + 1 < 8 && p1y + 2 < 8) {
        if (grid[p1x + 1][p1y + 2] != nullptr) {
            if (grid[p1x + 1][p1y + 2]->getTeam() != kingTeam &&
                grid[p1x + 1][p1y + 2]->getTitleChar() == 'k') {
                return true;
            }
        }
    }
    if (p1x - 1 >= 0 && p1y + 2 < 8) {
        if (grid[p1x - 1][p1y + 2] != nullptr) {
            if (grid[p1x - 1][p1y + 2]->getTeam() != kingTeam &&
                grid[p1x - 1][p1y + 2]->getTitleChar() == 'k') {
                return true;
            }
        }
    }
    if (p1x - 2 >= 0 && p1y - 1 >= 0) {
        if (grid[p1x - 2][p1y - 1] != nullptr) {
            if (grid[p1x - 2][p1y - 1]->getTeam() != kingTeam &&
                grid[p1x - 2][p1y - 1]->getTitleChar() == 'k') {
                return true;
            }
        }
    }
    if (p1x - 2 >= 0 && p1y + 1 < 8) {
        if (grid[p1x - 2][p1y + 1] != nullptr) {
            if (grid[p1x - 2][p1y + 1]->getTeam() != kingTeam &&
                grid[p1x - 2][p1y + 1]->getTitleChar() == 'k') {
                return true;
            }
        }
    }
    return false;
}
bool checkPawn(std::vector<std::vector<Piece*>>grid,
    std::string kingLocation, char kingTeam) {
    int p1x = alphToNumX(kingLocation), p1y = alphToNumY(kingLocation);
    
    if (kingTeam == 'W') {
        if (p1x - 1 >= 0 && p1y - 1 >= 0) {
            if (grid[p1x - 1][p1y - 1] != nullptr) {
                if (grid[p1x - 1][p1y - 1]->getTeam() != kingTeam &&
                    grid[p1x - 1][p1y - 1]->getTitleChar() == 'P') {
                    return true;
                }
            }
        }
        if (p1x + 1 < 8 && p1y - 1 >= 0) {
            if (grid[p1x + 1][p1y - 1] != nullptr) {
                if (grid[p1x + 1][p1y - 1]->getTeam() != kingTeam &&
                    grid[p1x + 1][p1y - 1]->getTitleChar() == 'P') {
                    return true;
                }
            }
        }
    }
    else {
        if (p1x - 1 >= 0 && p1y + 1 < 8) {
            if (grid[p1x - 1][p1y + 1] != nullptr) {
                if (grid[p1x - 1][p1y + 1]->getTeam() != kingTeam &&
                    grid[p1x - 1][p1y + 1]->getTitleChar() == 'P') {
                    return true;
                }
            }
        }
        if (p1x + 1 < 8 && p1y + 1 < 8) {
            if (grid[p1x + 1][p1y + 1] != nullptr) {
                if (grid[p1x + 1][p1y + 1]->getTeam() != kingTeam &&
                    grid[p1x + 1][p1y + 1]->getTitleChar() == 'P') {
                    return true;
                }
            }
        }
    }
    return false;
}
bool checkRook(std::vector<std::vector<Piece*>>grid,
    std::string kingLocation, char kingTeam, char rook) {
    int p1x = alphToNumX(kingLocation), p1y = alphToNumY(kingLocation);

    for (int x = p1x + 1; x < 8; ++x) {
        if (grid[x][p1y] != nullptr) {
            if (grid[x][p1y]->getTeam() == kingTeam) break;
            if (grid[x][p1y]->getTitleChar() != rook) break;
            return true;
        }
    }
    for (int x = p1x - 1; x >= 0; --x) {
        if (grid[x][p1y] != nullptr) {
            if (grid[x][p1y]->getTeam() == kingTeam) break;
            if (grid[x][p1y]->getTitleChar() != rook) break;
            return true;
        }
    }
    for (int y = p1y + 1; y < 8; ++y) {
        if (grid[p1x][y] != nullptr) {
            if (grid[p1x][y]->getTeam() == kingTeam) break;
            if (grid[p1x][y]->getTitleChar() != rook) break;
            return true;
        }
    }
    for (int y = p1y - 1; y >= 0; --y) {
        if (grid[p1x][y] != nullptr) {
            if (grid[p1x][y]->getTeam() == kingTeam) break;
            if (grid[p1x][y]->getTitleChar() != rook) break;
            return true;
        }
    }
    return false;
}
bool checkBishop(std::vector<std::vector<Piece*>>grid,
    std::string kingLocation, char kingTeam, char bishop) {
    int p1x = alphToNumX(kingLocation), p1y = alphToNumY(kingLocation);
    for (int i = 1; (p1x + i < 8) && (p1y + i < 8); ++i) {
        if (grid[p1x + i][p1y + i] != nullptr) {
            if (grid[p1x + i][p1y + i]->getTeam() == kingTeam) break;
            if (grid[p1x + i][p1y + i]->getTitleChar() != bishop) break;
            if (grid[p1x + i][p1y + i]->getTeam() != kingTeam &&
                grid[p1x + i][p1y + i]->getTitleChar() == bishop) {
                return true;
            }
        }
    }
    for (int i = 1; (p1x + i < 8) && (p1y - i >= 0); ++i) {
        if (grid[p1x + i][p1y - i] != nullptr) {
            if (grid[p1x + i][p1y - i]->getTeam() == kingTeam) break;
            if (grid[p1x + i][p1y - i]->getTitleChar() != bishop) break;
            if (grid[p1x + i][p1y - i]->getTeam() != kingTeam &&
                grid[p1x + i][p1y - i]->getTitleChar() == bishop) {
                return true;
            }
        }
    }
    for (int i = 1; (p1x - i >= 0) && (p1y + i < 8); ++i) {
        if (grid[p1x - i][p1y + i] != nullptr) {
            if (grid[p1x - i][p1y + i]->getTeam() == kingTeam) break;
            if (grid[p1x - i][p1y + i]->getTitleChar() != bishop) break;
            if (grid[p1x - i][p1y + i]->getTeam() != kingTeam &&
                grid[p1x - i][p1y + i]->getTitleChar() == bishop) {
                return true;
            }
        }
    }
    for (int i = 1; (p1x - i >= 0) && (p1y - i >= 0); ++i) {
        if (grid[p1x - i][p1y - i] != nullptr) {
            if (grid[p1x - i][p1y - i]->getTeam() == kingTeam) break;
            if (grid[p1x - i][p1y - i]->getTitleChar() != bishop) break;
            if (grid[p1x - i][p1y - i]->getTeam() != kingTeam &&
                grid[p1x - i][p1y - i]->getTitleChar() == bishop) {
                return true;
            }
        }
    }
    return false;
}
bool checkQueen(std::vector<std::vector<Piece*>>grid,
    std::string kingLocation, char kingTeam) {
    return (checkRook(grid, kingLocation, kingTeam, 'Q') ||
        checkBishop(grid, kingLocation, kingTeam, 'Q'));
}
bool checkHelper(std::vector<std::vector<Piece*>>grid, 
    std::string kingPosition, char kingTeam) {
    if (checkKnight(grid, kingPosition, kingTeam) ||
        checkPawn(grid, kingPosition, kingTeam) ||
        checkRook(grid, kingPosition, kingTeam, 'R') ||
        checkBishop(grid, kingPosition, kingTeam, 'B') ||
        checkQueen(grid, kingPosition, kingTeam)) {
        /*
        std::cout << grid[alphToNumX(kingPosition)][alphToNumY(kingPosition)] <<
            " in check at " << kingPosition << "\n";*/
        return true;
    }
    return false;
}
bool checkKingCheckMate(std::vector<std::vector<Piece*>>grid,
    std::string kingPosition, char kingTeam) {
    int x = alphToNumX(kingPosition), y = alphToNumY(kingPosition);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (!checkHelper(grid, 
                numToAlph((x - 1) + j, (y - 1) + i), kingTeam)) {
                return false;
            }
        }
    }
    return true;
}

#endif