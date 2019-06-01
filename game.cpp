#include <iostream>
#include <string>
#include "grid.h"
#include "gameinterface.h"
#include <vector>
#include <thread>
using namespace std;

bool asked = false;
string input;
bool runInterface = false;

void inputMove(Grid &grid, string &position_1, string &position_2, char team);
bool checkChosenPiece(Grid &grid, string &position_1, char team);
bool checkValidInput(Grid &grid, string position, bool &cancelled);
void printResult(Grid &grid, string p1_name, string p2_name);
void helpOptions(Grid &grid);
bool playerMove(Grid &grid, string other_name, bool &drawReached, char team);
void gameCycle(bool &play, string p1_name, string p2_name);
void backend();
void SFMLsetup();
void SFMLinterface();
class gameDraw {};
class cancelMove {};

int main() {

    std::string runInterfaceInput = "0";
    while (runInterfaceInput.size() > 1 || 
        (toupper(runInterfaceInput[0]) != 'Y' && toupper(runInterfaceInput[0]) != 'N')) {
        std::cout << "Include interface? Only functional on Windows (y/n): ";
        std::cin >> runInterfaceInput;
    }
    if (toupper(runInterfaceInput[0]) == 'Y') runInterface = true;


    std::thread SFMLthread(SFMLsetup);
    std::thread backendthread(backend);
    std::thread SFMLinterfacethread(SFMLinterface);

    backendthread.join();
    SFMLthread.join();
    SFMLinterfacethread.join();

    return 0;
}

void SFMLinterface() {
    if (runInterface) {
        Interface gameinterface;
        gameinterface.process();
    }
}
void SFMLsetup() {
    while (true) {

        //if user input requested
        if (asked) {
            std::cin >> input;

            //break data request
            asked = false;
        }
    }
}
void backend() {
    bool play = true;
    std::cout << "Welcome to ChessPlusPlus!\n\n";
    string p1_name, p2_name, garbage;

    //Player names input
    bool nameSuccess = false;
    while (!nameSuccess) {
        std::cout << "Player 1's name (White): ";
        getline(std::cin, p1_name);
        if (p1_name == "") {
            std::cout << "Name must be at least 1 character.\n";
            continue;
        }
        //Check if player names are different
        while (p2_name == "" || p1_name == p2_name){
            std::cout << "Player 2's name (Black): ";
            getline(std::cin, p2_name);
            //Check if player names are empty
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

    //Loop until player decides to end gameplay
    while (play) {
        std::cout << "\nEnter alphanumerical positions (\"A1\").\n";
        std::cout << "Type 'help' at anytime during gameplay for assistance.\n\n";
        std::cout << "ENTER to start game.";
        getline(std::cin,garbage);
        std::cout << "\n";
        gameCycle(play, p1_name,p2_name);
    }
}
//Full gameplay with repeated games until quit
void gameCycle(bool &play, string p1_name, string p2_name) {
    Grid grid;
    grid.init();
    int turn = 0;
    bool gameEnded = false, drawReached = false;
    grid.print();

    //Loop through moves until game end
    while (!gameEnded) {
        //Player 1's turn (White)
        std::cout << p1_name << "'s turn. (Turn " << turn + 1 << ")\n";

        //repeat playerMove() until move successful
        while (!playerMove(grid, p2_name, drawReached, 'W')) {}

        //End loop if draw
        if (drawReached) {
            gameEnded = true;
            continue;
        }

        //End loop of game if end reached
        gameEnded = grid.gameEnded();
        if (gameEnded) {
            printResult(grid, p1_name, p2_name);
            continue;
        }
        grid.print();

        ///////////////////////////////////////////////////////////////////////

        //Player 2's turn (Black)
        std::cout << "\n" << p2_name << "'s turn. (Turn " << turn + 1 << ")\n";

        //repeat playerMove() until move successful
        while (!playerMove(grid, p1_name, drawReached, 'B')) {}

        //End loop if draw
        if (drawReached) {
            gameEnded = true;
            continue;
        }
        //End loop of game if end reached
        gameEnded = grid.gameEnded();
        if (gameEnded) {
            printResult(grid, p1_name, p2_name);
            continue;
        }
        
        grid.print();
        ++turn;
    }

    //Game end menu 
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
        //Stop playing
        else {
            std::cout << "\nThanks for playing!\n";
            play = false;
        }
    }
}

//Full player move handler
bool playerMove(Grid &grid, string other_name, bool &drawReached, char team) {
    string position_1, position_2;
    try {
        inputMove(grid, position_1, position_2, team);
        while (!grid.movePiece(position_1, position_2)) {
            std::cout << "\n";
            inputMove(grid, position_1, position_2, team);
        }
    }
    //Catch draw game input, confirm with opposing player
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
    //Catch move cancel input
    catch (cancelMove) { return false; }
    return true;
}
//Player input move core handler
void inputMove(Grid &grid, string &position_1, string &position_2, char team) {
    bool cancelled = true;
    //Loop until full move uncancelled
    while (cancelled) {
        cancelled = false;

        //Choose first piece
        std::cout << "Move which piece? ";

        //Multithreaded call to user input
        asked = true;
        while (asked) {}
        position_1 = input;

        while (!checkChosenPiece(grid, position_1, team)) {
            std::cout << "Move which piece? ";

            //Multithreaded call to user input
            asked = true;
            while (asked) {}
            position_1 = input;

        }

        //Choose position to move piece to
        std::cout << "Move " << grid[position_1]->getTitle() << " to? ";

        //Multithreaded call to user input
        asked = true;
        while (asked) {}
        position_2 = input;

        while (!checkValidInput(grid, position_2, cancelled)) {
            //Break from loop if move successful and not cancelled
            if (cancelled == true) break;
            std::cout << "Move " << grid[position_1]->getTitle() << " to? ";

            //Multithreaded call to user input
            asked = true;
            while (asked) {}
            position_2 = input;


        }
    }
    std::cout << "\n";
}
//Check if chosen piece valid
bool checkChosenPiece(Grid &grid, string &position_1, char team){
    bool cancelled = false;
    //Check valid input
    while (!checkValidInput(grid, position_1, cancelled)) {
        std::cout << "Move which piece? ";

        //Multithreaded call to user input
        asked = true;
        while (asked) {}
        position_1 = input;
    }
    //Check if chosen exists on chosen position
    if (grid[position_1] == nullptr) {
        std::cout << "No piece exists at specified position.\n\n";
        return false;
    }
    //Check if chosen piece corresponds to player's team
    if (grid[position_1]->getTeam() != team) {
        std::cout << "Choose a ";
        team == 'W' ? std::cout << "White" : std::cout << "Black";
        std::cout << " piece.\n\n";
        return false;
    }
    return true;
}
//Help menu input handling
void helpOptions(Grid &grid) {
    std::string option = "0";
    while (option[0] < '1' || option[0] > '6') {
        std::cout << "\nOptions:\n";
        std::cout << "1: Cancel move (can also type cancel during gameplay)\n";
        std::cout << "2: Castle (currently not functional)\n"; //do
        std::cout << "3: Print move history\n";
        std::cout << "4: Print captured pieces\n5: Draw game\n";
        std::cout << "6: Return to game\n";
        std::cin >> option;
        if (option.size() > 1) option = '0';
    }
    std::cout << "\n";
    if (option == "1") throw cancelMove();
    //Castle implementation to be completed
    else if (option == "3") grid.printTurnHistory(0);
    else if (option == "4") {
        grid.printCaptured();
        std::cout << "\n";
    }
    else if (option == "5") throw gameDraw();
    //Else return normally
}
//Check valid input during gameplay
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
//Print game end result
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