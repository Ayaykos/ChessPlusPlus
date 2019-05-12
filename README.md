# ChessPlusPlus

Working on a Chess spinoff, exploring where I can take this. Will incorporate proper GUI and interactive interface.

```
g++ tests.cpp -o tests.exe
./tests.exe
```
- game.cpp  *//main driver*
  - game.h  *//Piece classes/subclasses*
  - grid.h  *//Grid class containing pieces*
  - helper.h  *//Helper functions for Grid's use of Pieces*
  - conversions.h  *//Numerical/alphabetical grid notation conversion functions*
  
- tests.cpp  *//test suite*
  - tests_basic_moves.h
  - tests_check_paths.h
  - tests_checkmate.h
  - tests_grid.h
  - tests_misc.h
