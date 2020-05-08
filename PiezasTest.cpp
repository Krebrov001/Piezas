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


TEST(PiezasTest, constructor_1)
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


TEST(PiezasTest, constructor_2)
{
    // This test checks if the constructor sets X as the first player.
    Piezas game;

    // When I drop the piece, it should be piece X.
    Piece piece = game.dropPiece(0);
    ASSERT_EQ(piece, X);
}


TEST(PiezasTest, reset_empty)
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


TEST(PiezasTest, reset_partial)
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


TEST(PiezasTest, reset_full)
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


TEST(PiezasTest, dropPiece_Invalid_1)
{
    // This test checks if Piezas::dropPiece() returns Invalid upon having the column
    // out of bounds to the negative.
    Piezas game;

    Piece piece = game.dropPiece(-1);
    ASSERT_EQ(piece, Invalid);
}


TEST(PiezasTest, dropPiece_Invalid_2)
{
    // This test checks if Piezas::dropPiece() returns Invalid upon having the column
    // out of bounds to the positive.
    Piezas game;

    Piece piece = game.dropPiece(BOARD_COLS);
    ASSERT_EQ(piece, Invalid);
}


TEST(PiezasTest, dropPiece_Invalid_3)
{
    // This test checks if Piezas::dropPiece() returns Invalid upon having the column
    // out of bounds to the negative.
    Piezas game;

    Piece piece = game.dropPiece(-10);
    ASSERT_EQ(piece, Invalid);
}


TEST(PiezasTest, dropPiece_Invalid_4)
{
    // This test checks if Piezas::dropPiece() returns Invalid upon having the column
    // out of bounds to the positive.
    Piezas game;

    Piece piece = game.dropPiece(BOARD_COLS + 10);
    ASSERT_EQ(piece, Invalid);
}


TEST(PiezasTest, pieceAt_Invalid_1)
{
    // This test checks if Piezas::pieceAt() returns Invalid upon having the column
    // out of bounds to the negative.
    Piezas game;

    Piece piece = game.pieceAt(1, -1);
    ASSERT_EQ(piece, Invalid);
}


TEST(PiezasTest, pieceAt_Invalid_2)
{
    // This test checks if Piezas::pieceAt() returns Invalid upon having the column
    // out of bounds to the positive.
    Piezas game;

    Piece piece = game.pieceAt(1, BOARD_COLS);
    ASSERT_EQ(piece, Invalid);
}


TEST(PiezasTest, pieceAt_Invalid_3)
{
    // This test checks if Piezas::pieceAt() returns Invalid upon having the row
    // out of bounds to the negative.
    Piezas game;

    Piece piece = game.pieceAt(-1, 1);
    ASSERT_EQ(piece, Invalid);
}


TEST(PiezasTest, pieceAt_Invalid_4)
{
    // This test checks if Piezas::pieceAt() returns Invalid upon having the row
    // out of bounds to the positive.
    Piezas game;

    Piece piece = game.pieceAt(BOARD_ROWS, 1);
    ASSERT_EQ(piece, Invalid);
}


TEST(PiezasTest, pieceAt_Invalid_5)
{
    // This test checks if Piezas::pieceAt() returns Invalid upon having a corenr case:
    // the row out of bounds to the negative AND the column out of bounds to the negative
    Piezas game;

    Piece piece = game.pieceAt(-1, -1);
    ASSERT_EQ(piece, Invalid);
}


TEST(PiezasTest, pieceAt_Invalid_6)
{
    // This test checks if Piezas::pieceAt() returns Invalid upon having a corenr case:
    // the row out of bounds to the negative AND the column out of bounds to the positive
    Piezas game;

    Piece piece = game.pieceAt(-1, BOARD_COLS);
    ASSERT_EQ(piece, Invalid);
}


TEST(PiezasTest, pieceAt_Invalid_7)
{
    // This test checks if Piezas::pieceAt() returns Invalid upon having a corenr case:
    // the row out of bounds to the positive AND the column out of bounds to the negative
    Piezas game;

    Piece piece = game.pieceAt(BOARD_ROWS, -1);
    ASSERT_EQ(piece, Invalid);
}


TEST(PiezasTest, pieceAt_Invalid_8)
{
    // This test checks if Piezas::pieceAt() returns Invalid upon having a corenr case:
    // the row out of bounds to the positive AND the column out of bounds to the positive
    Piezas game;

    Piece piece = game.pieceAt(BOARD_ROWS, BOARD_COLS);
    ASSERT_EQ(piece, Invalid);
}


TEST(PiezasTest, pieceAt_Invalid_9)
{
    // This test checks if Piezas::pieceAt() returns Invalid upon having the column way
    // out of bounds to the negative.
    Piezas game;

    Piece piece = game.pieceAt(1, -50);
    ASSERT_EQ(piece, Invalid);
}


TEST(PiezasTest, pieceAt_Invalid_10)
{
    // This test checks if Piezas::pieceAt() returns Invalid upon having the column way
    // out of bounds to the positive.
    Piezas game;

    Piece piece = game.pieceAt(1, BOARD_COLS + 50);
    ASSERT_EQ(piece, Invalid);
}


TEST(PiezasTest, pieceAt_Invalid_11)
{
    // This test checks if Piezas::pieceAt() returns Invalid upon having the row way
    // out of bounds to the negative.
    Piezas game;

    Piece piece = game.pieceAt(-50, 1);
    ASSERT_EQ(piece, Invalid);
}


TEST(PiezasTest, pieceAt_Invalid_12)
{
    // This test checks if Piezas::pieceAt() returns Invalid upon having the row way
    // out of bounds to the positive.
    Piezas game;

    Piece piece = game.pieceAt(BOARD_ROWS + 50, 1);
    ASSERT_EQ(piece, Invalid);
}


TEST(PiezasTest, first_dropPiece_succeeds)
{
    // This test checks if after you drop a piece into an empty collumn,
    // that piece falls down to the bottom of the column and that the memory is indeed modified.
    Piezas game;

    game.dropPiece(1);

    Piece piece = game.pieceAt(0, 1);
    ASSERT_EQ(piece, X);
}


TEST(PiezasTest, first_dropPiece_no_footprints)
{
    // This test checks if after you drop a piece into an empty collumn,
    // that piece falls down to the bottom of the column and that it doesn't corrupt all the other
    // cells in that collumn. It is possible for a bad implementation to leave "footprints" in
    // the memory, where all the cells in that collumn will have the value of that piece.
    // It would just blindly assign every cell in that column to have that piece value.
    Piezas game;

    game.dropPiece(1);

    Piece piece = game.pieceAt(1, 1);
    ASSERT_EQ(piece, Blank);

    piece = game.pieceAt(2, 1);
    ASSERT_EQ(piece, Blank);
}


TEST(PiezasTest, second_dropPiece_switches_plyaer)
{
    // This test checks that dropPiece() switches to O after an X is dropped.
    Piezas game;

    game.dropPiece(0);  // places X

    // When I drop the piece, it should be piece O.
    Piece piece = game.dropPiece(0);
    ASSERT_EQ(piece, O);
}


TEST(PiezasTest, third_dropPiece_switches_plyaer)
{
    // This test checks that dropPiece() switches to X after an O is dropped.
    Piezas game;

    game.dropPiece(0);  // places X
    game.dropPiece(0);  // places O

    // When I drop the piece, it should be piece X.
    Piece piece = game.dropPiece(0);
    ASSERT_EQ(piece, X);
}


TEST(PiezasTest, second_dropPiece_goes_above)
{
    // This test checks that a second dropPiece() actually places the second piece in the cell above
    // the first one, and not for instance in the same grid location, overwriting the first one.
    Piezas game;

    game.dropPiece(2);  // places X
    game.dropPiece(2);  // places O

    Piece piece = game.pieceAt(0, 2);
    ASSERT_EQ(piece, X);
    piece = game.pieceAt(1, 2);
    ASSERT_EQ(piece, O);
}


TEST(PiezasTest, dropPiece_Blank_1)
{
    // This test checks if a user wanted to drop a piece into a full column, it should return blank.
    // Then that player loses their turn.
    Piezas game;

    Piece turn = X;

    for (int row = 0; row < BOARD_ROWS; ++row, turn = (turn == X) ? O : X) {
        game.dropPiece(BOARD_COLS - 1);  // a valid grid loaction
    }

    // Attempts to drop a piece into a full collumn.
    Piece piece = game.dropPiece(BOARD_COLS - 1);
    turn = (turn == X) ? O : X;
    ASSERT_EQ(piece, Blank);

    piece = game.dropPiece(0);
    ASSERT_EQ(piece, turn);
}


TEST(PiezasTest, dropPiece_Blank_2)
{
    // This test checks if we are able to successfully fill the whole column using dropPiece().
    // If a user wanted to drop a piece into a full column, the memory contents of the board should
    // not change.
    Piezas game;

    for (int row = 0; row < BOARD_ROWS; ++row) {
        game.dropPiece(BOARD_COLS - 1);  // a valid grid loaction
    }

    // Attempts to drop a piece into a full collumn.
    game.dropPiece(BOARD_COLS - 1);

    Piece actual_piece = Blank;
    Piece theoretical_piece = X;

    for (int row = 0; row < BOARD_ROWS; ++row, theoretical_piece = (theoretical_piece == X) ? O : X) {
        actual_piece = game.pieceAt(row, BOARD_COLS - 1);  // a valid grid loaction
        ASSERT_EQ(actual_piece, theoretical_piece);
    }
}


TEST(PiezasTest, dropPiece_Invalid_5)
{
    // This test checks if a user wanted to drop a piece into an invalid column,
    // it should return Invalid and that player loses their turn.
    Piezas game;

    Piece turn = X, returned = Blank;

    game.dropPiece(1);
    turn = (turn == X) ? O : X;

    returned = game.dropPiece(BOARD_COLS + 2);
    turn = (turn == X) ? O : X;
    ASSERT_EQ(returned, Invalid);

    returned = game.dropPiece(2);
    ASSERT_EQ(returned, turn);
}


TEST(PiezasTest, gameState_Blank_edges)
{
    // This test checks if Piezas::gameState() correctly deals with blank edges.
    // The whole entire board is filled except for the last column and the last row.
    // This test should detect if there is an off by one error.
    Piezas game;

    game.dropPiece(0);  // drop X into [0][0]
    game.dropPiece(1);  // drop O into [0][1]
    game.dropPiece(2);  // drop X into [0][2]
    game.dropPiece(0);  // drop O into [1][0]
    game.dropPiece(1);  // drop X into [1][1]
    game.dropPiece(2);  // drop O into [1][2]

    Piece winner = game.gameState();
    ASSERT_EQ(winner, Invalid);
}


TEST(Piezas, gameState_tie_1)
{
    // This test checks if Piezas::gameState() correctly deals with ties when the maximum
    // continuous sequences for each player have a length of 1 only.
    Piezas game;

    game.dropPiece(0);  // drop X into [0][0]
    game.dropPiece(1);  // drop O into [0][1]
    game.dropPiece(2);  // drop X into [0][2]
    game.dropPiece(3);  // drop O into [0][3]
    game.dropPiece(3);  // drop X into [1][3]
    game.dropPiece(2);  // drop O into [1][2]
    game.dropPiece(1);  // drop X into [1][1]
    game.dropPiece(0);  // drop O into [1][0]
    game.dropPiece(0);  // drop X into [2][0]
    game.dropPiece(1);  // drop O into [2][1]
    game.dropPiece(2);  // drop X into [2][2]
    game.dropPiece(3);  // drop O into [2][3]

    Piece winner = game.gameState();
    ASSERT_EQ(winner, Blank);
}
