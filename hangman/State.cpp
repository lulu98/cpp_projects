#include "State.h"
#include "Game.h"

// IntroState

IntroState::IntroState(Game* game)
    : m_fr{assetDir,fileName}
    , m_game{game}
{
}

State::StateType IntroState::getStateType() const
{
    return StateType::intro;
}

void IntroState::guess(std::string str)
{
    return;
}

void IntroState::print()
{
    m_fr.printFile();

    m_game->changeState(new PlayState(m_game));
}

// PlayState

PlayState::PlayState(Game* game)
    : m_currentDrawing{drawing0}
    , m_fr{assetDir,fileNames[static_cast<int>(m_currentDrawing)]}
    , m_game{game}
{
}

State::StateType PlayState::getStateType() const
{
    return StateType::play;
}

void PlayState::guess(char c)
{
    if(outOfDrawings())
        return;

    bool guessed{false};
    for(int i{0}; i < m_game->m_word.length(); ++i)
    {
        if(c == m_game->m_word[i])
        {
            m_game->m_wordMap[i] = 1;
            guessed = true;
        }
    }
    if(!guessed)
        m_currentDrawing = static_cast<Drawing>(static_cast<int>(m_currentDrawing) + 1);
    if(m_game->wordGuessed())
        m_game->changeState(new WinnerState(m_game));
    if(outOfDrawings())
        m_game->changeState(new LoserState(m_game));
    else
        m_fr.reopen(assetDir,fileNames[static_cast<int>(m_currentDrawing)]);
}

void PlayState::guess(std::string str)
{
    if(outOfDrawings() && str.length() == 0)
        return;

    if(str.length() == 1){
        guess(str[0]);
        return;
    }

    if(str == m_game->m_word)
        std::fill_n(m_game->m_wordMap.begin(),m_game->m_wordMap.size(),1);
    else
        m_currentDrawing = static_cast<Drawing>(static_cast<int>(m_currentDrawing) + 1);

    if(m_game->wordGuessed())
        m_game->changeState(new WinnerState(m_game));
    if(outOfDrawings())
        m_game->changeState(new LoserState(m_game));
    else 
        m_fr.reopen(assetDir,fileNames[static_cast<int>(m_currentDrawing)]);

    return;
}

void PlayState::print()
{
    m_fr.printFile();

    // print word
    for(int i{0}; i < m_game->m_word.length(); ++i)
    {
        if(m_game->m_wordMap[i] == 0) std::cout << '_';
        else std::cout << m_game->m_word.at(i);
        std::cout << ' ';
    }
    std::cout << '\n';
}

// WinnerState

WinnerState::WinnerState(Game* game)
    : m_fr{assetDir,fileName}
    , m_game{game}
{
}

State::StateType WinnerState::getStateType() const
{
    return StateType::winner;
}

void WinnerState::guess(std::string str)
{
    return;
}

void WinnerState::print()
{
    m_fr.printFile();
    std::cout << "The hidden word is: " << m_game->m_word << '\n';
}

// LoserState

LoserState::LoserState(Game* game)
    : m_fr{assetDir,fileName}
    , m_game{game}
{
}

State::StateType LoserState::getStateType() const
{
    return StateType::loser;
}

void LoserState::guess(std::string str)
{
    return;
}

void LoserState::print()
{
    m_fr.printFile();
    std::cout << "The hidden word is: " << m_game->m_word << '\n';
}

