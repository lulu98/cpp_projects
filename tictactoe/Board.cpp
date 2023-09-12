#include "Board.h"
#include <cassert>

bool Board::isWon() const
{
    return (
        m_board[0] && m_board[3] && m_board[6] ||
        m_board[1] && m_board[4] && m_board[7] ||
        m_board[2] && m_board[5] && m_board[8] ||
        m_board[0] && m_board[1] && m_board[2] ||
        m_board[3] && m_board[4] && m_board[5] ||
        m_board[6] && m_board[7] && m_board[8] ||
        m_board[0] && m_board[4] && m_board[8] ||
        m_board[2] && m_board[4] && m_board[6]
    );
}

bool Board::check(int x, int y) const
{
    assert(x >= 0 && x < 3);
    assert(y >= 0 && y < 3);
    return m_board[x * 3 + y] == Board::filled;
}

void Board::move(int x, int y)
{
    assert(x >= 0 && x < 3);
    assert(y >= 0 && y < 3);
    m_board[x * 3 + y] = Board::filled;
}
