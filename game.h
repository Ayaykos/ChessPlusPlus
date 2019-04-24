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
    void print_details() {
        std::cout << "Title: " << title << "\nTeam: " << team << 
            "\nStatus: " << status << "\nx,y: " << xpos << ", " 
            << ypos << "\nAlph: " << getAlphPos() 
            << std::endl << std::endl;
    }
    virtual bool move(int newxpos, int newypos) = 0;
    void print() {
        std::cout << "x,y: " << xpos << " " << ypos << std::endl;
    }

    virtual ~Piece() {}
protected:
    std::string title;
    char team;
    int xpos, ypos;
    int status;
};

class King : public Piece {
public:
    King(char team_in) {
        title = "King";
        team = team_in; 
        status = 1; 
        xpos = 0; 
        ypos = 0;
    }
    King(char team_in, std::string position_in) {
        title = "King";
        team = team_in;
        status = 1;
        xpos = alphToNumX(position_in);
        ypos = alphToNumY(position_in);
    }
    bool move(int newxpos, int newypos) override {

        if(abs(newxpos - xpos) > 1 || abs(newypos - ypos) > 1) {
            std::cout << "Cannot move " << this->getFullTeam() 
                << " King from " << numToAlph(xpos, ypos) <<
                " to " << numToAlph(newxpos,newypos)
                << std::endl;
            return false;
        }
        std::cout << "Success in moving " << this->getFullTeam()
            << " King from " << numToAlph(xpos, ypos) <<
            " to " << numToAlph(newxpos, newypos)
            << std::endl;
        xpos = newxpos;
        ypos = newypos;
        return true;
    }

};
class Queen : public Piece {
public:
    Queen(char team_in) {
        title = "Queen";
        team = team_in;
        status = 1;
        xpos = 0;
        ypos = 0;
    }
    Queen(char team_in, std::string position_in) {
        title = "Queen";
        team = team_in;
        status = 1;
        xpos = alphToNumX(position_in);
        ypos = alphToNumY(position_in);
    }
    bool move(int newxpos, int newypos) override {
        if ((abs(newxpos - xpos) > 0 && abs(newypos - ypos) > 0) &&
            (abs(newxpos - xpos) != abs(newypos - ypos))) {
            std::cout << "Cannot move " << this->getFullTeam()
                << " Queen from " << numToAlph(xpos, ypos) <<
                " to " << numToAlph(newxpos, newypos)
                << std::endl;
            return false;
        }
        std::cout << "Success in moving " << this->getFullTeam()
            << " Queen from " << numToAlph(xpos, ypos) <<
            " to " << numToAlph(newxpos, newypos)
            << std::endl;
        xpos = newxpos;
        ypos = newypos;
        return true;
    }
};
class Rook : public Piece {
public:
    Rook(char team_in) {
        title = "Rook";
        team = team_in;
        status = 1;
        xpos = 0;
        ypos = 0;
    }
    Rook(char team_in, std::string position_in) {
        title = "Rook";
        team = team_in;
        status = 1;
        xpos = alphToNumX(position_in);
        ypos = alphToNumY(position_in);
    }
    bool move(int newxpos, int newypos) override {
        if (abs(newxpos - xpos) > 0 && abs(newypos - ypos) > 0) {
            std::cout << "Cannot move " << this->getFullTeam()
                << " Rook from " << numToAlph(xpos, ypos) <<
                " to " << numToAlph(newxpos, newypos)
                << std::endl;
            return false;
        }
        
        std::cout << "Success in moving " << this->getFullTeam()
            << " Rook from " << numToAlph(xpos,ypos) << 
            " to " << numToAlph(newxpos, newypos)
            << std::endl;
        xpos = newxpos;
        ypos = newypos;
        return true;
    }
};
class Bishop : public Piece {
public:
    Bishop(char team_in) {
        title = "Bishop";
        team = team_in;
        status = 1;
        xpos = 0;
        ypos = 0;
    }
    Bishop(char team_in, std::string position_in) {
        title = "Bishop";
        team = team_in;
        status = 1;
        xpos = alphToNumX(position_in);
        ypos = alphToNumY(position_in);
    }
    bool move(int newxpos, int newypos) override {
        if (abs(newxpos - xpos) != abs(newypos - ypos)) {
            std::cout << "Cannot move " << this->getFullTeam()
                << " Bishop from " << numToAlph(xpos, ypos) <<
                " to " << numToAlph(newxpos, newypos)
                << std::endl;
            return false;
        }
        std::cout << "Success in moving " << this->getFullTeam()
            << " Bishop from " << numToAlph(xpos, ypos) <<
            " to " << numToAlph(newxpos, newypos)
            << std::endl;
        xpos = newxpos;
        ypos = newypos;
        return true;
    }
};
class Knight : public Piece {
public:
    Knight(char team_in) {
        title = "Knight";
        team = team_in;
        status = 1;
        xpos = 0;
        ypos = 0;
    }
    Knight(char team_in, std::string position_in) {
        title = "Knight";
        team = team_in;
        status = 1;
        xpos = alphToNumX(position_in);
        ypos = alphToNumY(position_in);
    }
    bool move(int newxpos, int newypos) override {
        if ((abs(newxpos - xpos) == 2 && abs(newypos - ypos) == 1) ||
            (abs(newxpos - xpos) == 1 && abs(newypos - ypos) == 2)) {
            std::cout << "Success in moving " << this->getFullTeam()
                << " Knight from " << numToAlph(xpos, ypos) <<
                " to " << numToAlph(newxpos, newypos)
                << std::endl;
            xpos = newxpos;
            ypos = newypos;
            return true;
        }
        std::cout << "Cannot move " << this->getFullTeam()
            << " Knight from " << numToAlph(xpos, ypos) <<
            " to " << numToAlph(newxpos, newypos)
            << std::endl;
        return false;
    }
};
class Pawn : public Piece {
public:
    Pawn(char team_in) {
        title = "Pawn";
        team = team_in;
        status = 1;
        xpos = 0;
        ypos = 0;
    }
    Pawn(char team_in, std::string position_in) {
        title = "Pawn";
        team = team_in;
        status = 1;
        xpos = alphToNumX(position_in);
        ypos = alphToNumY(position_in);
    }
    bool move(int newxpos, int newypos) override {
        xpos = newxpos;
        ypos = newypos;
        return true;
    }
};
#endif