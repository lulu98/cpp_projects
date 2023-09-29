#include "GameService.h"

GameService::GameService()
{
    m_game = new Game();
}

bool GameService::gameEnd() const
{
    return m_game->gameEnd();
}

void GameService::print()
{
    m_game->print();
}

void GameService::makeGuess()
{
    std::cout << "Enter a character or directly guess the word: ";
    std::string input{};
    std::cin >> input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    m_game->guess(input);
}

