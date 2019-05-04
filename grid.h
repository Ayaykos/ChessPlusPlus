#ifndef GRID_H
#define GRID_H
#include <iostream>
#include <string>
#include "game.h"
#include "helper.h"
#include "conversions.h"

class Grid {
public:
    void initPieces() {
        fillPieces(WhitePieces, 'W');
        fillPieces(BlackPieces, 'B');
    }
    void initGrid() {
        fillGridInit(grid);
    }
    void fill() {
        fillGrid(WhitePieces, BlackPieces, grid);
    }
    void print() {
        printGrid(grid);
    }

    Piece* operator[](std::string lookup) {
        int x = alphToNumX(lookup);
        int y = alphToNumY(lookup);
        return grid[x][y];
    }
    void movePiece(std::string position1, std::string position2) {
        int x = alphToNumX(position1);
        int y = alphToNumY(position1);
        int newx = alphToNumX(position2);
        int newy = alphToNumY(position2);

        if (grid[x][y]->checkValidMove(newx, newy) == true) {
            //CHECKMOVE NEEDS TO BE DONE BEFORE ->MOVE CHANGES XPOS & YPOS
            if (checkMove(x, y, newx, newy, grid) == true) {
                grid[x][y]->move(newx, newy);
                updateGrid(x, y, newx, newy, grid);
            }
            else {
                //std::cout << "\tPath Blocked." << "\n";
            }
        }
    }
    void removePiece(std::string position) {
        grid[alphToNumX(position)][alphToNumY(position)] = nullptr;
    }
    void restoreGrid() {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                grid[j][i] = nullptr;
            }

        }
        WhitePieces[0][0]->updateStatus(1);
        WhitePieces[0][0]->updatePos("E1");
        WhitePieces[1][0]->updateStatus(1);
        WhitePieces[1][0]->updatePos("D1");
        WhitePieces[2][0]->updateStatus(1);
        WhitePieces[2][0]->updatePos("A1");
        WhitePieces[2][1]->updateStatus(1);
        WhitePieces[2][1]->updatePos("H1");
        WhitePieces[3][0]->updateStatus(1);
        WhitePieces[3][0]->updatePos("C1");
        WhitePieces[3][1]->updateStatus(1);
        WhitePieces[3][1]->updatePos("F1");
        WhitePieces[4][0]->updateStatus(1);
        WhitePieces[4][0]->updatePos("B1");
        WhitePieces[4][1]->updateStatus(1);
        WhitePieces[4][1]->updatePos("G1");
        WhitePieces[5][0]->updateStatus(1);
        WhitePieces[5][0]->updatePos("B1");
        WhitePieces[5][1]->updateStatus(1);
        WhitePieces[5][1]->updatePos("G1");
        for (int i = 0; i < 8; ++i) {
            WhitePieces[5][i]->updateStatus(1);
            WhitePieces[5][i]->updatePos(std::string() + char(i + 65) + "2");
        }
        BlackPieces[0][0]->updateStatus(1);
        BlackPieces[0][0]->updatePos("E8");
        BlackPieces[1][0]->updateStatus(1);
        BlackPieces[1][0]->updatePos("D8");
        BlackPieces[2][0]->updateStatus(1);
        BlackPieces[2][0]->updatePos("A8");
        BlackPieces[2][1]->updateStatus(1);
        BlackPieces[2][1]->updatePos("H8");
        BlackPieces[3][0]->updateStatus(1);
        BlackPieces[3][0]->updatePos("C8");
        BlackPieces[3][1]->updateStatus(1);
        BlackPieces[3][1]->updatePos("F8");
        BlackPieces[4][0]->updateStatus(1);
        BlackPieces[4][0]->updatePos("B8");
        BlackPieces[4][1]->updateStatus(1);
        BlackPieces[4][1]->updatePos("G8");
        for (int i = 0; i < 8; ++i) {
            BlackPieces[5][i]->updateStatus(1);
            BlackPieces[5][i]->updatePos(std::string() + char(i + 65) + "7");
        }
        fillGrid(WhitePieces, BlackPieces, grid);
    }
    //function only for testing
    void removePiecesGroup(std::string team, std::string title) {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (grid[j][i] != nullptr) {
                    if (grid[j][i]->getFullTeam() == team &&
                        grid[j][i]->getTitle() == title) {
                        grid[j][i] = nullptr;
                    }
                }
            }
        }
    }
    ~Grid() {
        deletePieces(WhitePieces);
        deletePieces(BlackPieces);
    }
private:
    std::vector<std::vector<Piece*>> grid;
    std::vector<std::vector<Piece*>>WhitePieces;
    std::vector<std::vector<Piece*>>BlackPieces;
};

#endif