#include "board.h"
#include "fen.h"

#include <stdbool.h>
#include <stdlib.h>

Board get_start_pos()
{
    return fen_to_board(start_pos);
}

bool is_in_check(Board board)
{
    // Find king
    int king_rank = -1, king_file = -1;

    for (int rank = 0; rank < 8 && king_rank == -1; rank++) {
        for (int file = 0; file < 8; file++) {
            if (board.grid[rank][file] * board.turn == 6) {
                king_rank = rank;
                king_file = file;
                break;
            }
        }
    }

    // Return if no king on board
    if (king_rank == -1)
        return 0;

    int rank_idx, file_idx;

    // Find rooks and queens
    if (king_rank > 0) {
        rank_idx = king_rank - 1;
        while (rank_idx > 0 && board.grid[rank_idx][king_file] == EMPTY)
            rank_idx--;
        if (board.grid[rank_idx][king_file] * board.turn == -4 || board.grid[rank_idx][king_file] * board.turn == -5)
            return 1;
    }

    if (king_rank < 7) {
        rank_idx = king_rank + 1;
        while (rank_idx < 7 && board.grid[rank_idx][king_file] == EMPTY) {
            rank_idx++;
        }
        if (board.grid[rank_idx][king_file] * board.turn == -4 || board.grid[rank_idx][king_file] * board.turn == -5)
            return 1;
    }

    if (king_file > 0) {
        file_idx = king_file - 1;
        while (file_idx > 0 && board.grid[king_rank][file_idx] == EMPTY)
            file_idx--;
        if (board.grid[king_rank][file_idx] * board.turn == -4 || board.grid[king_rank][file_idx] * board.turn == -5)
            return 1;
    }

    if (king_file < 7) {
        file_idx = king_file + 1;
        while (file_idx < 7 && board.grid[king_rank][file_idx] == EMPTY)
            file_idx++;
        if (board.grid[king_rank][file_idx] * board.turn == -4 || board.grid[king_rank][file_idx] * board.turn == -5)
            return 1;
    }

    // Find bishops and queens
    if (king_rank > 0 && king_file > 0) {
        rank_idx = king_rank - 1;
        file_idx = king_file - 1;
        while (rank_idx > 0 && file_idx > 0 && board.grid[rank_idx][file_idx] == EMPTY) {
            rank_idx--;
            file_idx--;
        }
        if (board.grid[rank_idx][file_idx] * board.turn == -3 || board.grid[rank_idx][file_idx] * board.turn == -5)
            return 1;
    }

    if (king_rank > 0 && king_file < 7) {
        rank_idx = king_rank - 1;
        file_idx = king_file + 1;
        while (rank_idx > 0 && file_idx < 7 && board.grid[rank_idx][file_idx] == EMPTY) {
            rank_idx--;
            file_idx++;
        }
        if (board.grid[rank_idx][file_idx] * board.turn == -3 || board.grid[rank_idx][file_idx] * board.turn == -5)
            return 1;
    }

    if (king_rank < 7 && king_file > 0) {
        rank_idx = king_rank + 1;
        file_idx = king_file - 1;
        while (rank_idx < 7 && file_idx > 0 && board.grid[rank_idx][file_idx] == EMPTY) {
            rank_idx++;
            file_idx--;
        }
        if (board.grid[rank_idx][file_idx] * board.turn == -3 || board.grid[rank_idx][file_idx] * board.turn == -5)
            return 1;
    }

    if (king_rank < 7 && king_file < 7) {
        rank_idx = king_rank + 1;
        file_idx = king_file + 1;
        while (rank_idx < 7 && file_idx < 7 && board.grid[rank_idx][file_idx] == EMPTY) {
            rank_idx++;
            file_idx++;
        }
        if (board.grid[rank_idx][file_idx] * board.turn == -3 || board.grid[rank_idx][file_idx] * board.turn == -5)
            return 1;
    }

    for (rank_idx = king_rank - 2; rank_idx <= king_rank + 2; rank_idx++) {
        if (rank_idx < 0 || rank_idx > 7)
            continue;
        for (file_idx = king_file - 2; file_idx <= king_file + 2; file_idx++) {
            if (file_idx < 0 || file_idx > 7)
                continue;
            if (abs(king_rank - rank_idx) == abs(king_file - file_idx))
                continue;
            if ((king_rank - rank_idx) == 0 || (king_file - file_idx) == 0)
                continue;
            if (board.grid[rank_idx][file_idx] * board.turn == -2)
                return 1;
        }
    }

    rank_idx = king_rank + board.turn;
    if (rank_idx >= 0 && rank_idx <= 7) {
        file_idx = king_file - 1;
        if (file_idx >= 0 && (board.grid[rank_idx][file_idx] == -1 * board.turn))
            return 1;
        file_idx = king_file + 1;
        if (file_idx <= 7 && (board.grid[rank_idx][file_idx] == -1 * board.turn))
            return 1;
    }

    return 0;
}