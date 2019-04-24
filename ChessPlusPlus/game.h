#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>

/*
class Piece {
public:
    Piece(char team_in) :
        team(team_in), status(1), xpos(0), ypos(0) {}
    void updateStatus(int status_in) { status = status_in; }
    void updatePos(int x, int y) { xpos = x, ypos = y; }
    char getTeam() { return team; }
    int getXPos() { return xpos; }
    int getYPos() { return ypos; }
    std::string getAlphPos() 
    { return char(xpos + 65) + std::to_string(8 - ypos); }
    int getStatus() { return status; }
    void print_details() {
        std::cout << "Team: " << team << "\nStatus: " << status <<
            "\nx,y: " << xpos << ", " << ypos <<
            "\nAlph: " << getAlphPos() << std::endl << std::endl;
    }
    virtual void move(std::string position_in) {
        std::cout << "move" << std::endl;
    }
    virtual ~Piece() {}
private:
    char team;
    int xpos, ypos;
    int status;
};
class King : public Piece {
    //King(int x) : xpos(x) {}
    void move(std::string position_in) {
        std::cout << "move king" << std::endl;
    }
};
*/
#endif