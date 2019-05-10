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
    bool movePiece(std::string position1, std::string position2);
    void updateGrid(int p1x, int p1y, int p2x, int p2y);
    void restoreGrid();
    int getTurnCount();
    void basicTakeOver(int p2x, int p2y);
    void updateHistory();
    int indexHistoryID(int turn, int x, int y);
    std::string idToStr(int value);
    void printTurn(int turn);
    void printTurnHistory(int startTurn);
    bool checkTeamBlock(int p1x, int p1y, int p2x, int p2y);
    bool checkRookPath(int p1x, int p1y, int p2x, int p2y);
    bool checkBishopPath(int p1x, int p1y, int p2x, int p2y);
    bool checkQueenPath(int p1x, int p1y, int p2x, int p2y);
    bool checkPawnPath(int p1x, int p1y, int p2x, int p2y);
    bool checkPath(int p1x, int p1y, int p2x, int p2y);
    void pawnPromote(int p1x, int p1y, int p2x, int p2y);
    bool check(std::string kingPosition, char kingTeam);
    void validMovePrint(int p1x, int p1y, int p2x, int p2y);
    void invalidMovePrint(int p1x, int p1y, int p2x, int p2y);
    void printCaptured();
    //functions only for testing
    void removePiece(std::string position);
    void removePiecesGroup(std::string team, std::string title);
    ~Grid();

private:
    std::vector<std::vector<Piece*>> grid;
    std::vector<std::vector<Piece*>> WhitePieces;
    std::vector<std::vector<Piece*>> BlackPieces;
    std::pair<std::vector<Piece*>, 
        std::vector<Piece*>>CapturedPieces;
    std::pair<std::vector<Piece*>,
        std::vector<Piece*>> PromotedPieces;
    std::vector<std::vector<int>> moveHistory;
    std::vector<std::string> moveDescriptionHistory;
    int turnCount;
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
    turnCount = 0;
    this->updateHistory();
    moveDescriptionHistory.push_back("Starting Position\n");
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

bool Grid::movePiece(std::string position1, std::string position2) {
    
    int x = alphToNumX(position1);
    int y = alphToNumY(position1);
    int newx = alphToNumX(position2);
    int newy = alphToNumY(position2);

    if (grid[x][y]->checkValidMove(newx, newy) == true) {
        //checkPath NEEDS TO BE DONE BEFORE ->MOVE CHANGES XPOS & YPOS

        if (this->checkPath(x, y, newx, newy) == true) {
            std::ostringstream oss;
            oss << grid[x][y] << " moved from " << numToAlph(x, y) <<
                " to " << numToAlph(newx, newy) << "\n";
            std::cout << oss.str();
            moveDescriptionHistory.push_back(oss.str());
            grid[x][y]->move(newx, newy);
            updateGrid(x, y, newx, newy);
            updateHistory();
            ++turnCount;

            return true;
        }
        return false;
    }
    return false;
}
void Grid::updateGrid(int p1x, int p1y, int p2x, int p2y) {
    //en passant
    if (grid[p2x][p1y] != nullptr) {
        if (grid[p2x][p1y]->getTitle() == "Pawn" &&
            grid[p1x][p1y]->getTitle() == "Pawn" &&
            grid[p2x][p2y] == nullptr && 
            grid[p2x][p1y]->getTeam() != grid[p1x][p1y]->getTeam()) {
            grid[p2x][p2y] = grid[p1x][p1y];
            grid[p1x][p1y] = nullptr;
            grid[p2x][p1y] = nullptr;
        }
    }
    if (grid[p1x][p1y]->getTitle() == "Pawn" && 
        ((grid[p1x][p1y]->getTeam() == 'B' && p2y == 7) || 
            (grid[p1x][p1y]->getTeam() == 'W' && p2y == 0))) {
        std::cout << "CHECK UPDATE GRID TO MAKE SURE" << std::endl;
        grid[p1x][p1y] = nullptr;
    }
    else {
        grid[p2x][p2y] = grid[p1x][p1y];
        grid[p1x][p1y] = nullptr;
    }

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
int Grid::getTurnCount() {
    return turnCount;
}
//function only for testing
void Grid::removePiece(std::string position) {
    grid[alphToNumX(position)][alphToNumY(position)] = nullptr;
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
void Grid::validMovePrint(int p1x, int p1y, int p2x, int p2y) {
    std::cout << "Valid move: " << grid[p1x][p1y] << " from " << 
        numToAlph(p1x, p1y) << " to " << numToAlph(p2x, p2y) << "\n";
}
void Grid::invalidMovePrint(int p1x, int p1y, int p2x, int p2y) {
    std::cout << "Invalid move: " << grid[p1x][p1y] << " from " <<
        numToAlph(p1x, p1y) << " to " << numToAlph(p2x, p2y) << "\n";
}
void Grid::basicTakeOver(int p2x, int p2y) {
    grid[p2x][p2y]->getTeam() == 'W' ?
        CapturedPieces.first.push_back(grid[p2x][p2y]) :
        CapturedPieces.second.push_back(grid[p2x][p2y]);
}
void Grid::updateHistory() {
    std::vector<int> newturn;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (grid[j][i] != nullptr) {
                newturn.push_back(grid[j][i]->getID());
            }
            else newturn.push_back(-1);
        }
    }
    moveHistory.push_back(newturn);
}
int Grid::indexHistoryID(int turn, int x, int y) {
    assert(int(moveHistory.size()) >= turn + 1);
    return moveHistory[turn][(8 * y) + x];
}
std::string Grid::idToStr(int value) {
    std::string converted = "";
    int tempVal = value;
    if (value > 15) tempVal = value - 15;
    if (tempVal == 0) converted += "K";
    else if (tempVal == 1) converted += "Q";
    else if (tempVal == 2 || tempVal == 3) converted += "R";
    else if (tempVal == 4 || tempVal == 5) converted += "B";
    else if (tempVal == 6 || tempVal == 7) converted += "k";
    else converted += "P";

    if (value > 15) converted += '.';
    else converted += "_";
    return converted;
    //std::cout << "correct: " << grid[x][y] << "\n";
    //std::cout << "answer: " << moveHistory[turn][(8 * y) + x] << "\n";
    //if (value;
}
void Grid::printTurn(int turn) {

    int val;
    std::cout << "Turn " << turn << ": " 
        << moveDescriptionHistory[turn] << "  ";
    for (size_t i = 0; i < grid.size(); ++i) {
        std::cout << "__" << char(i + 65) << "_";
    }
    std::cout << "\n";
    for (size_t i = 0; i < grid.size(); ++i) {
        std::cout << 8 - i << " ";
        for (size_t j = 0; j < grid.size(); ++j) {
            //std::cout << "|__";
            val = indexHistoryID(turn, j, i);
            if (val != -1) {
                std::cout << "|_"<< idToStr(val);
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
}
void Grid::printTurnHistory(int startTurn) {
    for (int i = startTurn; i <= turnCount; ++i) {
        this->printTurn(i);
    }
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
        //chosen move position is empty, enter enpassant possibility
        if (grid[p2x][p2y] == nullptr) {
            //position 1 below/above chose position has a piece
            if (grid[p2x][p1y] != nullptr) {
                //2nd piece is enemy
                if (grid[p2x][p1y]->getTeam() != grid[p1x][p1y]->getTeam()) {
                    //2nd piece has moved more than once + check both pawns
                    if (grid[p2x][p1y]->getTitle() != "Pawn") {
                        std::cout << "Invalid move: " << grid[p1x][p1y]->getFullTeam()
                            << " Pawn from " << numToAlph(p1x, p1y) <<
                            " to " << numToAlph(p2x, p2y)
                            << "\n\t//En Passant invalid - Enemy piece not a pawn.\n";
                        return false;
                    }
                    if (grid[p2x][p1y]->getMoveCount() > 1) {
                        //unsuccessful enpassant, wasn't opposites 1st move
                        std::cout << "Invalid move: " << grid[p1x][p1y]->getFullTeam()
                            << " Pawn from " << numToAlph(p1x, p1y) <<
                            " to " << numToAlph(p2x, p2y)
                            << "\n\t//En Passant invalid - Enemy pawn moved more than once.\n";
                        return false;
                    }
                    if (indexHistoryID(turnCount - 1, p2x, p1y) 
                        == grid[p2x][p1y]->getID()) {
                        //turn was not immediate move
                        std::cout << "Invalid move: " << grid[p1x][p1y]->getFullTeam()
                            << " Pawn from " << numToAlph(p1x, p1y) <<
                            " to " << numToAlph(p2x, p2y)
                            << "\n\t//En Passant invalid - Overtake must be immediate.\n";
                        return false;
                    }
                    //include second if for seeing if this turn was immediate move
                    //else successful en passant
                    validMovePrint(p1x, p2x, p1y, p2y);
                    std::cout << "En passant: " << grid[p1x][p1y] << " overtook " <<
                        grid[p2x][p1y] << " at " << numToAlph(p2x, p1y) << std::endl;
                    basicTakeOver(p2x, p1y);
                    return true;
                }
                //2nd piece is team member, blocked path
                invalidMovePrint(p1x, p1y, p2x, p2y);
                return false;
            }
            invalidMovePrint(p1x, p1y, p2x, p2y);
            //invalid move, impossible en passant, return false
            return false;
        }
        //regular possible overtake
        //if 2nd piece isn't enemy
        else if (grid[p2x][p2y]->getTeam() == grid[p1x][p1y]->getTeam()) {
            //blocked return false
            std::cout << "\tBlocked by team member: " << grid[p2x][p2y] <<
                " at " << numToAlph(p2x, p2y) << std::endl;
            return false;
        }
        //2nd piece is enemy, successful regular overtake
        else {
            std::cout << "Valid move: " << grid[p1x][p1y]->getFullTeam()
                << " Pawn from " << numToAlph(p1x, p1y) <<
                " to " << numToAlph(p2x, p2y)
                << "\n";
            std::cout << grid[p1x][p1y] << " overtook " <<
                grid[p2x][p2y] << " at " << numToAlph(p2x, p2y) << std::endl;
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
    std::string output = "Valid move: " + grid[p1x][p1y]->getFullTeam()
        + " Pawn from " + numToAlph(p1x, p1y) +
        " to " + numToAlph(p2x, p2y) + "\n";
    std::cout << output;
    return true;
}
void Grid::pawnPromote(int p1x, int p1y, int p2x, int p2y) {
    std::cout << "Pawn promotion on " << numToAlph(p2x, p2y);
    
    std::string promoted = promoteInput();
    std::cout << "Promoted " << grid[p1x][p1y] << " to " << promoted << "\n";
    int pairVal = -1;
    grid[p1x][p1y]->getTeam() == 'W' ? pairVal = 0 : pairVal = 1;
    grid[p2x][p2y] = nullptr;
    if (promoted == "Queen") {
        Piece *queen = 
            new Queen(grid[p1x][p1y]->getTeam(), numToAlph(p2x,p2y));
        pairVal == 0 ? PromotedPieces.first.push_back(queen) :
            PromotedPieces.second.push_back(queen);
        grid[p2x][p2y] = queen;
    }
    else if (promoted == "Rook") {
        Piece *rook =
            new Rook(grid[p1x][p1y]->getTeam(), numToAlph(p2x, p2y));
        pairVal == 0 ? PromotedPieces.first.push_back(rook) :
            PromotedPieces.second.push_back(rook);
        grid[p2x][p2y] = rook;
    }    
    else if (promoted == "Bishop") {
        Piece *bishop =
            new Bishop(grid[p1x][p1y]->getTeam(), numToAlph(p2x, p2y));
        pairVal == 0 ? PromotedPieces.first.push_back(bishop) :
            PromotedPieces.second.push_back(bishop);
        grid[p2x][p2y] = bishop;
    }
    else if (promoted == "Knight") {
        Piece *knight =
            new Knight(grid[p1x][p1y]->getTeam(), numToAlph(p2x, p2y));
        pairVal == 0 ? PromotedPieces.first.push_back(knight) :
            PromotedPieces.second.push_back(knight);
        grid[p2x][p2y] = knight;
    }
    else {
        std::cout << "Error in pawnPromote." << std::endl;
        assert(false);
    }
}
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
        if (this->checkPawnPath(p1x, p1y, p2x, p2y) == true) {
            if ((grid[p1x][p1y]->getTeam() == 'W' && p2y == 0) ||
                (grid[p1x][p1y]->getTeam() == 'B' && p2y == 7)) {
                this->pawnPromote(p1x, p1y, p2x, p2y);
                return true;
            }
            return true;
        }
        return false;
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
bool Grid::check(std::string kingPosition, char kingTeam) {
    /*
    if (checkHorse(grid, kingPosition, kingTeam) || 
        checkPawn(grid, kingPosition, kingTeam) || 
        checkRook(grid, kingPosition, kingTeam, 'R') ||
        checkBishop(grid, kingPosition, kingTeam, 'B') ||
        checkQueen(grid, kingPosition, kingTeam)) {
        std::cout << grid[alphToNumX(kingPosition)][alphToNumY(kingPosition)] <<
            " in check at " << kingPosition << "\n";
        return true;
    }*/
    if (checkQueen(grid, kingPosition, kingTeam)) {
        std::cout << grid[alphToNumX(kingPosition)][alphToNumY(kingPosition)] <<
            " in check at " << kingPosition << "\n";
        return true;
    }
    return false;
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
    deletePromotedPieces(PromotedPieces);
}
#endif