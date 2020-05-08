#include "Piezas.h"
#include <vector>
#include <cstddef>

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


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and
 * specifies it is X's turn first
**/
Piezas::Piezas()
{
    // set default 3 rows, 4 columns
    board.resize(BOARD_ROWS);
    for (int row = 0; row < BOARD_ROWS; ++row) {
        board[row].resize(BOARD_COLS);
    }

    // set an empty board
    for (int row = 0; row < BOARD_ROWS; ++row) {
        for (int col = 0; col < BOARD_COLS; ++col) {
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
    for (int row = 0; row < BOARD_ROWS; ++row) {
        for (int col = 0; col < BOARD_COLS; ++col) {
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
    if (column < 0 || column >= BOARD_COLS) {
        piece = Invalid;
    // Inside bounds coordinates
    } else {
        bool found_location = false;
        int row = BOARD_ROWS - 1;
        // Because of the flipped orientation, when you drop the pieces,
        // they rise up to the top.
        for (row = BOARD_ROWS - 1; row >= 0; --row) {
            // If current space is occupied
            if (board[row][column] != Blank) {
                found_location = false;
                break;
            // If previous space is occupied && current space is free
            } else if (row > 0 && board[row - 1][column] != Blank && board[row][column] == Blank) {
                found_location = true;
                break;
            // If row == 0 && current space is free
            } else if (row == 0 && board[row][column] == Blank) {
                found_location = true;
                break;
            }
        }

        if (found_location) {
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
    const bool row_invalid = row < 0 || row >= BOARD_ROWS;
    const bool col_invalid = column < 0 || column >= BOARD_COLS;

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
    // These variables hold the maximum number of continuous squares for each player in the whole board.
    std::size_t O_counter_max = 0;
    std::size_t X_counter_max = 0;

    // These variables hold the current number of continuous squares for each player in the whole board.
    std::size_t O_counter = 0;
    std::size_t X_counter = 0;

    // These variables record if the current cell is within a continuous sequence of X's or O's.
    bool O_sequence = false;
    bool X_sequence = false;

    // First scan the rows.
    for (int row = 0; row < BOARD_ROWS; ++row) {
        for (int col = 0; col < BOARD_COLS; ++col) {
            // Check for any Blank squares only in the first round, which touches all the squares.
            if (board[row][col] == Blank)
                return Invalid;

            // The start of an O sequence.
            if (!O_sequence && board[row][col] == O) {
                O_sequence = true;
                O_counter = 1;
            // The end of an O sequence.
            } else if (O_sequence && board[row][col] != O) {
                O_sequence = false;
                if (O_counter > O_counter_max)
                    O_counter_max = O_counter;
                O_counter = 0;
            // In the middle of an O sequence.
            } else if (O_sequence && board[row][col] == O) {
                ++O_counter;
            }

            // The start of an X sequence.
            if (!X_sequence && board[row][col] == X) {
                X_sequence = true;
                X_counter = 1;
            // The end of an X sequence.
            } else if (X_sequence && board[row][col] != X) {
                X_sequence = false;
                if (X_counter > X_counter_max)
                    X_counter_max = X_counter;
                X_counter = 0;
            // In the middle of an X sequence.
            } else if (X_sequence && board[row][col] == X) {
                ++X_counter;
            }
        }

        // The end of an O sequence.
        O_sequence = false;
        if (O_counter > O_counter_max)
            O_counter_max = O_counter;
        O_counter = 0;

        // The end of an X sequence.
        X_sequence = false;
        if (X_counter > X_counter_max)
            X_counter_max = X_counter;
        X_counter = 0;
    }

    // Second scan the columns.
    for (int col = 0; col < BOARD_COLS; ++col) {
        for (int row = 0; row < BOARD_ROWS; ++row) {
            // The start of an O sequence.
            if (!O_sequence && board[row][col] == O) {
                O_sequence = true;
                O_counter = 1;
            // The end of an O sequence.
            } else if (O_sequence && board[row][col] != O) {
                O_sequence = false;
                if (O_counter > O_counter_max)
                    O_counter_max = O_counter;
                O_counter = 0;
            // In the middle of an O sequence.
            } else if (O_sequence && board[row][col] == O) {
                ++O_counter;
            }

            // The start of an X sequence.
            if (!X_sequence && board[row][col] == X) {
                X_sequence = true;
                X_counter = 1;
            // The end of an X sequence.
            } else if (X_sequence && board[row][col] != X) {
                X_sequence = false;
                if (X_counter > X_counter_max)
                    X_counter_max = X_counter;
                X_counter = 0;
            // In the middle of an X sequence.
            } else if (X_sequence && board[row][col] == X) {
                ++X_counter;
            }
        }

        // The end of an O sequence.
        O_sequence = false;
        if (O_counter > O_counter_max)
            O_counter_max = O_counter;
        O_counter = 0;

        // The end of an X sequence.
        X_sequence = false;
        if (X_counter > X_counter_max)
            X_counter_max = X_counter;
        X_counter = 0;
    }

    // Third compare the maximum counters to see who won.
    if (O_counter_max == X_counter_max) {
        return Blank;
    } else if (O_counter_max > X_counter_max) {
        return O;
    } else if (O_counter_max < X_counter_max) {
        return X;
    }
}
