#include "Piezas.h"
#include <vector>
#include <iostream>

/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/

static const int num_rows = 3;
static const int num_cols = 4;

/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and
 * specifies it is X's turn first
**/
Piezas::Piezas()
{
    // set default 3 rows, 4 columns
    board.resize(num_rows);
    for (int row = 0; row < num_rows; ++row) {
        board[row].resize(num_cols);
    }

    // set an empty board
    for (int row = 0; row < num_rows; ++row) {
        for (int col = 0; col < num_cols; ++col) {
            board[row][col] = Blank;
        }
    }

    // specify it is X's turn first
    turn = X;
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
    // set an empty board
    for (int row = 0; row < num_rows; ++row) {
        for (int col = 0; col < num_cols; ++col) {
            board[row][col] = Blank;
        }
    }
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/
Piece Piezas::dropPiece(int column)
{
    Piece piece = Blank;

    // Out of bounds coordinates
    if (column < 0 || column >= num_cols) {
        piece = Invalid;
    // Inside bounds coordinates
    } else {
        bool found_location = false;
        int row = 2;
        // Because of the flipped orientation, when you drop the pieces,
        // they rise up to the top.
        for (row = 2; row >= 0; --row) {
            // If current space is occupied
            if (board[row][column] != Blank) {
                found_location = false;
                break;
            // If previous space is occupied && current space is free
            } else if (board[row - 1][column] != Blank && board[row][column] == Blank) {
                found_location = true;
                break;
            // If row == 0 && current space is free
            } else if (row == 0 && board[row][column] == Blank) {
                found_location = true;
                break;
            }
        }

        if (found_location) {
            std::cout << "row = " << row << std::endl;
            std::cout << "col = " << column << std::endl;
            board[row][column] = turn;
            piece = board[row][column];
        } else {
            piece = Blank;
        }
    }

    // set the turn to the other player
    turn = (turn == X) ? O : X;

    return piece;
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
    const bool row_invalid = row < 0 || row >= num_rows;
    const bool col_invalid = column < 0 || column >= num_cols;

    if (row_invalid || col_invalid) {
        return Invalid;
    } else {
        // This can return either the piece or a Blank.
        // By default when the board is cleared, all values are set to Blank.
        return board[row][column];
    }
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{
    return Blank;
}
