#ifndef PATH_H
#define PATH_H
#include <iostream>
#include <string>
#include <vector>

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

#endif