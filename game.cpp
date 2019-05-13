#include <iostream>
#include <string>
#include "grid.h"
#include <vector>
using namespace std;

void inputMove(Grid &grid, string &position_1, string &position_2, char team);
bool checkMove(Grid &grid, string &position_1, char team);
bool checkValidInput(Grid &grid, string position, bool &cancelled);
void printResult(Grid &grid, string p1_name, string p2_name);
void helpOptions(Grid &grid);
bool playerMove(Grid &grid, string other_name, bool &drawReached, char team);
class gameDraw {};
class cancelMove {};

int main() {

    Grid grid;
    grid.init();
    string p1_name, p2_name;
    int turn = 0;
    bool gameEnded = false, drawReached = false;
    
    cout << "Welcome to ChessPlusPlus!\n";
    cout << "Type 'help' at anytime for assistance.\n\n";
    cout << "Player 1's name (White): ";
    cin >> p1_name;
    cout << "Player 2's name (Black): ";
    cin >> p2_name;
    cout << "\n";
    grid.print();
    //bool drawFail = false;

    while (!gameEnded) {

        cout << p1_name << "'s turn.\n";
        while(!playerMove(grid, p2_name, drawReached, 'W')){}
        if (drawReached) {
            gameEnded = true;
            continue;
        }
        ++turn;
        gameEnded = grid.gameEnded();
        if (gameEnded) {
            printResult(grid, p1_name, p2_name);
            continue;
        }
        grid.print();

        /////////////////////////////////////////////////////////////
        
        cout << "\n" << p2_name << "'s turn.\n";
        while (!playerMove(grid, p1_name, drawReached, 'B')) {}    
        if (drawReached) {
            gameEnded = true;
            continue;
        }
        ++turn;
        gameEnded = grid.gameEnded();
        if (gameEnded) {
            printResult(grid, p1_name, p2_name);
            continue;
        }
        grid.print();
    }

    
    return 0;
}

bool playerMove(Grid &grid, string other_name, bool &drawReached, char team) {
    string position_1, position_2;
    try {
        inputMove(grid, position_1, position_2, team);
        while (!grid.movePiece(position_1, position_2)) {
            cout << "\n";
            inputMove(grid, position_1, position_2, team);
        }
    }
    catch (gameDraw) {
        char response;
        cout << other_name << ", confirm draw game?(y/n) ";
        cin >> response;
        if (toupper(response) == 'Y') {
            cout << "Game Draw!\n";
            drawReached = true;
            return true;
        }
        else {
            cout << "Oops! Game continues.\n\n";
            return false;
        }
    }
    catch (cancelMove) {
        return false;
    }
    return true;
}

void printResult(Grid &grid, string p1_name, string p2_name) {
    if (grid.getWinner() == 1) cout << "\nWhite King Checkmate. "
        << p2_name << " wins!\n";
    else if (grid.getWinner() == 2) cout << "\nBlack King Checkmate. "
        << p1_name << " wins!\n";
    else if (grid.getWinner() == 3) cout <<
        "\nWhite King Stalemate. Draw!\n";
    else if (grid.getWinner() == 4) cout <<
        "\nBlack King Stalemate. Draw!\n";
    grid.print();
}
void inputMove(Grid &grid, string &position_1, string &position_2, char team) {
    bool cancelled = true;
    while (cancelled) {
        cancelled = false;
        cout << "Move which piece? ";
        cin >> position_1;
        while (!checkMove(grid, position_1, team)) {
            cout << "Move which piece? ";
            cin >> position_1;
        }
        cout << "Move " << grid[position_1]->getTitle() << " to? ";
        cin >> position_2;

        while (!checkValidInput(grid, position_2, cancelled)) {
            if (cancelled == true) break;
            cout << "Move " << grid[position_1]->getTitle() << " to? ";
            cin >> position_2;
        }
        
    }

}
bool checkMove(Grid &grid, string &position_1, char team){
    bool cancelled = false;
    while (!checkValidInput(grid, position_1, cancelled)) {
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
void helpOptions(Grid &grid) {
    int option = 0;
    while (option < 1 || option > 5) {
        cout << "\nOptions:\n";
        cout << "1: Cancel move (can also type cancel anytime)\n";
        cout << "2: Print move history\n";
        cout << "3: Print captured pieces\n4: Draw game\n";
        cout << "5: Return to game\n";
        cin >> option;
    }
    if (option == 1) throw cancelMove();
    else if (option == 2) grid.printTurnHistory(0);
    else if (option == 3) {
        grid.printCaptured();
        cout << "\n";
    }
    else if (option == 4) throw gameDraw();
}
bool checkValidInput(Grid &grid, string position, bool &cancelled) {
    string temp = position;
    for (auto & i : temp) i = toupper(i);
    if (temp == "HELP") {
        helpOptions(grid);
        return false;
    }
    if (temp == "CANCEL") {
        cancelled = true;
        return false;
    }
    if (toupper(position[0]) < 'A' ||
        toupper(position[0]) > 'H' || 
        position[1] < '1' || position[1] > '8') {
        cout << "Invalid input.\n\n";
        return false;
    }
    return true;
}
