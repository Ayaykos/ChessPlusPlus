#ifndef GRID_H
#define GRID_H
#include <iostream>
#include <string>
#include "game.h"
#include "helper.h"

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
    void deleteAll() {
        deletePieces(WhitePieces);
        deletePieces(BlackPieces);
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

        if (grid[x][y]->move(newx, newy) == true) {
            updateGrid(x, y, newx, newy, grid);
        }
    }
private:
    std::vector<std::vector<Piece*>> grid;
    std::vector<std::vector<Piece*>>WhitePieces;
    std::vector<std::vector<Piece*>>BlackPieces;
};

#endif