/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"

class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};


TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}


TEST(PiezasTest, test_constructor_1)
{
    // This test checks if the constructor sets up the memory for the map correctly.
    Piezas game;

    // The constructor sets an empty board, which means that all the spaces have to be blank.
    // They cannot contain any garbage values.
    // This for loop is only one of the few places where we need to violate the one assert rule.
    for (int row = 0; row < BOARD_ROWS; ++row) {
        for (int col = 0; col < BOARD_COLS; ++col) {
            Piece piece = game.pieceAt(row, col);
            ASSERT_EQ(piece, Blank);
        }
    }
}


TEST(PiezasTest, test_constructor_2)
{
    // This test checks if the constructor sets X as the first player.
    Piezas game;

    // When I drop the piece, it should be piece X.
    Piece piece = game.dropPiece(0);
    ASSERT_EQ(piece, X);
}


TEST(PiezasTest, test_reset_empty)
{
    // This test checks if Piezas::reset() clears the memory correctly,
    // having an already empty board.
    Piezas game;
    game.reset();

    // reset should make all the pieces blank again
    // This for loop is only one of the few places where we need to violate the one assert rule.
    for (int row = 0; row < BOARD_ROWS; ++row) {
        for (int col = 0; col < BOARD_COLS; ++col) {
            Piece piece = game.pieceAt(row, col);
            ASSERT_EQ(piece, Blank);
        }
    }
}


TEST(PiezasTest, test_reset_partial)
{
    // This test checks if Piezas::reset() clears the memory correctly,
    // having a partially occupied board.
    Piezas game;

    // Add pieces to various collumns.
    // game::reset() needs to clear
    // a column with 3 pieces
    // a column with 2 pieces
    // a column with 1 pieces
    // a column with 0 pieces
    game.dropPiece(0);
    game.dropPiece(0);
    game.dropPiece(0);
    game.dropPiece(2);
    game.dropPiece(2);
    game.dropPiece(3);
    game.reset();

    // reset should make all the pieces blank again
    // This for loop is only one of the few places where we need to violate the one assert rule.
    for (int row = 0; row < BOARD_ROWS; ++row) {
        for (int col = 0; col < BOARD_COLS; ++col) {
            Piece piece = game.pieceAt(row, col);
            ASSERT_EQ(piece, Blank);
        }
    }
}


TEST(PiezasTest, test_reset_full)
{
    // This test checks if Piezas::reset() clears the memory correctly,
    // having a completely full board with pieces.
    Piezas game;

    // Fill up the entire board with pieces.
    // game::reset() needs to clear the entire board.
    for (int row = 0; row < BOARD_ROWS; ++row) {
        for (int col = 0; col < BOARD_COLS; ++col) {
            game.dropPiece(col);
        }
    }
    game.reset();

    // reset should make all the pieces blank again
    // This for loop is only one of the few places where we need to violate the one assert rule.
    for (int row = 0; row < BOARD_ROWS; ++row) {
        for (int col = 0; col < BOARD_COLS; ++col) {
            Piece piece = game.pieceAt(row, col);
            ASSERT_EQ(piece, Blank);
        }
    }
}


TEST(PiezasTest, test_pieceAt_Invalid_1)
{
    // This test checks if Piezas::pieceAt() returns Invalid upon having the column
    // out of bounds to the negative.
    Piezas game;

    Piece piece = game.pieceAt(1, -1);
    ASSERT_EQ(piece, Invalid);
}


TEST(PiezasTest, test_pieceAt_Invalid_2)
{
    // This test checks if Piezas::pieceAt() returns Invalid upon having the column
    // out of bounds to the positive.
    Piezas game;

    Piece piece = game.pieceAt(1, BOARD_COLS);
    ASSERT_EQ(piece, Invalid);
}


TEST(PiezasTest, test_pieceAt_Invalid_3)
{
    // This test checks if Piezas::pieceAt() returns Invalid upon having the row
    // out of bounds to the negative.
    Piezas game;

    Piece piece = game.pieceAt(-1, 1);
    ASSERT_EQ(piece, Invalid);
}


TEST(PiezasTest, test_pieceAt_Invalid_4)
{
    // This test checks if Piezas::pieceAt() returns Invalid upon having the row
    // out of bounds to the positive.
    Piezas game;

    Piece piece = game.pieceAt(BOARD_ROWS, 1);
    ASSERT_EQ(piece, Invalid);
}
