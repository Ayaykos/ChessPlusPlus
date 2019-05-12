#include <iostream>
#include <string>
#include "grid.h"
#include <vector>
using namespace std;

void inputMove(Grid &grid, string &position_1, string &position_2, char team);
bool checkMove(Grid &grid, string position_1, char team);
bool checkValidInput(string position);

int main() {

    Grid grid;
    grid.init();
    //grid.movePiece("A8", "A7");
    grid.print();
    string position_1, position_2;
    int turn = 0;
    bool gameEnded = false;
    while (!gameEnded) {
        cout << "\nPlayer 1's turn.\n";
        inputMove(grid, position_1, position_2, 'W');
        while (!grid.movePiece(position_1, position_2)) {
            cout << "\n";
            inputMove(grid, position_1, position_2, 'W');
        }
        grid.print();
        ++turn;
        cout << grid.printTurnDescription(turn);
        gameEnded = grid.gameEnded();
        if (gameEnded) continue;

        cout << "\nPlayer 2's turn.\n";
        inputMove(grid, position_1, position_2, 'B');
        while (!grid.movePiece(position_1, position_2)) {
            cout << "\n";
            inputMove(grid, position_1, position_2, 'B');
        }
        grid.print();
        ++turn;
        cout << grid.printTurnDescription(turn);
        gameEnded = grid.gameEnded();
    }
    
    return 0;
}

void inputMove(Grid &grid, string &position_1, string &position_2, char team) {
    cout << "Move which piece? ";
    cin >> position_1;
    while (!checkMove(grid, position_1, team)) {
        cout << "Move which piece? ";
        cin >> position_1;
    }
    cout << "Move " << grid[position_1]->getTitle() << " to? ";
    cin >> position_2;
}
bool checkMove(Grid &grid, string position_1, char team){
    while (!checkValidInput(position_1)) {
        cout << "Move which piece? ";
        cin >> position_1;
    }
    if (grid[position_1] == nullptr) {
        cout << "No piece exists at specified position.\n\n";
        return false;
    }
    if (grid[position_1]->getTeam() != team) {
        cout << "Choose a ";
        team == 'W' ? cout << "White" : cout << "Black";
        cout << " piece.\n\n";
        return false;
    }
    return true;
}
bool checkValidInput(string position) {
    //int letter = toupper(position_1[0]);
    if (toupper(position[0]) < 'A' ||
        toupper(position[0]) > 'H' || 
        position[1] < '1' || position[1] > '8') {
        cout << "Invalid input.\n\n";
        return false;
    }
    return true;
}