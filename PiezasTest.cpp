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

#define const const

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}


TEST(PiezasTest, test_constructor)
{
    const int num_rows = 3;
    const int num_cols = 4;

    Piezas game;

    // The constructor sets an empty board, which means that all the spaces have to be blank.
    // They cannot contain any garbage values.
    // This for loop is only one of the few places where we need to violate the one assert rule.
    for (int row = 0; row < num_rows; ++row) {
        for (int col = 0; col < num_cols; ++col) {
            Piece piece = game.pieceAt(row, col);
            ASSERT_EQ(piece, Blank);
        }
    }

    // When I drop the piece, it should be piece X.
    Piece piece = game.dropPiece(0);
    ASSERT_EQ(piece, X);
}
