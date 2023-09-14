#include <iostream>
#include "Game.h"

int main()
{
    Game g{};

    g.printIntroScreen();    
    while(!g.gameEnd())
    {
        std::cout << g << '\n'; 
        std::cout << "Enter a character or directly guess the word: ";
        std::string input{};
        std::cin >> input;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        g.guess(input);        
    }
    g.printEndScreen();

    return 0;
}
