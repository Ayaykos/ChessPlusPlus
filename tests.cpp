#include <iostream>
#include <string>
#include "tests_basic_moves.h"
using namespace std;


int main() {

    //basic moves
    TestKing testking;
    testking.test();
    TestRook testrook;
    testrook.testsuccess();
    testrook.testfail();
    //test returning and staying still?
    TestBishop testbishop;
    testbishop.testsuccess();
    testbishop.testfail();
    TestQueen testqueen;
    testqueen.testsuccess();
    testqueen.testfail();
    TestKnight testknight;
    testknight.testsuccess();
    testknight.testfail();

    return 0;
}