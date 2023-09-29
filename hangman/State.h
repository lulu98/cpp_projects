#ifndef STATE_H
#define STATE_H

#include "FileReader.h"
#include <array>
#include <string>

class Game;
class State
{
protected:
    const std::string assetDir{ASSETS_DIR};

public:
    enum StateType
    {
        intro,
        play,
        winner,
        loser
    };

    virtual StateType getStateType() const = 0;
    virtual void guess(std::string str) = 0;
    virtual void print() = 0;
    virtual ~State() = default;
};

class IntroState : public State
{
private:
    const std::string fileName{"intro.txt"};
    Game* m_game;
    FileReader m_fr;

public:
    IntroState(Game* game);

    StateType getStateType() const override;

    void guess(std::string str) override;

    void print() override;
};

class PlayState : public State
{
private:
    enum Drawing
    {
        drawing0,
        drawing1,
        drawing2,
        drawing3,
        drawing4,
        drawing5,
        num_drawings
    };

    const std::array<std::string,num_drawings> fileNames{
        "hangman00.txt",
        "hangman01.txt",
        "hangman02.txt",
        "hangman03.txt",
        "hangman04.txt",
        "hangman05.txt"
    };
    Drawing m_currentDrawing{};
    Game* m_game;
    FileReader m_fr;

    bool outOfDrawings() const
    {
        return (m_currentDrawing == num_drawings);
    }

public:
    PlayState(Game* game);

    StateType getStateType() const override;

    void guess(char c);
    
    void guess(std::string str) override;
    
    void print() override;
};

class WinnerState : public State
{
private:
    const std::string fileName{"winner.txt"};
    Game* m_game;
    FileReader m_fr;

public:
    WinnerState(Game* game);

    StateType getStateType() const override;

    void guess(std::string str) override;

    void print() override;
};

class LoserState : public State
{
private:
    const std::string fileName{"loser.txt"};
    Game* m_game;
    FileReader m_fr;

public:
    LoserState(Game* game);

    StateType getStateType() const override;

    void guess(std::string str) override;

    void print() override;
};

#endif
