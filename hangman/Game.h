#ifndef GAME_H
#define GAME_H

#include "FileReader.h"
#include "State.h"
#include <vector>

class Game
{
private:
    const std::string assetDir{ASSETS_DIR};
    State* m_state;

public:
    std::string m_word{};
    std::vector<int> m_wordMap;

    Game();

    // state transition
    void changeState(State* state);

    // get state type
    State::StateType getStateType() const;

    // check if word was guessed already
    bool wordGuessed() const;

    // check if the game is over
    bool gameEnd() const;

    // make a guess -> easier to test
    void guess(std::string input);

    // print current state
    void print();
};

#endif
