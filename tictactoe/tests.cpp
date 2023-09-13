#include "Board.h"
#include <gtest/gtest.h>

// check if all fields are initialized empty
TEST(BoardTest, EmptyFields)
{
    Board b{};
    for(int row{0}; row < 3; ++row)
        for(int col{0}; col < 3; ++col)
            ASSERT_EQ(false,b.check(row,col));
}

// check if setting each field works
TEST(BoardTest, FillFields)
{
    Board b{};
    for(int row{0}; row < 3; ++row){
        for(int col{0}; col < 3; ++col){
            b.move(row,col);
            ASSERT_EQ(true,b.check(row,col));
        }
    }
}

// check all win states
TEST(BoardTest, WinStates)
{
    Board b{};

    /*
     * x x x
     * - - -
     * - - -
     */
    b.move(0,0);
    b.move(0,1);
    b.move(0,2);
    ASSERT_EQ(true,b.isWon());

    /*
     * - - -
     * x x x
     * - - -
     */
    b = Board{};
    b.move(1,0);
    b.move(1,1);
    b.move(1,2);
    ASSERT_EQ(true,b.isWon());

    /*
     * - - -
     * - - -
     * x x x
     */
    b = Board{};
    b.move(2,0);
    b.move(2,1);
    b.move(2,2);
    ASSERT_EQ(true,b.isWon());

    /*
     * x - -
     * x - -
     * x - -
     */
    b = Board{};
    b.move(0,0);
    b.move(1,0);
    b.move(2,0);
    ASSERT_EQ(true,b.isWon());

    /*
     * - x -
     * - x -
     * - x -
     */
    b = Board{};
    b.move(0,1);
    b.move(1,1);
    b.move(2,1);
    ASSERT_EQ(true,b.isWon());

    /*
     * - - x
     * - - x
     * - - x
     */
    b = Board{};
    b.move(0,2);
    b.move(1,2);
    b.move(2,2);
    ASSERT_EQ(true,b.isWon());

    /*
     * x - -
     * - x -
     * - - x
     */
    b = Board{};
    b.move(0,0);
    b.move(1,1);
    b.move(2,2);
    ASSERT_EQ(true,b.isWon());

    /*
     * - - x
     * - x -
     * x - -
     */
    b = Board{};
    b.move(0,2);
    b.move(1,1);
    b.move(2,0);
    ASSERT_EQ(true,b.isWon());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
