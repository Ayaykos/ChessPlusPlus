#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <string>
#include <cmath>   
#include "conversions.h"


class Piece {
public:
    void updateStatus(int status_in) { status = status_in; }
    void updatePos(int x, int y) { xpos = x, ypos = y; }
    void updatePos(std::string xy) { 
        xpos = alphToNumX(xy), 
        ypos = alphToNumY(xy); 
    }
    std::string getTitle() { return title; }
    char getTitleChar() { 
        if (title == "Knight") {
            return 'k';
        }
        return title[0]; 
    }
    char getTeam() { return team; }
    std::string getFullTeam() {
        if (team == 'B') { return "Black"; }
        else { return "White"; }
    }
    int getXPos() { return xpos; }
    int getYPos() { return ypos; }
    std::string getAlphPos() {
        return char(xpos + 65) + std::to_string(8 - ypos);
    }
    int getStatus() { return status; }
    int getMoveCount() { return moveCount;  }
    void initID(int id_in) { id = id_in; }
    int getID() { return id;  }
    void print_details() {
        std::cout << "Title: " << title << "\nTeam: " << team << 
            "\nStatus: " << status << "\nx,y: " << xpos << ", " 
            << ypos << "\nAlph: " << getAlphPos() 
            << "\n" << "\n";
    }
    //check valid move
    virtual bool checkValidMove(int newxpos, int newypos) = 0;
    //execute move
    void move(int newxpos, int newypos) {
        xpos = newxpos;
        ypos = newypos;
        ++moveCount;
    }
    virtual ~Piece() {}
protected:
    std::string title;
    char team;
    int xpos, ypos;
    int status;
    int moveCount;
    int id;
};

class King : public Piece {
public:
    King(char team_in) {
        title = "King";
        team = team_in; 
        status = 1; 
        xpos = 0, ypos = 0, moveCount = 0, id = -1;
    }
    King(char team_in, std::string position_in) {
        title = "King";
        team = team_in;
        xpos = alphToNumX(position_in);
        ypos = alphToNumY(position_in);
        status = 1, moveCount = 0, id = -1;
    }
    bool checkValidMove(int newxpos, int newypos) override {
        if(abs(newxpos - xpos) > 1 || abs(newypos - ypos) > 1) {
            std::cout << "\tInvalid move: " << this->getFullTeam() 
                << " King from " << numToAlph(xpos, ypos) <<
                " to " << numToAlph(newxpos,newypos)
                << "\n";
            return false;
        }
        /*std::cout << "Valid move: " << this->getFullTeam()
            << " King from " << numToAlph(xpos, ypos) <<
            " to " << numToAlph(newxpos, newypos)
            << "\n";*/
        return true;
    }
};
class Queen : public Piece {
public:
    Queen(char team_in) {
        title = "Queen";
        team = team_in;
        status = 1;
        xpos = 0, ypos = 0, moveCount = 0, id = -1;
    }
    Queen(char team_in, std::string position_in) {
        title = "Queen";
        team = team_in;
        xpos = alphToNumX(position_in);
        ypos = alphToNumY(position_in);
        status = 1, moveCount = 0, id = -1;
    }
    bool checkValidMove(int newxpos, int newypos) override {
        if ((abs(newxpos - xpos) > 0 && abs(newypos - ypos) > 0) &&
            (abs(newxpos - xpos) != abs(newypos - ypos))) {
            std::cout << "\tInvalid move: " << this->getFullTeam()
                << " Queen from " << numToAlph(xpos, ypos) <<
                " to " << numToAlph(newxpos, newypos)
                << "\n";
            return false;
        }
        /*std::cout << "Valid move: " << this->getFullTeam()
            << " Queen from " << numToAlph(xpos, ypos) <<
            " to " << numToAlph(newxpos, newypos)
            << "\n";*/
        return true;
    }
};
class Rook : public Piece {
public:
    Rook(char team_in) {
        title = "Rook";
        team = team_in;
        status = 1, xpos = 0, ypos = 0, moveCount = 0, id = -1;
    }
    Rook(char team_in, std::string position_in) {
        title = "Rook";
        team = team_in;
        xpos = alphToNumX(position_in);
        ypos = alphToNumY(position_in);
        status = 1, moveCount = 0, id = -1;
    }
    bool checkValidMove(int newxpos, int newypos) override {

        if (abs(newxpos - xpos) > 0 && abs(newypos - ypos) > 0) {
            std::cout << "\tInvalid move: " << this->getFullTeam()
                << " Rook from " << numToAlph(xpos, ypos) <<
                " to " << numToAlph(newxpos, newypos)
                << "\n";
            return false;
        }
        
        /*std::cout << "Valid move: " << this->getFullTeam()
            << " Rook from " << numToAlph(xpos,ypos) << 
            " to " << numToAlph(newxpos, newypos)
            << "\n";*/

        return true;
    }
};
class Bishop : public Piece {
public:
    Bishop(char team_in) {
        title = "Bishop";
        team = team_in;
        status = 1, xpos = 0, ypos = 0, moveCount = 0, id = -1;
    }
    Bishop(char team_in, std::string position_in) {
        title = "Bishop";
        team = team_in;
        xpos = alphToNumX(position_in);
        ypos = alphToNumY(position_in);
        status = 1, moveCount = 0, id = -1;
    }
    bool checkValidMove(int newxpos, int newypos) override {
        if (abs(newxpos - xpos) != abs(newypos - ypos)) {
            std::cout << "\tInvalid move: " << this->getFullTeam()
                << " Bishop from " << numToAlph(xpos, ypos) <<
                " to " << numToAlph(newxpos, newypos)
                << "\n";
            return false;
        }
        /*std::cout << "Valid move: " << this->getFullTeam()
            << " Bishop from " << numToAlph(xpos, ypos) <<
            " to " << numToAlph(newxpos, newypos)
            << "\n";*/
        return true;
    }
};
class Knight : public Piece {
public:
    Knight(char team_in) {
        title = "Knight";
        team = team_in;
        status = 1, xpos = 0, ypos = 0, moveCount = 0, id = -1;
    }
    Knight(char team_in, std::string position_in) {
        title = "Knight";
        team = team_in;
        xpos = alphToNumX(position_in);
        ypos = alphToNumY(position_in);
        status = 1, moveCount = 0, id = -1;
    }
    bool checkValidMove(int newxpos, int newypos) override {

        if ((abs(newxpos - xpos) == 2 && abs(newypos - ypos) == 1) ||
            (abs(newxpos - xpos) == 1 && abs(newypos - ypos) == 2)) {
            /*std::cout << "Valid move: " << this->getFullTeam()
                << " Knight from " << numToAlph(xpos, ypos) <<
                " to " << numToAlph(newxpos, newypos)
                << "\n";*/
            return true;
        }
        std::cout << "\tInvalid move: " << this->getFullTeam()
            << " Knight from " << numToAlph(xpos, ypos) <<
            " to " << numToAlph(newxpos, newypos)
            << "\n";
        return false;
    }
};
class Pawn : public Piece {
public:
    Pawn(char team_in) {
        title = "Pawn";
        team = team_in;
        status = 1, xpos = 0, ypos = 0, moveCount = 0, id = -1;
    }
    Pawn(char team_in, std::string position_in) {
        title = "Pawn";
        team = team_in;
        xpos = alphToNumX(position_in);
        ypos = alphToNumY(position_in);
        status = 1, moveCount = 0, id = -1;
    }
    bool checkValidMove(int newxpos, int newypos) override {
        if ((team == 'W' && newypos > ypos) ||
            (team == 'B' && ypos > newypos)) {
            std::cout << "\tInvalid move: " << this->getFullTeam()
                << " Pawn from " << numToAlph(xpos, ypos) <<
                " to " << numToAlph(newxpos, newypos)
                << "\n";
            return false;
        }
        if (newxpos != xpos) {
            if ((abs(newxpos - xpos) > 1) || abs(newypos - ypos) > 1 || 
                (newypos == ypos)) {
                std::cout << "\tInvalid move: " << this->getFullTeam()
                    << " Pawn from " << numToAlph(xpos, ypos) <<
                    " to " << numToAlph(newxpos, newypos)
                    << "\n";
                return false;
            }
        }
        if ((moveCount == 0 && abs(newypos - ypos) > 2) || 
            (moveCount != 0 && abs(newypos - ypos) > 1)) {
            std::cout << "\tInvalid move: " << this->getFullTeam()
                << " Pawn from " << numToAlph(xpos, ypos) <<
                " to " << numToAlph(newxpos, newypos)
                << "\n";
            return false;
        }

        return true;
    }
};

std::ostream & operator<<(std::ostream & os, Piece* piece) {
    if (piece == nullptr) {
        return os << "null piece";
    }
    return os << piece->getFullTeam() << " " << piece->getTitle();
}
#endif