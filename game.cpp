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
void mainCycle(bool &play, string p1_name, string p2_name);
class gameDraw {};
class cancelMove {};

int main() {

    bool play = true;
    cout << "Welcome to ChessPlusPlus!\n\n";
    string p1_name, p2_name;
    
    cout << "Player 1's name (White): ";
    getline(cin, p1_name);
    cout << "Player 2's name (Black): ";
    getline(cin, p2_name);
    while (p2_name == p1_name) {
        cout << "Names must be different.\n";
        cout << "Player 1's name (White): ";
        getline(cin, p1_name);
        cout << "Player 2's name (Black): ";
        getline(cin, p2_name);
    }
    cout << "\n";

    while (play) {
        cout << "Game started! Enter alphanumerical positions (\"A1\").\n";
        cout << "Type 'help' at anytime for assistance.\n\n";
        mainCycle(play, p1_name,p2_name);
    }

    return 0;
}
void mainCycle(bool &play, string p1_name, string p2_name) {
    Grid grid;
    grid.init();
    int turn = 0;
    bool gameEnded = false, drawReached = false;
    grid.print();
    //bool drawFail = false;

    while (!gameEnded) {

        cout << p1_name << "'s turn. (Turn " << turn + 1 << ")\n";
        while (!playerMove(grid, p2_name, drawReached, 'W')) {}
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

        cout << "\n" << p2_name << "'s turn. (Turn " << turn + 1 << ")\n";
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
        //++turn;
    }
    int option = 0;
    while (option != 3 && option != 4) {
        while (option < 1 || option > 4) {
            cout << "\nMenu:\n";
            cout << "1: Print move history\n";
            cout << "2: Print captured pieces\n";
            cout << "3: Play again\n";
            cout << "4: Quit\n";
            cin >> option;
        }
        if (option == 1) {
            grid.printTurnHistory(0);
            option = 0;
        }
        else if (option == 2) {
            grid.printCaptured();
            option = 0;
            cout << "\n";
        }
        else if (option == 3) break;
        else {
            cout << "\nThanks for playing!\n";
            play = false;
        }
    }
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
    cout << "\n";

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
        cout << "1: Cancel move (can also type cancel during gameplay)\n";
        cout << "2: Print move history\n";
        cout << "3: Print captured pieces\n4: Draw game\n";
        cout << "5: Return to game\n";
        cin >> option;
    }
    cout << "\n";
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
    if (position.size() != 2) {
        cout << "Invalid input.\n\n";
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
