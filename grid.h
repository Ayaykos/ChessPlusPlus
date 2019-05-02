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
                std::cout << "  //Path Check Failed." << "\n";
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
        fillGrid(WhitePieces, BlackPieces, grid);
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