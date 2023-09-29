#include <algorithm>
#include <iostream>
#include <string>
#include "Game.h"

Game::Game()
{
    FileReader fr{assetDir,"words.txt"};
    m_word = fr.getRandomLine();
    m_wordMap.insert(m_wordMap.end(), m_word.length(), 0);
    m_state = new IntroState(this);
}

void Game::changeState(State* state)
{
    m_state = state;
}

State::StateType Game::getStateType() const
{
    return m_state->getStateType();
}

bool Game::wordGuessed() const
{
    return std::all_of(m_wordMap.begin(), m_wordMap.end(), [](int x){ return x == 1; } );
}

bool Game::gameEnd() const
{
    State::StateType currentStateType{m_state->getStateType()};
    return (currentStateType == State::StateType::winner || currentStateType == State::StateType::loser);
}

void Game::guess(std::string input)
{
    m_state->guess(input);
}

void Game::print()
{
    m_state->print();
}

