# ChessPlusPlus

Working on a Chess spinoff, exploring where I can take this. Will incorporate proper GUI and interactive interface.

- game.cpp  *//main driver*
  - game.h  *//Piece classes/subclasses*
  - grid.h  *//Grid class containing pieces*
  - helper.h  *//Helper functions for Grid's use of Pieces*
  - conversions.h  *//Numerical/alphabetical grid notation conversion functions*
  
- tests.cpp  *//test suite - currently only calling from here during testing (main driver empty)*
  - tests_basic_moves.h
  - tests_check_paths.h
  - tests_grid.h
  - tests_misc.h
```
g++ tests.cpp -o tests.exe
./tests.exe
```
