#ifndef GRID_H
#define GRID_H
#include <iostream>
#include <fstream>
#include <sstream>
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
    int getMoveCount();
    void basicTakeOver(int p2x, int p2y);
    void updateHistory();
    int indexHistoryID(int moveNum, int x, int y);
    std::string idToStr(int value);
    void printMove(int moveNum);
    void printTurnHistory(int startMove);
    bool checkTeamBlock(int p1x, int p1y, int p2x, int p2y);
    bool checkRookPath(int p1x, int p1y, int p2x, int p2y);
    bool checkBishopPath(int p1x, int p1y, int p2x, int p2y);
    bool checkQueenPath(int p1x, int p1y, int p2x, int p2y);
    bool checkPawnPath(int p1x, int p1y, int p2x, int p2y);
    bool checkPath(int p1x, int p1y, int p2x, int p2y);
    void pawnPromote(int p1x, int p1y, int p2x, int p2y);
    void check();
    bool checkMate();
    bool gameEnded();
    int getWinner();
    void validMovePrint(int p1x, int p1y, int p2x, int p2y);
    void invalidMovePrint(int p1x, int p1y, int p2x, int p2y);
    void printCaptured();
    std::string printMoveDescription(int moveNum);
    //Functions only for testing
    void init(std::string fileName);
    void movePieceTest(std::string position1, std::string position2);
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
    int moveCount;
    std::string whiteKingPos, blackKingPos;
    bool whiteKingCheck, blackKingCheck;
    bool endReached;
    int winner;
};

//Lookup operator using Grid instance
Piece* Grid::operator[](std::string lookup) {
    int x = alphToNumX(lookup);
    int y = alphToNumY(lookup);
    return grid[x][y];
}
//Initialize vectors of references to Black/White Piece instances
//Initializes Pieces to have default inital positions at start of game (Move 0)
void Grid::initPieces() {
    fillPieces(WhitePieces, 'W');
    fillPieces(BlackPieces, 'B');
}
//Initialize grid (2D vector of references to Piece instances) values to nullptr
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
//Fill 2D grid vector with references to Black/White pieces instances
//in their correct default positions at start of game (Move 0)
void Grid::fill() {
    //Fill with White pieces at respective positions
    for (size_t i = 0; i < WhitePieces.size(); ++i) {
        for (size_t j = 0; j < WhitePieces[i].size(); ++j) {
            grid[WhitePieces[i][j]->getXPos()][WhitePieces[i][j]->getYPos()] =
                WhitePieces[i][j];
        }
    }
    //Fill with Black pieces at respective positions
    for (size_t i = 0; i < BlackPieces.size(); ++i) {
        for (size_t j = 0; j < BlackPieces[i].size(); ++j) {
            grid[BlackPieces[i][j]->getXPos()][BlackPieces[i][j]->getYPos()] =
                BlackPieces[i][j];
        }
    }
}
//Cumulative initialization of Grid class
//initializing pieces, grid, default values, etc 
void Grid::init() {
    this->initPieces();
    this->initGrid();
    this->fill();
    moveCount = 0;
    this->updateHistory();
    moveDescriptionHistory.push_back("Starting Position\n");
    whiteKingPos = "E1", blackKingPos = "E8";
    whiteKingCheck = false, blackKingCheck = false, endReached = false;
    winner = 0;
}
//Cumulative initialization of Grid class through input file with custom positions
void Grid::init(std::string fileName) {
    fillPieces(fileName, WhitePieces, 'W');
    fillPieces(fileName,BlackPieces, 'B');      
    whiteKingPos = char(fileName[11]);
    whiteKingPos += char(fileName[12]);
    blackKingPos = char(fileName[13]);
    blackKingPos += char(fileName[14]);
    this->initGrid();
    this->fill();
    moveCount = 0;
    this->updateHistory();
    moveDescriptionHistory.push_back("Starting Position\n");
    whiteKingCheck = false, blackKingCheck = false, endReached = false;
    winner = 0;
    if (!this->checkMate()) {
        this->check();
    }
}
//Print grid vector with newest update of Pieces
void Grid::print() {
    std::cout << "  ";
    for (size_t i = 0; i < grid.size(); ++i) {
        std::cout << "__" << char(i + 65) << "_";
    }
    std::cout << "\n";
    for (size_t i = 0; i < grid.size(); ++i) {
        std::cout << 8 - i << " ";
        for (size_t j = 0; j < grid.size(); ++j) {
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
}
//Move piece from position1 to position2
//Return true if successful, false otherwise
//Handles updates to grid and other elements if successful
bool Grid::movePiece(std::string position1, std::string position2) {
    int x = alphToNumX(position1);
    int y = alphToNumY(position1);
    int newx = alphToNumX(position2);
    int newy = alphToNumY(position2);

    //If King of respective team in check, check if king is being moved out
    if (whiteKingCheck) {
        if (grid[x][y]->getTeam() == 'W' && 
            grid[x][y]->getTitleChar() != 'K') {
            std::cout << "\tMust move King - in Check.\n";
            return false;
        }
    }
    if (blackKingCheck) {
        if (grid[x][y]->getTeam() == 'B' &&
            grid[x][y]->getTitleChar() != 'K') {
            std::cout << "\tMust move King - in Check.\n";
            return false;
        }
    }

    //Check if move is valid
    if (grid[x][y]->checkValidMove(newx, newy) == true) {
        //Check if path allows move
        if (this->checkPath(x, y, newx, newy) == true) {
            std::ostringstream oss;
            oss << grid[x][y] << " moved from " << alphaNumUpper(position1) <<
                " to " << alphaNumUpper(position2) << "\n";
            std::cout << oss.str() << "\n";
            if (grid[x][y]->getTitleChar() == 'K') {
                grid[x][y]->getTeam() == 'W' ?
                    whiteKingPos = position2 : blackKingPos = position2;
            }
            moveDescriptionHistory.push_back(oss.str());
            grid[x][y]->move(newx, newy);
            updateGrid(x, y, newx, newy);
            updateHistory();
            ++moveCount;
            //Check if new move caused Check/Checkmate
            if (!this->checkMate()) {
                this->check();
            }
            else {
            }
            return true;
        }
        return false;
    }
    return false;
}
//Move any piece to any specified position without checking for validity move
//Only for testing
void Grid::movePieceTest(std::string position1, std::string position2) {
    int p1x = alphToNumX(position1);
    int p1y = alphToNumY(position1);
    int p2x = alphToNumX(position2);
    int p2y = alphToNumY(position2);
    grid[p2x][p2y] = grid[p1x][p1y];
    grid[p1x][p1y] = nullptr;
    if (checkHelper(grid, whiteKingPos, 'W')) whiteKingCheck = true;
    else {
        if (whiteKingCheck) {
            whiteKingCheck = false;
        }
    }
    if (checkHelper(grid, blackKingPos, 'B')) blackKingCheck = true;
    else {
        if (blackKingCheck) {
            blackKingCheck = false;
        }
    }
}
//Updates grid upon successful move
void Grid::updateGrid(int p1x, int p1y, int p2x, int p2y) {
    //En Passant
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
    //Pawn promotion
    if (grid[p1x][p1y]->getTitle() == "Pawn" && 
        ((grid[p1x][p1y]->getTeam() == 'B' && p2y == 7) || 
            (grid[p1x][p1y]->getTeam() == 'W' && p2y == 0))) {
        grid[p1x][p1y] = nullptr;
    }
    //Regular
    else {
        grid[p2x][p2y] = grid[p1x][p1y];
        grid[p1x][p1y] = nullptr;
    }

}
//Restores Grid instance to default
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
//Returns number of moves occured so far in game
int Grid::getMoveCount() {
    return moveCount;
}
//Removes piece at specified position, only for testing
void Grid::removePiece(std::string position) {
    grid[alphToNumX(position)][alphToNumY(position)] = nullptr;
}
//Removes group of pieces by team and title, only for testing
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
//Print valid move confirmation output
void Grid::validMovePrint(int p1x, int p1y, int p2x, int p2y) {
    std::cout << "Valid move: " << grid[p1x][p1y] << " from " << 
        numToAlph(p1x, p1y) << " to " << numToAlph(p2x, p2y) << "\n";
}
//Print Invalid move confirmation output
void Grid::invalidMovePrint(int p1x, int p1y, int p2x, int p2y) {
    std::cout << "\tInvalid move: " << grid[p1x][p1y] << " from " <<
        numToAlph(p1x, p1y) << " to " << numToAlph(p2x, p2y) << "\n";
}
//Updates Black/White CapturedPieces vector of Pieces 
//after successful simple overtake
void Grid::basicTakeOver(int p2x, int p2y) {
    grid[p2x][p2y]->getTeam() == 'W' ?
        CapturedPieces.first.push_back(grid[p2x][p2y]) :
        CapturedPieces.second.push_back(grid[p2x][p2y]);
}
//Add grid positioning of current turn to moveHistory vector
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
//Return ID of piece at specified location of specified move number
int Grid::indexHistoryID(int moveNum, int x, int y) {
    assert(int(moveHistory.size()) >= moveNum + 1);
    return moveHistory[moveNum][(8 * y) + x];
}
//Converts Piece ID to standard printed string form
std::string Grid::idToStr(int value) {
    //String/ID convention:
    //White pieces: K/0, Q/1, R/2, R/3, B/4, B/5, k/6, k/7
                  //P/8, P/9, P/10, P/11, P/12, P/13, P/14, P/15
    //Black pieces: K./16, Q./17, R./18, R./19, B./20, B./21, k./22, k./23
                  //P./24, P./25, P./26, P./27, P./28, P./29, P./30, P./31
    std::string converted = "";
    int tempVal = value;
    if (value > 15) tempVal = value - 16;
    if (tempVal == 0) converted += "K";
    else if (tempVal == 1) converted += "Q";
    else if (tempVal == 2 || tempVal == 3) converted += "R";
    else if (tempVal == 4 || tempVal == 5) converted += "B";
    else if (tempVal == 6 || tempVal == 7) converted += "k";
    else converted += "P";

    if (value > 15) converted += '.';
    else converted += "_";
    return converted;
}
//Print positioning of grid at specified move number
void Grid::printMove(int moveNum) {
    int val;
    std::cout << "Move " << moveNum << ": "
        << moveDescriptionHistory[moveNum] << "  ";
    for (size_t i = 0; i < grid.size(); ++i) {
        std::cout << "__" << char(i + 65) << "_";
    }
    std::cout << "\n";
    for (size_t i = 0; i < grid.size(); ++i) {
        std::cout << 8 - i << " ";
        for (size_t j = 0; j < grid.size(); ++j) {
            val = indexHistoryID(moveNum, j, i);
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
//Print all moves starting from specified start move until last move
void Grid::printTurnHistory(int startMove) {
    for (int i = startMove; i <= moveCount; ++i) {
        this->printMove(i);
    }
}

//Path Functions

//Check if team member present at desired move position
bool Grid::checkTeamBlock(int p1x, int p1y, int p2x, int p2y) {
    //If piece exists at desired move position
    if (grid[p2x][p2y] != nullptr) {
        //If piece is team member, move blocked
        if (grid[p2x][p2y]->getTeam() == grid[p1x][p1y]->getTeam()) {
            std::cout << "\tBlocked by team member: " << grid[p2x][p2y] <<
                " at " << numToAlph(p2x, p2y) << std::endl;
            return false;
        }
        //Else, successful basic piece capture
        else {
            std::cout << grid[p1x][p1y] << " overtook " <<
                grid[p2x][p2y] << " at " << numToAlph(p2x, p2y) << std::endl;
            basicTakeOver(p2x, p2y);
            return true;
        }
    }
    return true;
}
//Check for collisions on path of Rook
bool Grid::checkRookPath(int p1x, int p1y, int p2x, int p2y) {
    //Moving Right
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
    //Moving Left
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
    //Moving Down
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
    //Moving Up
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
//Check for collisions along path of Bishop
bool Grid::checkBishopPath(int p1x, int p1y, int p2x, int p2y) {

    //Moving Down, Right
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
    //Moving Up, Right
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
    //Moving Down, Left
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
    //Moving Up, Left
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
//Check for collisions along path of Queen
bool Grid::checkQueenPath(int p1x, int p1y, int p2x, int p2y) {
    //If moving along bishop path
    if (abs(p2x - p1x) > 0 && abs(p2y - p1y) > 0) {
        return this->checkBishopPath(p1x, p1y, p2x, p2y);
    }
    //If moving along rook path
    return this->checkRookPath(p1x, p1y, p2x, p2y);
}
//Check for collisions along path of Pawn, En Passant
bool Grid::checkPawnPath(int p1x, int p1y, int p2x, int p2y) {
    //give option to do en passant?

    //Moving diagonally
    if (p2x != p1x) {
        //Chosen move position is empty, enter enpassant possibility
        if (grid[p2x][p2y] == nullptr) {
            //Position 1 below/above chose position has a piece
            if (grid[p2x][p1y] != nullptr) {
                //2nd piece is enemy
                if (grid[p2x][p1y]->getTeam() != grid[p1x][p1y]->getTeam()) {
                    //2nd piece has moved more than once + check both pawns
                    if (grid[p2x][p1y]->getTitle() != "Pawn") {
                        std::cout << "\tInvalid move: " << grid[p1x][p1y]->getFullTeam()
                            << " Pawn from " << numToAlph(p1x, p1y) <<
                            " to " << numToAlph(p2x, p2y)
                            << "\n\t//En Passant invalid - Enemy piece not a pawn.\n";
                        return false;
                    }
                    if (grid[p2x][p1y]->getMoveCount() > 1) {
                        //Unsuccessful enpassant, wasn't opposites 1st move
                        std::cout << "\tInvalid move: " << grid[p1x][p1y]->getFullTeam()
                            << " Pawn from " << numToAlph(p1x, p1y) <<
                            " to " << numToAlph(p2x, p2y)
                            << "\n\t//En Passant invalid - Enemy pawn moved more than once.\n";
                        return false;
                    }
                    if (indexHistoryID(moveCount - 1, p2x, p1y) 
                        == grid[p2x][p1y]->getID()) {
                        //Turn was not immediate move
                        std::cout << "\tInvalid move: " << grid[p1x][p1y]->getFullTeam()
                            << " Pawn from " << numToAlph(p1x, p1y) <<
                            " to " << numToAlph(p2x, p2y)
                            << "\n\t//En Passant invalid - Overtake must be immediate.\n";
                        return false;
                    }
                    //Else successful en passant
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
            //Invalid move, impossible en passant, return false
            return false;
        }
        //Regular possible overtake
        //If 2nd piece isn't enemy
        else if (grid[p2x][p2y]->getTeam() == grid[p1x][p1y]->getTeam()) {
            //Blocked return false
            std::cout << "\tBlocked by team member: " << grid[p2x][p2y] <<
                " at " << numToAlph(p2x, p2y) << std::endl;
            return false;
        }
        //2nd piece is enemy, successful regular overtake
        else {
            /*std::cout << "Valid move: " << grid[p1x][p1y]->getFullTeam()
                << " Pawn from " << numToAlph(p1x, p1y) <<
                " to " << numToAlph(p2x, p2y)
                << "\n";*/
            std::cout << grid[p1x][p1y] << " overtook " <<
                grid[p2x][p2y] << " at " << numToAlph(p2x, p2y) << std::endl;
            basicTakeOver(p2x, p2y);
            return true;
        }
    }
    //Moving straight onto nonempty position
    if (grid[p2x][p2y] != nullptr) {
        if (grid[p2x][p2y]->getTeam() == grid[p1x][p1y]->getTeam()) {
            std::cout << "\tBlocked by team member: " << grid[p2x][p2y] <<
                " at " << numToAlph(p2x, p2y) << std::endl;
            return false;
        }
        else {
            std::cout << "\tInvalid move: " << grid[p1x][p1y]->getFullTeam()
                << " Pawn from " << numToAlph(p1x, p1y) <<
                " to " << numToAlph(p2x, p2y)
                << "\n";
            return false;
        }
    }
    /*
    std::string output = "Valid move: " + grid[p1x][p1y]->getFullTeam()
        + " Pawn from " + numToAlph(p1x, p1y) +
        " to " + numToAlph(p2x, p2y) + "\n";
    std::cout << output;*/

    //Moving straight into empty position
    return true;
}
//Promote pawn after having reached opposite end
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
//Cumulative path checking function using piece specific functions
bool Grid::checkPath(int p1x, int p1y, int p2x, int p2y) {
    if (p1x == p2x && p1y == p2y) {
        std::cout << "\tUnmoved piece.\n";
        return false;
    }
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
        if (this->checkTeamBlock(p1x, p1y, p2x, p2y)) {
            if (grid[p1x][p1y]->getTeam() == 'W' && whiteKingCheck) {
                if (checkHelper(grid, numToAlph(p2x, p2y), 'W')) {
                    std::cout << "King must be moved out of check position.\n";
                    return false;
                }
            }
            if (grid[p1x][p1y]->getTeam() == 'B' && blackKingCheck) {
                if (checkHelper(grid, numToAlph(p2x, p2y), 'B')) {
                    std::cout << "King must be moved out of check position.\n";
                    return false;
                }
            }
            return true;
        }
        return false;
    }
    if (grid[p1x][p1y]->getTitleChar() == 'k') {
        //nullptr check already done??
        return this->checkTeamBlock(p1x, p1y, p2x, p2y);
    }
    return true;
}
//Check if either King in Check
void Grid::check() {
    //both kings can be in Check

    if (checkHelper(grid,whiteKingPos,'W')) {
        whiteKingCheck = true;
        std::cout << grid[alphToNumX(whiteKingPos)][alphToNumY(whiteKingPos)] 
            << " in Check at " << whiteKingPos << "\n";
    }
    else {
        if (whiteKingCheck) {
            whiteKingCheck = false;
        }
    }
    if (checkHelper(grid, blackKingPos, 'B')) {
        blackKingCheck = true;
        std::cout << grid[alphToNumX(blackKingPos)][alphToNumY(blackKingPos)]
            << " in Check at " << blackKingPos << "\n";
    }
    else {
        if (blackKingCheck) {
            blackKingCheck = false;
        }
    }
}
//Check if either King Checkmated
bool Grid::checkMate() {
    if (checkKingCheckMate(grid, whiteKingPos, 'W')) {
        endReached = true;
        this->check();
        if (whiteKingCheck) {
            //std::cout << "White King Checkmate.";
            winner = 1;
        }
        else {
            winner = 3;
            //std::cout << "White King Stalemate. Draw!\n";
        }
        return true;
    }
    if (checkKingCheckMate(grid, blackKingPos, 'B')) {
        endReached = true;
        this->check();
        if (blackKingCheck) {
            //std::cout << "Black King Checkmate.";
            winner = 2;
        }
        else {
            winner = 4;
        } //std::cout << "Black King Stalemate. Draw!\n";
        return true;
    }
    return false;
}
//Print captured pieces of both teams
void Grid::printCaptured() {
    if (CapturedPieces.first.empty()) {
        std::cout << "Captured by Black: None.\n";
    }
    else {
        std::cout << "Captured by Black:\n";
        for (size_t i = 0; i < CapturedPieces.first.size(); ++i) {
            std::cout << "\t" << CapturedPieces.first[i] << "\n";
        }
    }
    if (CapturedPieces.second.empty()) {
        std::cout << "Captured by White: None.\n";
    }
    else {
        std::cout << "Captured by White:\n";
        for (size_t i = 0; i < CapturedPieces.second.size(); ++i) {
            std::cout << "\t" << CapturedPieces.second[i] << "\n";
        }
    }
}
//Return true if game ended
bool Grid::gameEnded() { return endReached; }
//Return int responding to result of game (respective winner/draws)
int Grid::getWinner() { return winner;  }
//Print description of move at specified move number in game history
std::string Grid::printMoveDescription(int moveNum) {
    return moveDescriptionHistory[moveNum];
}
//Grid class destructor
Grid::~Grid() {
    deletePieces(WhitePieces);
    deletePieces(BlackPieces);
    deletePromotedPieces(PromotedPieces);
}
#endif