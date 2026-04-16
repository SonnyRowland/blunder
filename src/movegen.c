#include "movegen.h"
#include "board.h"
#include "move.h"

#include <stdlib.h>

MoveList generate_legal_moves(Board board)
{

    MoveList move_list;
    int count = 0;

    for (int rank = 0; rank < 8; rank++) {
        for (int file = 0; file < 8; file++) {
            Piece piece = board.grid[rank][file];

            if ((piece * board.turn) < 0)
                continue;

            // Process white and black pieces in same switch statement
            int piece_abs = abs((int)piece);
            int rank_idx, file_idx;

            if (piece == EMPTY)
                continue;

            Move temp_move;

            switch (piece_abs) {
            // Deal with pawn case
            case (1): {
                // TODO: Deal with promotion
                rank_idx = rank + (int)piece;
                if (rank_idx < 0 || rank_idx >= 8)
                    break;

                // Take with pawns
                if (((board.grid[rank_idx][file - 1] * piece) < 0) && (file - 1 >= 0)) {
                    temp_move = (Move) { rank, file, rank_idx, file - 1 };
                    move_list.moves[count++] = temp_move;
                }
                if (((board.grid[rank_idx][file + 1] * piece) < 0) && (file + 1) < 8) {
                    temp_move = (Move) { rank, file, rank_idx, file + 1 };
                    move_list.moves[count++] = temp_move;
                }

                // Take en passant
                if (board.ep_rank != -1) {
                    if ((rank_idx == board.ep_rank) && ((file - 1) == board.ep_file)) {
                        temp_move = (Move) { rank, file, board.ep_rank, board.ep_file };
                        move_list.moves[count++] = temp_move;
                    }
                    if ((rank_idx == board.ep_rank) && ((file + 1) == board.ep_file)) {
                        temp_move = (Move) { rank, file, board.ep_rank, board.ep_file };
                        move_list.moves[count++] = temp_move;
                    }
                }

                // Push pawns
                if (rank_idx >= 0 && rank_idx < 8 && board.grid[rank_idx][file] == EMPTY) {
                    temp_move = (Move) { rank, file, rank_idx, file };
                    move_list.moves[count++] = temp_move;

                    // Double push only from starting rank, and only if single push wasn't blocked
                    if (rank == (piece > 0 ? 1 : 6)) {
                        rank_idx = rank + ((int)piece * 2);
                        if (board.grid[rank_idx][file] == EMPTY) {
                            temp_move = (Move) { rank, file, rank_idx, file };
                            move_list.moves[count++] = temp_move;
                        }
                    }
                }
                break;
            }
            // Deal with knight case
            case (2):
                for (rank_idx = rank - 2; rank_idx <= rank + 2; rank_idx++) {
                    if (rank_idx < 0 || rank_idx > 7)
                        continue;
                    if (rank_idx == rank)
                        continue;

                    for (file_idx = file - 2; file_idx <= file + 2; file_idx++) {
                        if (file_idx < 0 || file_idx > 7)
                            continue;
                        if (abs(rank_idx - rank) == abs(file_idx - file))
                            continue;
                        if (file_idx == file)
                            continue;
                        if ((board.grid[rank_idx][file_idx] * piece) <= 0) {
                            temp_move = (Move) { rank, file, rank_idx, file_idx };
                            move_list.moves[count++] = temp_move;
                        }
                    }
                }
                break;
            // Let queen case fall through to both bishop and rook cases
            case (5):
            // Deal with bishop case
            case (3):
                rank_idx = rank + 1;
                file_idx = file + 1;
                while (rank_idx < 8 && file_idx < 8 && (board.grid[rank_idx][file_idx] * board.turn) <= 0) {
                    temp_move = (Move) { rank, file, rank_idx, file_idx };
                    move_list.moves[count++] = temp_move;
                    if (board.grid[rank_idx][file_idx] != EMPTY)
                        break;
                    rank_idx++;
                    file_idx++;
                }
                rank_idx = rank + 1;
                file_idx = file - 1;
                while (rank_idx < 8 && file_idx >= 0 && (board.grid[rank_idx][file_idx] * board.turn) <= 0) {
                    temp_move = (Move) { rank, file, rank_idx, file_idx };
                    move_list.moves[count++] = temp_move;
                    if (board.grid[rank_idx][file_idx] != EMPTY)
                        break;
                    rank_idx++;
                    file_idx--;
                }
                rank_idx = rank - 1;
                file_idx = file + 1;
                while (rank_idx >= 0 && file_idx < 8 && (board.grid[rank_idx][file_idx] * board.turn) <= 0) {
                    temp_move = (Move) { rank, file, rank_idx, file_idx };
                    move_list.moves[count++] = temp_move;
                    if (board.grid[rank_idx][file_idx] != EMPTY)
                        break;
                    rank_idx--;
                    file_idx++;
                }
                rank_idx = rank - 1;
                file_idx = file - 1;
                while (rank_idx >= 0 && file_idx >= 0 && (board.grid[rank_idx][file_idx] * board.turn) <= 0) {
                    temp_move = (Move) { rank, file, rank_idx, file_idx };
                    move_list.moves[count++] = temp_move;
                    if (board.grid[rank_idx][file_idx] != EMPTY)
                        break;
                    rank_idx--;
                    file_idx--;
                }
            // Deal with rook case
            case (4):
                // Prevent bishop case from falling through, let queen case through
                if (piece_abs == 3)
                    break;
                file_idx = file + 1;
                while (file_idx < 8 && (board.grid[rank][file_idx] * board.turn) <= 0) {
                    temp_move = (Move) { rank, file, rank, file_idx };
                    move_list.moves[count++] = temp_move;
                    if (board.grid[rank][file_idx] != EMPTY)
                        break;
                    file_idx++;
                }
                file_idx = file - 1;
                while (file_idx >= 0 && (board.grid[rank][file_idx] * board.turn) <= 0) {
                    temp_move = (Move) { rank, file, rank, file_idx };
                    move_list.moves[count++] = temp_move;
                    if (board.grid[rank][file_idx] != EMPTY)
                        break;
                    file_idx--;
                }
                rank_idx = rank + 1;
                while (rank_idx < 8 && (board.grid[rank_idx][file] * board.turn) <= 0) {
                    temp_move = (Move) { rank, file, rank_idx, file };
                    move_list.moves[count++] = temp_move;
                    if (board.grid[rank_idx][file] != EMPTY)
                        break;
                    rank_idx++;
                }
                rank_idx = rank - 1;
                while (rank_idx >= 0 && (board.grid[rank_idx][file] * board.turn) <= 0) {
                    temp_move = (Move) { rank, file, rank_idx, file };
                    move_list.moves[count++] = temp_move;
                    if (board.grid[rank_idx][file] != EMPTY)
                        break;
                    rank_idx--;
                }
                break;
            // Deal with king case
            case (6):
                for (rank_idx = rank - 1; rank_idx <= rank + 1; rank_idx++) {
                    if (rank_idx < 0 || rank_idx > 7)
                        continue;
                    for (file_idx = file - 1; file_idx <= file + 1; file_idx++) {
                        if (file_idx < 0 || file_idx > 7)
                            continue;
                        if (file_idx == file && rank_idx == rank)
                            continue;
                        if ((board.grid[rank_idx][file_idx] * piece) <= 0) {
                            temp_move = (Move) { rank, file, rank_idx, file_idx };
                            move_list.moves[count++] = temp_move;
                        }
                    }
                }
                break;
            default:
                break; /* Intentionally unhandled */
            }
        }
    }

    move_list.count = count;
    return move_list;
}