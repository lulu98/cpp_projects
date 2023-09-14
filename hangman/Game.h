#pragma once

#include <array>
#include <algorithm>
#include <iostream>
#include <string>
#include "FileReader.h"

class Game
{
private:
    enum GameState
    {
        intro,
        hangman00,
        hangman01,
        hangman02,
        hangman03,
        hangman04,
        hangman05,
        end,
        winner,
        loser,

        max_states
    };

    // use m_state as index
    const std::array<std::string,max_states> m_filenames{
        "intro.txt",
        "hangman00.txt",
        "hangman01.txt",
        "hangman02.txt",
        "hangman03.txt",
        "hangman04.txt",
        "hangman05.txt",
        "",
        "winner.txt",
        "loser.txt"
    };

    const std::string assetDir{ASSETS_DIR};
    GameState m_state{};
    std::string m_word{};
    int* m_wordMap{}; // if field is set, then character is guessed

public:
    Game();
    ~Game();

    // check if word was guessed already
    bool wordGuessed() const;

    // take a character guess
    void guess(char c);

    // take a string guess
    void guess(std::string str);

    // check if the game is over
    bool gameEnd() const;

    // print the intro screen
    void printIntroScreen();

    // print end screen
    void printEndScreen();

    friend std::ostream& operator<<(std::ostream& out, const Game& g);
};

