#pragma once

#include <iostream>

class Board
{
public:
    enum FieldType
    {
        empty,
        filled
    };

protected:
    static constexpr int numberOfTiles{9};
    FieldType m_board[numberOfTiles]{empty}; // implement board as 1D array

public:
    Board() = default;

    // check if current player has won
    bool isWon() const;

    // check if current player has made a move
    bool check(int x, int y) const;

    // make a move
    void move(int x, int y);
};

