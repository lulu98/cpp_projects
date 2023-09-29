#include <iostream>
#include "GameService.h"

int main()
{
    GameService g{};
    g.print();
    while(!g.gameEnd())
    {
        g.print();
        g.makeGuess();
    }
    g.print();

    return 0;
}
