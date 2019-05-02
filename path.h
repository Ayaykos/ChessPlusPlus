#ifndef PATH_H
#define PATH_H
#include <iostream>
#include <string>
#include <vector>

//differentiate between blocks along the way and block at end
//any piece blocks along the way are issue
//piece at end depends on team or not

//test for end of path team/not team

bool checkRookPath(int p1x, int p1y, int p2x, int p2y,
    std::vector<std::vector<Piece*>> &grid) {
    //right
    if (abs(p2x - p1x) > 0 && p2x > p1x) {
        for (int i = p1x + 1; i <= p2x; ++i) {
            if (grid[i][p1y] != nullptr) {
                std::cout << "\tBlocked by: " <<
                    grid[i][p1y]->getFullTeam() << " " <<
                    grid[i][p1y]->getTitle() << " at " <<
                    numToAlph(i, p1y) << "\n";
                return false;
            }
        }
        return true;
    }
    //left
    else if (abs(p2x - p1x) > 0 && p1x > p2x) {
        for (int i = p1x - 1; i >= p2x; --i) {
            if (grid[i][p1y] != nullptr) {
                std::cout << "\tBlocked by: " <<
                    grid[i][p1y]->getFullTeam() << " " <<
                    grid[i][p1y]->getTitle() << " at " <<
                    numToAlph(i, p1y) << "\n";
                return false;
            }
        }
        return true;
    }
    //down
    else if (abs(p2y - p1y) > 0 && p2y > p1y) {
        for (int i = p1y + 1; i <= p2y; ++i) {
            if (grid[p1x][i] != nullptr) {
                std::cout << "\tBlocked by: " <<
                    grid[p1x][i]->getFullTeam() << " " <<
                    grid[p1x][i]->getTitle() << " at " <<
                    numToAlph(p1x, i) << "\n";
                return false;
            }
        }
        return true;
    }
    //up
    else {
        for (int i = p1y - 1; i >= p2y; --i) {
            if (grid[p1x][i] != nullptr) {
                std::cout << "\tBlocked by: " <<
                    grid[p1x][i]->getFullTeam() << " " <<
                    grid[p1x][i]->getTitle() << " at " <<
                    numToAlph(p1x, i) << "\n";
                return false;
            }
        }
        return true;
    }
    std::cout << "error in checkRootPath" << "\n";
    assert(false);
    return false;
}
bool checkBishopPath(int p1x, int p1y, int p2x, int p2y,
    std::vector<std::vector<Piece*>> &grid) {

    if ((abs(p2x - p1x) > 0 && p2x > p1x) &&
        (abs(p2y - p1y) > 0 && p2y > p1y)) {
        for (int i = 0; i < abs(p1x - p2x); ++i) {
            if (grid[p1x + i + 1][p1y + i + 1] != nullptr) {
                std::cout << "\tBlocked by: " <<
                    grid[p1x + i + 1][p1y + i + 1]->getFullTeam() << " " <<
                    grid[p1x + i + 1][p1y + i + 1]->getTitle() << " at " <<
                    numToAlph(p1x + i + 1, p1y + i + 1) << std::endl;
                return false;
            }
        }
        return true;
    }
    else if ((abs(p2x - p1x) > 0 && p2x > p1x) &&
        (abs(p2y - p1y) > 0 && p1y > p2y)) {
        for (int i = 0; i < abs(p1x - p2x); ++i) {
            if (grid[p1x + i + 1][p1y - i - 1] != nullptr) {
                std::cout << "\tBlocked by: " <<
                    grid[p1x + i + 1][p1y - i - 1]->getFullTeam() << " " <<
                    grid[p1x + i + 1][p1y - i - 1]->getTitle() << " at " <<
                    numToAlph(p1x + i + 1, p1y - i - 1) << std::endl;
                return false;
            }
        }
        return true;
    }
    else if ((abs(p2x - p1x) > 0 && p1x > p2x) &&
        (abs(p2y - p1y) > 0 && p2y > p1y)) {
        for (int i = 0; i < abs(p1x - p2x); ++i) {
            if (grid[p1x - i - 1][p1y + i + 1] != nullptr) {
                std::cout << "\tBlocked by: " <<
                    grid[p1x - i - 1][p1y + i + 1]->getFullTeam() << " " <<
                    grid[p1x - i - 1][p1y + i + 1]->getTitle() << " at " <<
                    numToAlph(p1x - i - 1, p1y + i + 1) << std::endl;
                return false;
            }
        }
        return true;
    }
    else {
        for (int i = 0; i < abs(p1x - p2x); ++i) {
            if (grid[p1x - i - 1][p1y - i - 1] != nullptr) {
                std::cout << "\tBlocked by: " <<
                    grid[p1x - i - 1][p1y - i - 1]->getFullTeam() << " " <<
                    grid[p1x - i - 1][p1y - i - 1]->getTitle() << " at " <<
                    numToAlph(p1x - i - 1, p1y - i - 1) << std::endl;
                return false;
            }
        }
        return true;
    }
    std::cout << "error in checkBishopPath" << "\n";
    assert(false);
    return false;
}
bool checkQueenPath(int p1x, int p1y, int p2x, int p2y,
    std::vector<std::vector<Piece*>> &grid) {
    if (abs(p2x - p1x) > 0 && abs(p2y - p1y) > 0) {
        return checkBishopPath(p1x, p1y, p2x, p2y, grid);
    }
    return checkRookPath(p1x, p1y, p2x, p2y, grid);
}
bool checkKingPath(int p1x, int p1y, int p2x, int p2y,
    std::vector<std::vector<Piece*>> &grid) {
    if (grid[p2x][p2y] != nullptr) {
        if (grid[p2x][p2y]->getTeam() == grid[p1x][p1y]->getTeam()) {
            std::cout << "\tBlocked by team member: " << 
                grid[p2x][p2y]->getFullTeam() << " " <<
                grid[p2x][p2y]->getTitle() << " at " <<
                numToAlph(p2x, p2y) << std::endl;
            return false;
        }
    }
    return true;
}
#endif