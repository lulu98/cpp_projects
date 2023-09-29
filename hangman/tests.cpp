#include "FileReader.h"
#include "Game.h"
#include "State.h"
#include <string>
#include <gtest/gtest.h>

/*
 * FileReader tests
 */

// check whether getLineCount() works as expected
TEST(FileReaderTest, LineCount)
{
    const std::string assetDir{ASSETS_DIR};
    FileReader fr{assetDir, "words.txt"};
    ASSERT_EQ(100,fr.getLineCount());
}

// checks whether getLine() works as expected
TEST(FileReaderTest, GetLine)
{
    const std::string assetDir{ASSETS_DIR};
    FileReader fr{assetDir, "words.txt"};
    ASSERT_STREQ("art",fr.getLine(0).c_str());
    ASSERT_STREQ("affair",fr.getLine(fr.getLineCount() - 1).c_str());
    ASSERT_STREQ("climate",fr.getLine(9).c_str());
}

// checks whether getPath() and getFileName() works as expected
TEST(FileReaderTest, GetPathAndFileName)
{
    const std::string assetDir{ASSETS_DIR};
    FileReader fr{assetDir, "words.txt"};
    ASSERT_STREQ((assetDir + "words.txt").c_str(), fr.getPath().c_str());
    ASSERT_STREQ("words.txt", fr.getFileName().c_str());
}

// checks whether reopen() works as expected
TEST(FileReaderTest, Reopen)
{
    const std::string assetDir{ASSETS_DIR};
    FileReader fr{assetDir, "words.txt"};
    ASSERT_STREQ((assetDir + "words.txt").c_str(), fr.getPath().c_str());
    fr.reopen(assetDir, "intro.txt");
    ASSERT_STREQ((assetDir + "intro.txt").c_str(), fr.getPath().c_str());
}

/*
 * State machine tests
 */
TEST(StateMachineTest, TestIntroState)
{
    Game g{};
    ASSERT_EQ(State::intro,g.getStateType());
    g.getStateType();   // getStateType():  IntroState -> IntroState
    g.guess("test");    // guess(string):   IntroState -> IntroState
    ASSERT_EQ(State::intro,g.getStateType());
    g.print();          // print():         IntroState -> PlayState
    ASSERT_EQ(State::play,g.getStateType());
}

TEST(StateMachineTest, TestPlayState)
{
    Game g{};
    g.changeState(new PlayState(&g));

    // general tests
    ASSERT_EQ(State::play,g.getStateType());
    g.getStateType();   // getStateType():  PlayState -> PlayState 
    g.print();          // print():         PlayState -> PlayState
    ASSERT_EQ(State::play,g.getStateType());
}

TEST(StateMachineTest, TestPlayStateToWinnerState)
{
    Game g{};
    g.changeState(new PlayState(&g));

    std::string hiddenWord{g.m_word};
    g.guess(hiddenWord);
    ASSERT_EQ(State::winner,g.getStateType());
}

TEST(StateMachineTest, TestPlayStateToWinnerStateStepwise)
{
    Game g{};
    g.changeState(new PlayState(&g));

    std::string hiddenWord{g.m_word};
    for(auto c: hiddenWord)
        g.guess(std::string(1,c));
    
    ASSERT_EQ(State::winner,g.getStateType());
}

TEST(StateMachineTest, TestPlayStateToLoserState)
{
    Game g{};
    g.changeState(new PlayState(&g));

    while(!g.gameEnd())
        g.guess("test");
    
    ASSERT_EQ(State::loser,g.getStateType());
}

TEST(StateMachineTest, TestWinnerState)
{
    Game g{};
    g.changeState(new WinnerState(&g));
    ASSERT_EQ(State::winner,g.getStateType());
    g.getStateType();   // getStateType():  WinnerState -> WinnerState
    g.guess("test");    // guess(string):   WinnerState -> WinnerState
    g.print();          // print():         WinnerState -> WinnerState
    ASSERT_EQ(State::winner,g.getStateType());
}

TEST(StateMachineTest, TestLoserState)
{
    Game g{};
    g.changeState(new LoserState(&g));
    ASSERT_EQ(State::loser,g.getStateType());
    g.getStateType();   // getStateType():  LoserState -> LoserState
    g.guess("test");    // guess(string):   LoserState -> LoserState
    g.print();          // print():         LoserState -> LoserState
    ASSERT_EQ(State::loser,g.getStateType());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
