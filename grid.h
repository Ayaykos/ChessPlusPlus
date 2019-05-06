#ifndef GRID_H
#define GRID_H
#include <iostream>
#include <string>
#include "game.h"
#include "helper.h"
#include "conversions.h"

class Grid {
public:
    Piece* operator[](std::string lookup);
    void initPieces();
    void initGrid();
    void fill();
    void init();
    void print();
    void movePiece(std::string position1, std::string position2);
    void restoreGrid();
    //function only for testing
    void removePiece(std::string position);
    //function only for testing
    void removePiecesGroup(std::string team, std::string title);
    void basicTakeOver(int p2x, int p2y);
    bool checkTeamBlock(int p1x, int p1y, int p2x, int p2y);
    bool checkRookPath(int p1x, int p1y, int p2x, int p2y);
    bool checkBishopPath(int p1x, int p1y, int p2x, int p2y);
    bool checkQueenPath(int p1x, int p1y, int p2x, int p2y);
    bool checkPawnPath(int p1x, int p1y, int p2x, int p2y);
    bool checkPath(int p1x, int p1y, int p2x, int p2y);
    void printCaptured();
    ~Grid();

private:
    std::vector<std::vector<Piece*>> grid;
    std::vector<std::vector<Piece*>> WhitePieces;
    std::vector<std::vector<Piece*>> BlackPieces;
    std::pair<std::vector<Piece*>, 
        std::vector<Piece*>>CapturedPieces;
};


Piece* Grid::operator[](std::string lookup) {
    int x = alphToNumX(lookup);
    int y = alphToNumY(lookup);
    return grid[x][y];
}
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
void Grid::init() {
    this->initPieces();
    this->initGrid();
    this->fill();
}
void Grid::print() {
    std::cout << "  ";
    for (size_t i = 0; i < grid.size(); ++i) {
        std::cout << "__" << char(i + 65) << "_";
    }
    std::cout << "\n";
    for (size_t i = 0; i < grid.size(); ++i) {
        std::cout << 8 - i << " ";
        for (size_t j = 0; j < grid.size(); ++j) {
            //std::cout << "|__";
            if (grid[j][i] != nullptr) {
                std::cout << "|_" << grid[j][i]->getTitleChar();
                grid[j][i]->getTeam() == 'W' ? std::cout << "_" :
                    std::cout << ".";
            }
            else {
                std::cout << "|___";
            }
        }
        if (i == 0) std::cout << "  B";
        if (i == 7) std::cout << "  W";
        std::cout << "\n";
    }
    std::cout << "\n";
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
        //checkPath NEEDS TO BE DONE BEFORE ->MOVE CHANGES XPOS & YPOS
        if (this->checkPath(x, y, newx, newy) == true) {
            grid[x][y]->move(newx, newy);
            this->print();
            std::cout << "x,y,nx,ny: " << x << " " << y << " " << newx << " " << newy << "\n";
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
    CapturedPieces.first.clear();
    CapturedPieces.second.clear();
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
void Grid::basicTakeOver(int p2x, int p2y) {
    grid[p2x][p2y]->getTeam() == 'W' ?
        CapturedPieces.first.push_back(grid[p2x][p2y]) :
        CapturedPieces.second.push_back(grid[p2x][p2y]);
}
bool Grid::checkTeamBlock(int p1x, int p1y, int p2x, int p2y) {
    if (grid[p2x][p2y] != nullptr) {
        if (grid[p2x][p2y]->getTeam() == grid[p1x][p1y]->getTeam()) {
            std::cout << "\tBlocked by team member: " << grid[p2x][p2y] <<
                " at " << numToAlph(p2x, p2y) << std::endl;
            return false;
        }
        else {
            std::cout << grid[p1x][p1y] << " overtook " <<
                grid[p2x][p2y] << " at " << numToAlph(p2x, p2y) << std::endl;
            grid[p2x][p2y]->getTeam() == 'W' ?
                CapturedPieces.first.push_back(grid[p2x][p2y]) :
                CapturedPieces.second.push_back(grid[p2x][p2y]);

            return true;
        }
    }
    return true;
}
//Path Functions
bool Grid::checkRookPath(int p1x, int p1y, int p2x, int p2y) {
    //right
    if (abs(p2x - p1x) > 0 && p2x > p1x) {
        for (int i = p1x + 1; i < p2x; ++i) {
            if (grid[i][p1y] != nullptr) {
                std::cout << "\tBlocked by: " <<
                    grid[i][p1y] << " at " <<
                    numToAlph(i, p1y) << "\n";
                return false;
            }
        }
        return checkTeamBlock(p1x,p1y,p2x,p2y);
    }
    //left
    else if (abs(p2x - p1x) > 0 && p1x > p2x) {
        for (int i = p1x - 1; i > p2x; --i) {
            if (grid[i][p1y] != nullptr) {
                std::cout << "\tBlocked by: " <<
                    grid[i][p1y] << " at " <<
                    numToAlph(i, p1y) << "\n";
                return false;
            }
        }
        return checkTeamBlock(p1x, p1y, p2x, p2y);
    }
    //down
    else if (abs(p2y - p1y) > 0 && p2y > p1y) {
        for (int i = p1y + 1; i < p2y; ++i) {
            if (grid[p1x][i] != nullptr) {
                std::cout << "\tBlocked by: " <<
                    grid[p1x][i] << " at " <<
                    numToAlph(p1x, i) << "\n";
                return false;
            }
        }
        return checkTeamBlock(p1x, p1y, p2x, p2y);
    }
    //up
    else {
        for (int i = p1y - 1; i > p2y; --i) {
            if (grid[p1x][i] != nullptr) {
                std::cout << "\tBlocked by: " <<
                    grid[p1x][i] << " at " <<
                    numToAlph(p1x, i) << "\n";
                return false;
            }
        }
        return checkTeamBlock(p1x, p1y, p2x, p2y);
    }
    std::cout << "error in checkRootPath" << "\n";
    assert(false);
    return false;
}
bool Grid::checkBishopPath(int p1x, int p1y, int p2x, int p2y) {

    if ((abs(p2x - p1x) > 0 && p2x > p1x) &&
        (abs(p2y - p1y) > 0 && p2y > p1y)) {
        for (int i = 0; i < abs(p1x - p2x) - 1; ++i) {
            if (grid[p1x + i + 1][p1y + i + 1] != nullptr) {
                std::cout << "\tBlocked by: " <<
                    grid[p1x + i + 1][p1y + i + 1] << " at " <<
                    numToAlph(p1x + i + 1, p1y + i + 1) << std::endl;
                return false;
            }
        }
        return checkTeamBlock(p1x,p1y,p2x,p2y);
    }
    else if ((abs(p2x - p1x) > 0 && p2x > p1x) &&
        (abs(p2y - p1y) > 0 && p1y > p2y)) {
        for (int i = 0; i < abs(p1x - p2x) - 1; ++i) {
            if (grid[p1x + i + 1][p1y - i - 1] != nullptr) {
                std::cout << "\tBlocked by: " <<
                    grid[p1x + i + 1][p1y - i - 1] << " at " <<
                    numToAlph(p1x + i + 1, p1y - i - 1) << std::endl;
                return false;
            }
        }
        return checkTeamBlock(p1x, p1y, p2x, p2y);
    }
    else if ((abs(p2x - p1x) > 0 && p1x > p2x) &&
        (abs(p2y - p1y) > 0 && p2y > p1y)) {
        for (int i = 0; i < abs(p1x - p2x) - 1; ++i) {
            if (grid[p1x - i - 1][p1y + i + 1] != nullptr) {
                std::cout << "\tBlocked by: " <<
                    grid[p1x - i - 1][p1y + i + 1] << " at " <<
                    numToAlph(p1x - i - 1, p1y + i + 1) << std::endl;
                return false;
            }
        }
        return checkTeamBlock(p1x, p1y, p2x, p2y);
    }
    else {
        for (int i = 0; i < abs(p1x - p2x) - 1; ++i) {
            if (grid[p1x - i - 1][p1y - i - 1] != nullptr) {
                std::cout << "\tBlocked by: " <<
                    grid[p1x - i - 1][p1y - i - 1] << " at " <<
                    numToAlph(p1x - i - 1, p1y - i - 1) << std::endl;
                return false;
            }
        }
        return checkTeamBlock(p1x, p1y, p2x, p2y);
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
bool Grid::checkPawnPath(int p1x, int p1y, int p2x, int p2y) {
    //give option to do en passant?

    //moving diagonally
    if (p2x != p1x) {
        std::cout << "//moving diagonally\n";
        //chosen move position is empty, enter enpassant possibility
        if (grid[p2x][p2y] == nullptr) {
            std::cout << "//chosen move position is empty, enter enpassant possibility\n";

            //position 1 below/above chose position has a piece
            if (grid[p2x][p1y] != nullptr) {
                std::cout << "//position 1 below/above chose position has a piece\n";

                //2nd piece is enemy
                if (grid[p2x][p1y]->getTeam() != grid[p1x][p1y]->getTeam()) {
                    std::cout << "//2nd piece is enemy\n";

                    //2nd piece has moved more than once
                    if (grid[p2x][p1y]->getMoveCount() > 1) {
                        std::cout << "//2nd piece has moved more than once, failed en passant\n";
                        //unsuccessful enpassant, wasn't opposites 1st move
                        return false;
                    }
                    //include second if for seeing if this turn was immediate move
                    std::cout << "//else successful en passant\n";
                    //else successful en passant
                    std::cout << "Valid move: " << grid[p1x][p1y]->getFullTeam()
                        << " Pawn from " << numToAlph(p1x, p1y) <<
                        " to " << numToAlph(p2x, p2y)
                        << "\n";
                    basicTakeOver(p2x, p1y);
                    return true;
                }
                //2nd piece is team member, blocked path
                std::cout << "//2nd piece is team member, blocked path\n";
                return false;
            }
            //invalid move, impossible en passant, return false
            std::cout << "//invalid move, impossible en passant, return false\n";
            return false;
        }
        //regular possible overtake
        //if 2nd piece isn't enemy
        else if (grid[p2x][p2y]->getTeam() == grid[p1x][p1y]->getTeam()) {
            std::cout << "//regular possibly overtake\n";
            std::cout << "//2nd piece isn't enemy, blocked\n";
            //blocked return false
            return false;
        }
        //2nd piece is enemy, successful regular overtake
        else {
            std::cout << "//2nd piece is enemy, successful regular overtake\n";
            std::cout << "Valid move: " << grid[p1x][p1y]->getFullTeam()
                << " Pawn from " << numToAlph(p1x, p1y) <<
                " to " << numToAlph(p2x, p2y)
                << "\n";
            basicTakeOver(p2x, p2y);
            return true;
        }
    }
    //moving straight
    //nonempty position
    if (grid[p2x][p2y] != nullptr) {
        if (grid[p2x][p2y]->getTeam() == grid[p1x][p1y]->getTeam()) {
            std::cout << "\tBlocked by team member: " << grid[p2x][p2y] <<
                " at " << numToAlph(p2x, p2y) << std::endl;
            return false;
        }
        else {
            std::cout << "Invalid move: " << grid[p1x][p1y]->getFullTeam()
                << " Pawn from " << numToAlph(p1x, p1y) <<
                " to " << numToAlph(p2x, p2y)
                << "\n";
            return false;
        }
    }
    std::cout << "Valid move: " << grid[p1x][p1y]->getFullTeam()
        << " Pawn from " << numToAlph(p1x, p1y) <<
        " to " << numToAlph(p2x, p2y)
        << "\n";
    return true;
}
//differentiate between blocks along the way and block at end
//any piece blocks along the way are issue
//piece at end depends on team or not

//test for end of path team/not team
bool Grid::checkPath(int p1x, int p1y, int p2x, int p2y) {
    if (grid[p1x][p1y]->getTitleChar() == 'R') {
        return this->checkRookPath(p1x, p1y, p2x, p2y);
    }
    if (grid[p1x][p1y]->getTitleChar() == 'B') {
        return this->checkBishopPath(p1x, p1y, p2x, p2y);
    }
    if (grid[p1x][p1y]->getTitleChar() == 'Q') {
        return this->checkQueenPath(p1x, p1y, p2x, p2y);
    }
    if (grid[p1x][p1y]->getTitleChar() == 'P') {
        return this->checkPawnPath(p1x, p1y, p2x, p2y);
    }
    if (grid[p1x][p1y]->getTitleChar() == 'K') {
        //nullptr check already done??
        return this->checkTeamBlock(p1x, p1y, p2x, p2y);
    }
    if (grid[p1x][p1y]->getTitleChar() == 'k') {
        //nullptr check already done??
        return this->checkTeamBlock(p1x, p1y, p2x, p2y);
    }
    return true;
}
void Grid::printCaptured() {
    if (CapturedPieces.first.empty()) {
        std::cout << "\t" << "Captured White: None.\n";
    }
    else {
        std::cout << "\t" << "Captured White:\n";
        for (size_t i = 0; i < CapturedPieces.first.size(); ++i) {
            std::cout << "\t-" << CapturedPieces.first[i] << "\n";
        }
    }
    if (CapturedPieces.second.empty()) {
        std::cout << "\t" << "Captured Black: None.\n";
    }
    else {
        std::cout << "\t" << "Captured Black:\n";
        for (size_t i = 0; i < CapturedPieces.second.size(); ++i) {
            std::cout << "\t-" << CapturedPieces.second[i] << "\n";
        }
    }
}
Grid::~Grid() {
    deletePieces(WhitePieces);
    deletePieces(BlackPieces);
}
#endif