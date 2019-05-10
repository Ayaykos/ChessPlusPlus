#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <sstream>
#include "tests_basic_moves.h"
#include "tests_check_paths.h"
#include "tests_misc.h"
#include "tests_grid.h"
#include "tests_checkmate.h"
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
        //TestRookPath trp;
        //trp.test();
        //trp.testOvertake();
        //TestBishopPath tbp;
        //tbp.test();
        //tbp.testOvertake();
        //TestKingPath tKp;
        //tKp.test();
        //tKp.testOvertake();
        //TestQueenPath tqp;
        //tqp.testOvertake();
        //tqp.test();
        //TestKnightPath tkp;
        //tkp.test();
        //TestPawnPath tpp;
        //tpp.test();
        //tpp.testOvertake();
        //tpp.testEP();
        //tpp.testEPbothpawns();
    }
};
class TestGrid {
public:
    void test() {
        GridTest gt;
        gt.testHistory();
        gt.testID();
    }
};
class TestCheckMate {
public:
    void test() {
        testCheckMate tcm;
        //tcm.testKnight();
        //tcm.testPawn();
        //tcm.testRook();
        //tcm.testRookBlock();
        //tcm.testBishopBlock();
        //tcm.testQueenRook();
        //tcm.testQueenBishop();
        //tcm.testQueenBishopBlock();
        tcm.testQueenRookBlock();
        
    }
};
class TestMisc {
public:
    void test() {
        General g;
        //g.KingMoveCount();
        //g.promoteInputTest();
        //g.movePieceTest();
        g.fileInputTest();
    }
};

int main() {
    //TestBasicMoves tbm;
    //tbm.test();
    //TestCheckPaths tcp;
    //tcp.test();
    //TestGrid tg;
    //tg.test();
    //TestCheckMate tcm;
    //tcm.test();
    TestMisc tm;
    tm.test();
    return 0;
}