#include "Board.h"
#include <iomanip>
#include <iostream>

enum class PlayerType
{
    player1,
    player2,
    numPlayers
};

struct Point
{
    int x;
    int y;
};

void drawBoard(const Board& p1, const Board& p2)
{
    for(int row{0}; row < 3; ++row)
    {
        for(int col{0}; col < 3; ++col)
        {
            if(p1.check(row,col)) std::cout << 'x';
            else if(p2.check(row,col)) std::cout << 'o';
            else std::cout << '-';
            std::cout << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

Point getUserInput(PlayerType currentPlayer)
{
    std::cout << "Current Player: " << ((currentPlayer == PlayerType:: player1) ? "Player 1" : "Player 2") << '\n';
    Point p{};
    std::cout << "Enter row: ";
    std::cin >> p.x;
    std::cout << "Enter col: ";
    std::cin >> p.y;
    std::cout << '\n';
    return p;
}

int main()
{
    std::cout << "Welcome to TicTacToe!\n\n";
    Board player1{};
    Board player2{};
    PlayerType currentPlayer{PlayerType::player1};
    int count{0};
    while(true)
    {
        drawBoard(player1, player2);

        // check if game is over
        if(player1.isWon()){
            std::cout << "Player 1 has won. Congrats!\n";
            break;
        }else if(player2.isWon()){
            std::cout << "Player 2 has won. Congrats!\n";
            break;
        }else if(count >= 9){
            std::cout << "No player won. It's a draw!\n";
            break;
        }

        // get user input
        Point p{getUserInput(currentPlayer)};
        while(player1.check(p.x,p.y) || player2.check(p.x,p.y))
        {
            p = getUserInput(currentPlayer);
        }

        // make a move
        (currentPlayer == PlayerType::player1) ? player1.move(p.x,p.y) : player2.move(p.x,p.y);

        // progress game state
        currentPlayer = static_cast<PlayerType>((static_cast<int>(currentPlayer) + 1) % static_cast<int>(PlayerType::numPlayers));
        ++count;
    }

    std::cout << "Thanks for playing. See you next time!\n";
    return 0;
}
