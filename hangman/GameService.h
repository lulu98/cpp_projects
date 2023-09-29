#ifndef GAME_SERVICE_H
#define GAME_SERVICE_H

#include "Game.h"

class GameService
{
private:
    Game* m_game;

public:
    GameService();

    bool gameEnd() const;
    void print();
    void makeGuess();
};

#endif
