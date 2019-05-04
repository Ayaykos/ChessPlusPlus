#ifndef GRID_H
#define GRID_H
#include <iostream>
#include <string>
#include "game.h"
#include "helper.h"
#include "conversions.h"

class Grid {
public:
    void initPieces();
    void initGrid();
    void fill();
    void print();
    /*Piece* operator[](std::string lookup) {
        int x = alphToNumX(lookup);
        int y = alphToNumY(lookup);
        return grid[x][y];
    }*/
    void movePiece(std::string position1, std::string position2);
    void removePiece(std::string position);
    void restoreGrid();
    //function only for testing
    void removePiecesGroup(std::string team, std::string title);
    ~Grid();
    bool checkRookPath(int p1x, int p1y, int p2x, int p2y);
    bool checkBishopPath(int p1x, int p1y, int p2x, int p2y);
    bool checkQueenPath(int p1x, int p1y, int p2x, int p2y);
    bool checkKingPath(int p1x, int p1y, int p2x, int p2y);
    bool checkMove(int p1x, int p1y, int p2x, int p2y);

private:
    std::vector<std::vector<Piece*>> grid;
    std::vector<std::vector<Piece*>> WhitePieces;
    std::vector<std::vector<Piece*>> BlackPieces;
    std::vector<Piece*> CapturedWhitePieces;
    std::vector<Piece*> CapturedBlackPieces;
};


void Grid::initPieces() {
    fillPieces(WhitePieces, 'W');
    fillPieces(BlackPieces, 'B');
}
void Grid::initGrid() {
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
void Grid::fill() {
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
void Grid::print() {
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

void Grid::movePiece(std::string position1, std::string position2) {
    int x = alphToNumX(position1);
    int y = alphToNumY(position1);
    int newx = alphToNumX(position2);
    int newy = alphToNumY(position2);

    if (grid[x][y]->checkValidMove(newx, newy) == true) {
        //CHECKMOVE NEEDS TO BE DONE BEFORE ->MOVE CHANGES XPOS & YPOS
        if (checkMove(x, y, newx, newy) == true) {
            grid[x][y]->move(newx, newy);
            updateGrid(x, y, newx, newy, grid);
        }
        else {
            //std::cout << "\tPath Blocked." << "\n";
        }
    }
}
void Grid::removePiece(std::string position) {
    grid[alphToNumX(position)][alphToNumY(position)] = nullptr;
}
void Grid::restoreGrid() {
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
    this->fill();
}
//function only for testing
void Grid::removePiecesGroup(std::string team, std::string title) {
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
bool Grid::checkRookPath(int p1x, int p1y, int p2x, int p2y) {
    //right
    if (abs(p2x - p1x) > 0 && p2x > p1x) {
        for (int i = p1x + 1; i <= p2x; ++i) {
            if (grid[i][p1y] != nullptr) {
                std::cout << "\tBlocked by: " <<
                    grid[i][p1y]->getFullTeam() << " " <<
                    grid[i][p1y]->getTitle() << " at " <<
                    numToAlph(i, p1y) << "\n";
                return false;
            }
        }
        return true;
    }
    //left
    else if (abs(p2x - p1x) > 0 && p1x > p2x) {
        for (int i = p1x - 1; i >= p2x; --i) {
            if (grid[i][p1y] != nullptr) {
                std::cout << "\tBlocked by: " <<
                    grid[i][p1y]->getFullTeam() << " " <<
                    grid[i][p1y]->getTitle() << " at " <<
                    numToAlph(i, p1y) << "\n";
                return false;
            }
        }
        return true;
    }
    //down
    else if (abs(p2y - p1y) > 0 && p2y > p1y) {
        for (int i = p1y + 1; i <= p2y; ++i) {
            if (grid[p1x][i] != nullptr) {
                std::cout << "\tBlocked by: " <<
                    grid[p1x][i]->getFullTeam() << " " <<
                    grid[p1x][i]->getTitle() << " at " <<
                    numToAlph(p1x, i) << "\n";
                return false;
            }
        }
        return true;
    }
    //up
    else {
        for (int i = p1y - 1; i >= p2y; --i) {
            if (grid[p1x][i] != nullptr) {
                std::cout << "\tBlocked by: " <<
                    grid[p1x][i]->getFullTeam() << " " <<
                    grid[p1x][i]->getTitle() << " at " <<
                    numToAlph(p1x, i) << "\n";
                return false;
            }
        }
        return true;
    }
    std::cout << "error in checkRootPath" << "\n";
    assert(false);
    return false;
}
bool Grid::checkBishopPath(int p1x, int p1y, int p2x, int p2y) {

    if ((abs(p2x - p1x) > 0 && p2x > p1x) &&
        (abs(p2y - p1y) > 0 && p2y > p1y)) {
        for (int i = 0; i < abs(p1x - p2x); ++i) {
            if (grid[p1x + i + 1][p1y + i + 1] != nullptr) {
                std::cout << "\tBlocked by: " <<
                    grid[p1x + i + 1][p1y + i + 1]->getFullTeam() << " " <<
                    grid[p1x + i + 1][p1y + i + 1]->getTitle() << " at " <<
                    numToAlph(p1x + i + 1, p1y + i + 1) << std::endl;
                return false;
            }
        }
        return true;
    }
    else if ((abs(p2x - p1x) > 0 && p2x > p1x) &&
        (abs(p2y - p1y) > 0 && p1y > p2y)) {
        for (int i = 0; i < abs(p1x - p2x); ++i) {
            if (grid[p1x + i + 1][p1y - i - 1] != nullptr) {
                std::cout << "\tBlocked by: " <<
                    grid[p1x + i + 1][p1y - i - 1]->getFullTeam() << " " <<
                    grid[p1x + i + 1][p1y - i - 1]->getTitle() << " at " <<
                    numToAlph(p1x + i + 1, p1y - i - 1) << std::endl;
                return false;
            }
        }
        return true;
    }
    else if ((abs(p2x - p1x) > 0 && p1x > p2x) &&
        (abs(p2y - p1y) > 0 && p2y > p1y)) {
        for (int i = 0; i < abs(p1x - p2x); ++i) {
            if (grid[p1x - i - 1][p1y + i + 1] != nullptr) {
                std::cout << "\tBlocked by: " <<
                    grid[p1x - i - 1][p1y + i + 1]->getFullTeam() << " " <<
                    grid[p1x - i - 1][p1y + i + 1]->getTitle() << " at " <<
                    numToAlph(p1x - i - 1, p1y + i + 1) << std::endl;
                return false;
            }
        }
        return true;
    }
    else {
        for (int i = 0; i < abs(p1x - p2x); ++i) {
            if (grid[p1x - i - 1][p1y - i - 1] != nullptr) {
                std::cout << "\tBlocked by: " <<
                    grid[p1x - i - 1][p1y - i - 1]->getFullTeam() << " " <<
                    grid[p1x - i - 1][p1y - i - 1]->getTitle() << " at " <<
                    numToAlph(p1x - i - 1, p1y - i - 1) << std::endl;
                return false;
            }
        }
        return true;
    }
    std::cout << "error in checkBishopPath" << "\n";
    assert(false);
    return false;
}
bool Grid::checkQueenPath(int p1x, int p1y, int p2x, int p2y) {
    if (abs(p2x - p1x) > 0 && abs(p2y - p1y) > 0) {
        return this->checkBishopPath(p1x, p1y, p2x, p2y);
    }
    return this->checkRookPath(p1x, p1y, p2x, p2y);
}
bool Grid::checkKingPath(int p1x, int p1y, int p2x, int p2y) {
    if (grid[p2x][p2y] != nullptr) {
        if (grid[p2x][p2y]->getTeam() == grid[p1x][p1y]->getTeam()) {
            std::cout << "\tBlocked by team member: " <<
                grid[p2x][p2y]->getFullTeam() << " " <<
                grid[p2x][p2y]->getTitle() << " at " <<
                numToAlph(p2x, p2y) << std::endl;
            return false;
        }
    }
    return true;
}
bool Grid::checkMove(int p1x, int p1y, int p2x, int p2y) {

    if (grid[p2x][p2y] != nullptr) {
        if (grid[p1x][p1y]->getTeam() ==
            grid[p2x][p2y]->getTeam()) {
            std::cout << "\tBlocked by " << grid[p2x][p2y]->getFullTeam() << " "
                << grid[p2x][p2y]->getTitle() << " in place on " <<
                numToAlph(p2x, p2y) << "\n";
            return false;
        }
    }
    if (grid[p1x][p1y]->getTitleChar() == 'R') {
        return this->checkRookPath(p1x, p1y, p2x, p2y);
    }
    if (grid[p1x][p1y]->getTitleChar() == 'B') {
        return this->checkBishopPath(p1x, p1y, p2x, p2y);
    }
    if (grid[p1x][p1y]->getTitleChar() == 'K') {
        //nullptr check already done??
        return this->checkKingPath(p1x, p1y, p2x, p2y);
    }
    if (grid[p1x][p1y]->getTitleChar() == 'Q') {
        return this->checkQueenPath(p1x, p1y, p2x, p2y);
    }
    //use polymorphism similar to move function to determine
    //whether specific piece can make the travel
    return true;
}

Grid::~Grid() {
    deletePieces(WhitePieces);
    deletePieces(BlackPieces);
}
#endif