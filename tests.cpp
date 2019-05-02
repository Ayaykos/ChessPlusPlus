#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <sstream>
#include "tests_basic_moves.h"
#include "tests_check_paths.h"
using namespace std;

class TestBasicMoves {
public:
    void test() {
        TestKingBasic testking;
        testking.test();
        TestRookBasic testrook;
        testrook.testsuccess();
        testrook.testfail();
        //test returning and staying still?
        TestBishopBasic testbishop;
        testbishop.testsuccess();
        testbishop.testfail();
        TestQueenBasic testqueen;
        testqueen.testsuccess();
        testqueen.testfail();
        TestKnightBasic testknight;
        testknight.testsuccess();
        testknight.testfail();
    }
};
class TestCheckPaths {
public:
    void test() {
        TestRookPath testrootpath;
        testrootpath.test();
    }
};
void asd() {
    std::cout << "asds" << std::endl;
}
int main() {
    //TestBasicMoves tbm;
    //tbm.test();
    TestCheckPaths tcp;
    tcp.test();
    ostringstream oss;
    //oss << asd();
    std::cout << oss.str();
    return 0;
}