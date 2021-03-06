# ChessPlusPlus
<p align="left">
  <img src="https://raw.githubusercontent.com/Ayaykos/ChessPlusPlus/master/icon.ico" width="150" title="icon">
</p>
Working on a Chess spinoff, exploring where I can take this. Using SFML for GUI and interactive interface.

Core Chess game nearly complete, currently working on finishing: 
- castling
- checking for possible elimation of threat during checkmate
- draw technicality - impossible checkmate

## Setup:
Currently have no simple way to circumvent setting up SFML.
To avoid compiler errors, in game.cpp, comment out:
* //#include "gameinterface.h"
* in SFMLinterface(): //Interface gameinterface();
```
g++ -pthread game.cpp -o game.exe
./game.exe
```
- game.cpp  *//main driver*
  - game.h  *//Piece classes/subclasses*
  - grid.h  *//Grid class containing pieces*
  - helper.h  *//Helper functions for Grid's use of Pieces*
  - gameinterface.h  *//Interface class using SFML*
  - conversions.h  *//Numerical/alphabetical grid notation conversion functions*
  
- tests.cpp  *//test suite*
  - tests_basic_moves.h
  - tests_check_paths.h
  - tests_checkmate.h
  - tests_grid.h
  - tests_misc.h
___
  Gridprint naming convention:

    
   |     |A  |B  |C  |D  |E  |F  |G  |H  ||
   |:-:  |:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
   |**8**|R. |k. |B. |Q. |K. |B. |k. |R. |`Black`|
   |**7**|P. |P. |P. |P. |P. |P. |P. |P. ||
   |**6**|   |   |   |   |   |   |   |   ||
   |**5**|   |   |   |   |   |   |   |   ||
   |**4**|   |   |   |   |   |   |   |   ||
   |**3**|   |   |   |   |   |   |   |   ||
   |**2**|P  |P  |P  |P  |P  |P  |P  |P  ||
   |**1**|R  |k  |B  |Q  |K  |B  |k  |R  |`White`|

 
   IDs (only important for development):
 
   |     |A  |B  |C  |D  |E  |F  |G  |H  ||
   |:-:  |:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
   |**8**|18 |22 |20 |17 |16 |21 |23 |19 |`Black`|
   |**7**|24 |25 |26 |27 |28 |29 |30 |31 ||
   |**6**|   |   |   |   |   |   |   |   ||
   |**5**|   |   |   |   |   |   |   |   ||
   |**4**|   |   |   |   |   |   |   |   ||
   |**3**|   |   |   |   |   |   |   |   ||
   |**2**|8  |9  |10 |11 |12 |13 |14 |15 ||
   |**1**|2  |6  |4  |1  |0  |5  |7  |3  |`White`|
