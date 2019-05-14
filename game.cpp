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
    std::cout << "Welcome to ChessPlusPlus!\n\n";
    string p1_name, p2_name, garbage;

    bool nameSuccess = false;
    while (!nameSuccess) {
        std::cout << "Player 1's name (White): ";
        getline(std::cin, p1_name);
        if (p1_name == "") {
            std::cout << "Name must be at least 1 character.\n";
            continue;
        }
        while (p2_name == "" || p1_name == p2_name){
            std::cout << "Player 2's name (Black): ";
            getline(std::cin, p2_name);
            if (p2_name == "") {
                std::cout << "Name must be at least 1 character.\n";
                continue;
            }
            if (p1_name == p2_name) {
                std::cout << "Names must be different.\n";
                continue;
            }
        }
        std::cout << "\n";
        nameSuccess = true;
    }
    while (play) {
        std::cout << "\nEnter alphanumerical positions (\"A1\").\n";
        std::cout << "Type 'help' at anytime during gameplay for assistance.\n\n";
        std::cout << "ENTER to start game.";
        getline(std::cin,garbage);
        std::cout << "\n";
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

    while (!gameEnded) {

        std::cout << p1_name << "'s turn. (Turn " << turn + 1 << ")\n";
        while (!playerMove(grid, p2_name, drawReached, 'W')) {}
        if (drawReached) {
            gameEnded = true;
            continue;
        }
        //++turn;
        gameEnded = grid.gameEnded();
        if (gameEnded) {
            printResult(grid, p1_name, p2_name);
            continue;
        }
        grid.print();

        /////////////////////////////////////////////////////////////

        std::cout << "\n" << p2_name << "'s turn. (Turn " << turn + 1 << ")\n";
        while (!playerMove(grid, p1_name, drawReached, 'B')) {}
        if (drawReached) {
            gameEnded = true;
            continue;
        }
        //++turn;
        gameEnded = grid.gameEnded();
        if (gameEnded) {
            printResult(grid, p1_name, p2_name);
            continue;
        }
        grid.print();
        ++turn;
    }
    string option = "0";
    while (option[0] != '3' && option[0] != '4') {
        while (option[0] < '1' || option[0] > '4') {
            std::cout << "\nMenu:\n";
            std::cout << "1: Print move history\n";
            std::cout << "2: Print captured pieces\n";
            std::cout << "3: Play again\n";
            std::cout << "4: Quit\n";
            std::cin >> option;
            if (option.size() > 1) option = "0";
            
        }
        if (option[0] == '1') {
            grid.printTurnHistory(0);
            option = "0";
        }
        else if (option[0] == '2') {
            grid.printCaptured();
            option = "0";
            std::cout << "\n";
        }
        else if (option[0] == '3') break;
        else {
            std::cout << "\nThanks for playing!\n";
            play = false;
        }
    }
}

bool playerMove(Grid &grid, string other_name, bool &drawReached, char team) {
    string position_1, position_2;
    try {
        inputMove(grid, position_1, position_2, team);
        while (!grid.movePiece(position_1, position_2)) {
            std::cout << "\n";
            inputMove(grid, position_1, position_2, team);
        }
    }
    catch (gameDraw) {
        char response;
        std::cout << other_name << ", confirm draw game?(y/n) ";
        std::cin >> response;
        if (toupper(response) == 'Y') {
            std::cout << "Game Draw!\n";
            drawReached = true;
            return true;
        }
        else {
            std::cout << "Oops! Game continues.\n\n";
            return false;
        }
    }
    catch (cancelMove) {
        return false;
    }
    return true;
}

void printResult(Grid &grid, string p1_name, string p2_name) {
    if (grid.getWinner() == 1) std::cout << "\nWhite King Checkmate. "
        << p2_name << " wins!\n";
    else if (grid.getWinner() == 2) std::cout << "\nBlack King Checkmate. "
        << p1_name << " wins!\n";
    else if (grid.getWinner() == 3) std::cout <<
        "\nWhite King Stalemate. Draw!\n";
    else if (grid.getWinner() == 4) std::cout <<
        "\nBlack King Stalemate. Draw!\n";
    grid.print();
}
void inputMove(Grid &grid, string &position_1, string &position_2, char team) {
    bool cancelled = true;
    while (cancelled) {
        cancelled = false;
        std::cout << "Move which piece? ";
        std::cin >> position_1;
        while (!checkMove(grid, position_1, team)) {
            std::cout << "Move which piece? ";
            std::cin >> position_1;
        }
        std::cout << "Move " << grid[position_1]->getTitle() << " to? ";
        std::cin >> position_2;

        while (!checkValidInput(grid, position_2, cancelled)) {
            if (cancelled == true) break;
            std::cout << "Move " << grid[position_1]->getTitle() << " to? ";
            std::cin >> position_2;
        }
    }
    std::cout << "\n";

}
bool checkMove(Grid &grid, string &position_1, char team){
    bool cancelled = false;
    while (!checkValidInput(grid, position_1, cancelled)) {
        std::cout << "Move which piece? ";
        std::cin >> position_1;
    }
    if (grid[position_1] == nullptr) {
        std::cout << "No piece exists at specified position.\n\n";
        return false;
    }
    if (grid[position_1]->getTeam() != team) {
        std::cout << "Choose a ";
        team == 'W' ? std::cout << "White" : std::cout << "Black";
        std::cout << " piece.\n\n";
        return false;
    }
    return true;
}
void helpOptions(Grid &grid) {
    std::string option = "0";
    while (option[0] < '1' || option[0] > '5') {
        std::cout << "\nOptions:\n";
        std::cout << "1: Cancel move (can also type cancel during gameplay)\n";
        std::cout << "2: Print move history\n";
        std::cout << "3: Print captured pieces\n4: Draw game\n";
        std::cout << "5: Return to game\n";
        std::cin >> option;
        if (option.size() > 1) option = '0';
    }
    std::cout << "\n";
    if (option == "1") throw cancelMove();
    else if (option == "2") grid.printTurnHistory(0);
    else if (option == "3") {
        grid.printCaptured();
        std::cout << "\n";
    }
    else if (option == "4") throw gameDraw();
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
        std::cout << "Invalid input.\n\n";
        return false;
    }
    if (toupper(position[0]) < 'A' ||
        toupper(position[0]) > 'H' || 
        position[1] < '1' || position[1] > '8') {
        std::cout << "Invalid input.\n\n";
        return false;
    }
    return true;
}
