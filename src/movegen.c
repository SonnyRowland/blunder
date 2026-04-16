#include "movegen.h"
#include "board.h"
#include "move.h"

#include <stdlib.h>

static void generate_pawn_moves(int rank, int file, Board board, MoveList* move_list);
static void generate_knight_moves(int rank, int file, Board board, MoveList* move_list);
static void generate_bishop_moves(int rank, int file, Board board, MoveList* move_list);
static void generate_rook_moves(int rank, int file, Board board, MoveList* move_list);
static void generate_king_moves(int rank, int file, Board board, MoveList* move_list);

MoveList generate_legal_moves(Board board)
{

    MoveList move_list = { .count = 0 };

    for (int rank = 0; rank < 8; rank++) {
        for (int file = 0; file < 8; file++) {
            Piece piece = board.grid[rank][file];

            if ((piece * board.turn) <= 0)
                continue;

            // Process white and black pieces in same switch statement
            int piece_abs = abs((int)piece);

            switch (piece_abs) {
            // Deal with pawn case
            case (1): {
                generate_pawn_moves(rank, file, board, &move_list);
                break;
            }
            // Deal with knight case
            case (2):
                generate_knight_moves(rank, file, board, &move_list);
                break;
            // Deal with bishop case
            case (3):
                generate_bishop_moves(rank, file, board, &move_list);
                break;
            // Deal with rook case
            case (4):
                generate_rook_moves(rank, file, board, &move_list);
                break;
            // Deal with queen case
            case (5):
                generate_bishop_moves(rank, file, board, &move_list);
                generate_rook_moves(rank, file, board, &move_list);
                break;
            // Deal with king case
            case (6):
                generate_king_moves(rank, file, board, &move_list);
                break;
            default:
                break; /* Intentionally unhandled */
            }
        }
    }

    return move_list;
}

static void generate_pawn_moves(int rank, int file, Board board, MoveList* move_list)
{
    // TODO: Deal with promotion
    Piece piece = board.grid[rank][file];
    int rank_idx = rank + (int)piece;
    Move temp_move;

    if (rank_idx < 0 || rank_idx >= 8)
        return;

    // Take with pawns
    if ((file - 1 >= 0) && ((board.grid[rank_idx][file - 1] * piece) < 0)) {
        temp_move = (Move) { rank, file, rank_idx, file - 1 };
        move_list->moves[move_list->count++] = temp_move;
    }
    if (((file + 1) < 8) && ((board.grid[rank_idx][file + 1] * piece) < 0)) {
        temp_move = (Move) { rank, file, rank_idx, file + 1 };
        move_list->moves[move_list->count++] = temp_move;
    }

    // Take en passant
    if (board.ep_rank != -1) {
        if ((rank_idx == board.ep_rank) && ((file - 1) == board.ep_file)) {
            temp_move = (Move) { rank, file, board.ep_rank, board.ep_file };
            move_list->moves[move_list->count++] = temp_move;
        }
        if ((rank_idx == board.ep_rank) && ((file + 1) == board.ep_file)) {
            temp_move = (Move) { rank, file, board.ep_rank, board.ep_file };
            move_list->moves[move_list->count++] = temp_move;
        }
    }

    // Push pawns
    if (board.grid[rank_idx][file] == EMPTY) {
        temp_move = (Move) { rank, file, rank_idx, file };
        move_list->moves[move_list->count++] = temp_move;

        // Double push only from starting rank, and only if single push wasn't blocked
        if (rank == (piece > 0 ? 1 : 6)) {
            rank_idx = rank + ((int)piece * 2);
            if (board.grid[rank_idx][file] == EMPTY) {
                temp_move = (Move) { rank, file, rank_idx, file };
                move_list->moves[move_list->count++] = temp_move;
            }
        }
    }
}

static void generate_knight_moves(int rank, int file, Board board, MoveList* move_list)
{
    Move temp_move;

    for (int rank_idx = rank - 2; rank_idx <= rank + 2; rank_idx++) {
        if (rank_idx < 0 || rank_idx > 7)
            continue;
        if (rank_idx == rank)
            continue;

        for (int file_idx = file - 2; file_idx <= file + 2; file_idx++) {
            if (file_idx < 0 || file_idx > 7)
                continue;
            if (abs(rank_idx - rank) == abs(file_idx - file))
                continue;
            if (file_idx == file)
                continue;
            if ((board.grid[rank_idx][file_idx] * board.grid[rank][file]) <= 0) {
                temp_move = (Move) { rank, file, rank_idx, file_idx };
                move_list->moves[move_list->count++] = temp_move;
            }
        }
    }
}

static void generate_bishop_moves(int rank, int file, Board board, MoveList* move_list)
{
    int rank_idx = rank + 1;
    int file_idx = file + 1;
    Move temp_move;

    while (rank_idx < 8 && file_idx < 8 && (board.grid[rank_idx][file_idx] * board.turn) <= 0) {
        temp_move = (Move) { rank, file, rank_idx, file_idx };
        move_list->moves[move_list->count++] = temp_move;
        if (board.grid[rank_idx][file_idx] != EMPTY)
            break;
        rank_idx++;
        file_idx++;
    }

    rank_idx = rank + 1;
    file_idx = file - 1;
    while (rank_idx < 8 && file_idx >= 0 && (board.grid[rank_idx][file_idx] * board.turn) <= 0) {
        temp_move = (Move) { rank, file, rank_idx, file_idx };
        move_list->moves[move_list->count++] = temp_move;
        if (board.grid[rank_idx][file_idx] != EMPTY)
            break;
        rank_idx++;
        file_idx--;
    }

    rank_idx = rank - 1;
    file_idx = file + 1;
    while (rank_idx >= 0 && file_idx < 8 && (board.grid[rank_idx][file_idx] * board.turn) <= 0) {
        temp_move = (Move) { rank, file, rank_idx, file_idx };
        move_list->moves[move_list->count++] = temp_move;
        if (board.grid[rank_idx][file_idx] != EMPTY)
            break;
        rank_idx--;
        file_idx++;
    }

    rank_idx = rank - 1;
    file_idx = file - 1;
    while (rank_idx >= 0 && file_idx >= 0 && (board.grid[rank_idx][file_idx] * board.turn) <= 0) {
        temp_move = (Move) { rank, file, rank_idx, file_idx };
        move_list->moves[move_list->count++] = temp_move;
        if (board.grid[rank_idx][file_idx] != EMPTY)
            break;
        rank_idx--;
        file_idx--;
    }
}

static void generate_rook_moves(int rank, int file, Board board, MoveList* move_list)
{
    int file_idx = file + 1;
    Move temp_move;

    while (file_idx < 8 && (board.grid[rank][file_idx] * board.turn) <= 0) {
        temp_move = (Move) { rank, file, rank, file_idx };
        move_list->moves[move_list->count++] = temp_move;
        if (board.grid[rank][file_idx] != EMPTY)
            break;
        file_idx++;
    }

    file_idx = file - 1;
    while (file_idx >= 0 && (board.grid[rank][file_idx] * board.turn) <= 0) {
        temp_move = (Move) { rank, file, rank, file_idx };
        move_list->moves[move_list->count++] = temp_move;
        if (board.grid[rank][file_idx] != EMPTY)
            break;
        file_idx--;
    }

    int rank_idx = rank + 1;
    while (rank_idx < 8 && (board.grid[rank_idx][file] * board.turn) <= 0) {
        temp_move = (Move) { rank, file, rank_idx, file };
        move_list->moves[move_list->count++] = temp_move;
        if (board.grid[rank_idx][file] != EMPTY)
            break;
        rank_idx++;
    }

    rank_idx = rank - 1;
    while (rank_idx >= 0 && (board.grid[rank_idx][file] * board.turn) <= 0) {
        temp_move = (Move) { rank, file, rank_idx, file };
        move_list->moves[move_list->count++] = temp_move;
        if (board.grid[rank_idx][file] != EMPTY)
            break;
        rank_idx--;
    }
}

static void generate_king_moves(int rank, int file, Board board, MoveList* move_list)
{
    Move temp_move;

    for (int rank_idx = rank - 1; rank_idx <= rank + 1; rank_idx++) {
        if (rank_idx < 0 || rank_idx > 7)
            continue;
        for (int file_idx = file - 1; file_idx <= file + 1; file_idx++) {
            if (file_idx < 0 || file_idx > 7)
                continue;
            if (file_idx == file && rank_idx == rank)
                continue;
            if ((board.grid[rank_idx][file_idx] * board.grid[rank][file]) <= 0) {
                temp_move = (Move) { rank, file, rank_idx, file_idx };
                move_list->moves[move_list->count++] = temp_move;
            }
        }
    }
}