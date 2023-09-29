# Project: Tic Tac Toe

## Concepts

- class
- struct
- enum
- ternary operator

## Description

TicTacToe is a very simple game. You have two players that try to complete the
3x3 game. If one of the players gets three in a row, then he has won. In case
the board is full and no player has won yet, it's a draw.

## Build Instructions

```bash
mkdir build
cd build
cmake -DBUILD_EXEC=ON ..
cmake --build ..
./tictactoe
```

## Test Instructions

```bash
mkdir test
cd test
cmake -DUNIT_TEST=ON ..
cmake --build ..
./runTests
```

## TODO

- maybe not have a separate board per player
- have better text alignment
- more thorough testing

