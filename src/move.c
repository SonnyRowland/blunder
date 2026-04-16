#include "move.h"
#include "board.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static Board move_piece(Board board, Move move);
bool is_piece_move_valid(Piece piece, Move move);
bool is_square_on_board(Move move);
bool is_player_in_check(Board board);

Board apply_move(Board board, Move move)
{

    // Check piece exists
    if (board.grid[move.from_rank][move.from_file] == EMPTY) {
        printf("No piece here...\n");
        return board;
    }

    // Check move is actually a move (and not just staying still)
    if (move.from_rank == move.to_rank && move.from_file == move.to_file) {
        printf("Move must be a move...\n");
        return board;
    }

    if (!is_square_on_board(move)) {
        printf("Move is out of board bounds...\n");
        return board;
    }

    if (!is_piece_move_valid(board.grid[move.from_rank][move.from_file], move)) {
        printf("Move is illegal...\n");
        return board;
    }

    // Prevent player taking their own piece
    if (board.grid[move.to_rank][move.to_file] * board.turn > 0) {
        printf("Cannot take your own piece...\n");
        return board;
    }

    // Ensure player is not in check
    Board temp_board = move_piece(board, move);
    temp_board.turn *= -1;
    if (is_player_in_check(temp_board)) {
        printf("Move would leave king in check...\n");
        return board;
    }

    printf("Move is legal...\n");
    return move_piece(board, move);
}

static Board move_piece(Board board, Move move)
{
    Piece moving_piece = board.grid[move.from_rank][move.from_file];

    bool is_capture = board.grid[move.to_rank][move.from_rank] != EMPTY;
    bool is_pawn_move = moving_piece == W_PAWN || moving_piece == B_PAWN;

    board.grid[move.to_rank][move.to_file] = board.grid[move.from_rank][move.from_file];
    board.grid[move.from_rank][move.from_file] = EMPTY;
    board.turn *= -1;
    board.fullmove_count++;

    if (is_capture || is_pawn_move) {
        board.halfmove_clock = 0;
    } else {
        board.halfmove_clock++;
    }

    return board;
}

// Check the move is correct for the piece specified
bool is_piece_move_valid(Piece piece, Move move)
{

    // TODO: Check no piece is in the way

    switch (piece) {

    case W_PAWN:
        // TODO: amend the following for the instance when the pawn is taking a piece
        if (move.from_file != move.to_file)
            return false;
        if (move.to_rank - move.from_rank == 1) {
            return true;
        } else if (move.from_rank == 1 && move.to_rank == 3) {
            return true;
        } else {
            return false;
        }

    case B_PAWN:
        // TODO: amend the following for the instance when the pawn is taking a piece
        if (move.from_file != move.to_file)
            return false;
        if (move.from_rank - move.to_rank == 1) {
            return true;
        } else if (move.from_rank == 6 && move.to_rank == 4) {
            return true;
        } else {
            return false;
        }

    case W_ROOK:
        if ((move.to_rank == move.from_rank) || (move.to_file == move.from_file))
            return true;
        return false;

    case B_ROOK:
        if ((move.to_rank == move.from_rank) || (move.to_file == move.from_file))
            return true;
        return false;

    case W_BISHOP:
        if (abs(move.to_rank - move.from_rank) == abs(move.to_file - move.from_file))
            return true;
        return false;

    case B_BISHOP:
        if (abs(move.to_rank - move.from_rank) == abs(move.to_file - move.from_file))
            return true;
        return false;

    case W_KNIGHT:
        if (((abs(move.to_file - move.from_file) == 2) && (abs(move.to_rank - move.from_rank) == 1)) || (abs(move.to_file - move.from_file) == 1) && (abs(move.to_rank - move.from_rank) == 2))
            return true;
        return false;

    case B_KNIGHT:
        if (((abs(move.to_file - move.from_file) == 2) && (abs(move.to_rank - move.from_rank) == 1)) || (abs(move.to_file - move.from_file) == 1) && (abs(move.to_rank - move.from_rank) == 2))
            return true;
        return false;

    case W_QUEEN:
        if (abs(move.to_rank - move.from_rank) == abs(move.to_file - move.from_file))
            return true;
        if ((move.to_rank == move.from_rank) || (move.to_file == move.from_file))
            return true;
        return false;

    case B_QUEEN:
        if (abs(move.to_rank - move.from_rank) == abs(move.to_file - move.from_file))
            return true;
        if ((move.to_rank == move.from_rank) || (move.to_file == move.from_file))
            return true;
        return false;

    case W_KING:
        if ((abs(move.to_rank - move.from_rank) <= 1) && (abs(move.to_file - move.from_file) <= 1))
            return true;
        return false;

    case B_KING:
        if ((abs(move.to_rank - move.from_rank) <= 1) && (abs(move.to_file - move.from_file) <= 1))
            return true;
        return false;

    default:
        break;
    }

    return false;
}

// Ensure the move stays within the bounds of the board
bool is_square_on_board(Move move)
{
    if (!(0 <= move.from_rank && move.from_rank <= 7))
        return false;
    if (!(0 <= move.from_file && move.from_file <= 7))
        return false;
    if (!(0 <= move.to_rank && move.to_rank <= 7))
        return false;
    if (!(0 <= move.to_file && move.to_file <= 7))
        return false;
    return true;
}

bool is_player_in_check(Board board)
{
    // Scan for king position
    int king_rank, king_file;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board.grid[i][j] == 6 * board.turn) {
                king_rank = i;
                king_file = j;
                break;
            }
        }
    }

    // Search all opponent pieces for potential checking piece
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board.grid[i][j] * board.turn < 0) {
                Move temp_move = {
                    i,
                    j,
                    king_rank,
                    king_file,
                };

                if (is_piece_move_valid(board.grid[i][j], temp_move)) {
                    return true;
                };
            }
        }
    }

    return false;
}