#include "Game.h"

Game::Game()
    : m_state{intro}
{
    FileReader fr{assetDir,"words.txt"};
    m_word = fr.getRandomLine();
    m_wordMap = new int[m_word.length()]{};
}

Game::~Game()
{
    delete[] m_wordMap;
}

bool Game::wordGuessed() const
{
    bool guessed{true};
    for(int i{0}; i < m_word.length(); ++i)
        if(m_wordMap[i] == 0) guessed = false;
    return guessed;
}

void Game::guess(char c)
{
    if(m_state >= end) // don't allow guesses if already in finished state
        return;

    bool guessed{false};
    for(int i{0}; i < m_word.length(); ++i)
    {
        if(c == m_word[i])
        {
            m_wordMap[i] = 1;
            guessed = true;
        }
    }
    if(!guessed) // if no letter was guessed we have to progress state
        m_state = static_cast<GameState>(static_cast<int>(m_state) + 1);
    if(wordGuessed()) // word guessed -> winner
        m_state = winner;
    if(m_state == end) // end state reached, but word not guessed -> loser
        m_state = loser;
}

void Game::guess(std::string str)
{
    if(m_state >= end || str.length() == 0) // don't allow guesses if already in finished state
        return;

    if(str.length() == 1){
        guess(str[0]);
        return;
    }

    if(str == m_word)
        std::fill_n(m_wordMap,m_word.length(),1);
    else
        m_state = static_cast<GameState>(static_cast<int>(m_state) + 1);

    if(wordGuessed()) // word guessed -> winner
        m_state = winner;
    if(m_state == end) // end state reached, but word not guessed -> loser
        m_state = loser;
}

bool Game::gameEnd() const
{
    return m_state >= end;
}

void Game::printIntroScreen()
{
    if(m_state != intro)
        return;

    std::cout << *this << '\n';

    m_state = static_cast<GameState>(static_cast<int>(m_state) + 1);
}

void Game::printEndScreen()
{
    if(m_state < end)
        return;

    std::cout << *this << '\n';
}

std::ostream& operator<<(std::ostream& out, const Game& g)
{
    FileReader fr{g.assetDir,g.m_filenames[g.m_state]};
    fr.printFile();

    if(g.m_state == g.intro || g.m_state >= g.end)
        return out;

    // print word
    for(int i{0}; i < g.m_word.length(); ++i)
    {
        if(g.m_wordMap[i] == 0) std::cout << '_';
        else std::cout << g.m_word.at(i);
        std::cout << ' ';
    }
    std::cout << '\n';

    return out;
}

