#include "movegen.h"

#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "move.h"

static void generate_pawn_moves(int rank, int file, Board* board,
                                MoveList* move_list);
static void generate_knight_moves(int rank, int file, Board* board,
                                  MoveList* move_list);
static void generate_bishop_moves(int rank, int file, Board* board,
                                  MoveList* move_list);
static void generate_rook_moves(int rank, int file, Board* board,
                                MoveList* move_list);
static void generate_king_moves(int rank, int file, Board* board,
                                MoveList* move_list);
static void generate_castling_moves(int rank, int file, Board* board,
                                    MoveList* move_list);
static void generate_promotion_moves(int rank, int file, Board* board,
                                     MoveList* move_list);
static void add_move_if_legal(MoveList* move_list, Board* board, Move move);

MoveList generate_legal_moves(Board* board) {
  MoveList move_list = {.count = 0};

  for (int rank = 0; rank < 8; rank++) {
    for (int file = 0; file < 8; file++) {
      Piece piece = board->grid[rank][file];

      if ((piece * board->turn) <= 0) continue;

      // Process white and black pieces in same switch statement
      int piece_abs = abs((int)piece);

      switch (piece_abs) {
        // Deal with pawn case
        case (1): {
          if ((rank == 1 && board->turn == -1) ||
              (rank == 6 && board->turn == 1)) {
            generate_promotion_moves(rank, file, board, &move_list);
          } else {
            generate_pawn_moves(rank, file, board, &move_list);
          }
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
          generate_castling_moves(rank, file, board, &move_list);
          break;
        default:
          break; /* Intentionally unhandled */
      }
    }
  }

  return move_list;
}

static void generate_pawn_moves(int rank, int file, Board* board,
                                MoveList* move_list) {
  Piece piece = board->grid[rank][file];
  int rank_idx = rank + (int)piece;
  if (rank_idx < 0 || rank_idx >= 8) return;

  Move temp_move;

  // Take with pawns
  if ((file - 1 >= 0) && ((board->grid[rank_idx][file - 1] * piece) < 0)) {
    temp_move = (Move){rank, file, rank_idx, file - 1};
    add_move_if_legal(move_list, board, temp_move);
  }
  if (((file + 1) < 8) && ((board->grid[rank_idx][file + 1] * piece) < 0)) {
    temp_move = (Move){rank, file, rank_idx, file + 1};
    add_move_if_legal(move_list, board, temp_move);
  }

  // Take en passant
  if (board->ep_rank != -1) {
    if ((rank_idx == board->ep_rank) && ((file - 1) == board->ep_file)) {
      temp_move = (Move){rank, file, board->ep_rank, board->ep_file};
      add_move_if_legal(move_list, board, temp_move);
    }
    if ((rank_idx == board->ep_rank) && ((file + 1) == board->ep_file)) {
      temp_move = (Move){rank, file, board->ep_rank, board->ep_file};
      add_move_if_legal(move_list, board, temp_move);
    }
  }

  // Push pawns
  if (board->grid[rank_idx][file] == EMPTY) {
    temp_move = (Move){rank, file, rank_idx, file};
    add_move_if_legal(move_list, board, temp_move);

    // Double push only from starting rank, and only if single push wasn't
    // blocked
    if (rank == (piece > 0 ? 1 : 6)) {
      rank_idx = rank + ((int)piece * 2);
      if (board->grid[rank_idx][file] == EMPTY) {
        temp_move = (Move){rank, file, rank_idx, file};
        add_move_if_legal(move_list, board, temp_move);
      }
    }
  }
}

static void generate_knight_moves(int rank, int file, Board* board,
                                  MoveList* move_list) {
  Move temp_move;

  for (int rank_idx = rank - 2; rank_idx <= rank + 2; rank_idx++) {
    if (rank_idx < 0 || rank_idx > 7) continue;
    if (rank_idx == rank) continue;

    for (int file_idx = file - 2; file_idx <= file + 2; file_idx++) {
      if (file_idx < 0 || file_idx > 7) continue;
      if (abs(rank_idx - rank) == abs(file_idx - file)) continue;
      if (file_idx == file) continue;
      if ((board->grid[rank_idx][file_idx] * board->grid[rank][file]) <= 0) {
        temp_move = (Move){rank, file, rank_idx, file_idx};
        add_move_if_legal(move_list, board, temp_move);
      }
    }
  }
}

static void generate_bishop_moves(int rank, int file, Board* board,
                                  MoveList* move_list) {
  int rank_idx = rank + 1;
  int file_idx = file + 1;
  Move temp_move;

  while (rank_idx < 8 && file_idx < 8 &&
         (board->grid[rank_idx][file_idx] * board->turn) <= 0) {
    temp_move = (Move){rank, file, rank_idx, file_idx};
    add_move_if_legal(move_list, board, temp_move);
    if (board->grid[rank_idx][file_idx] != EMPTY) break;
    rank_idx++;
    file_idx++;
  }

  rank_idx = rank + 1;
  file_idx = file - 1;
  while (rank_idx < 8 && file_idx >= 0 &&
         (board->grid[rank_idx][file_idx] * board->turn) <= 0) {
    temp_move = (Move){rank, file, rank_idx, file_idx};
    add_move_if_legal(move_list, board, temp_move);
    if (board->grid[rank_idx][file_idx] != EMPTY) break;
    rank_idx++;
    file_idx--;
  }

  rank_idx = rank - 1;
  file_idx = file + 1;
  while (rank_idx >= 0 && file_idx < 8 &&
         (board->grid[rank_idx][file_idx] * board->turn) <= 0) {
    temp_move = (Move){rank, file, rank_idx, file_idx};
    add_move_if_legal(move_list, board, temp_move);
    if (board->grid[rank_idx][file_idx] != EMPTY) break;
    rank_idx--;
    file_idx++;
  }

  rank_idx = rank - 1;
  file_idx = file - 1;
  while (rank_idx >= 0 && file_idx >= 0 &&
         (board->grid[rank_idx][file_idx] * board->turn) <= 0) {
    temp_move = (Move){rank, file, rank_idx, file_idx};
    add_move_if_legal(move_list, board, temp_move);
    if (board->grid[rank_idx][file_idx] != EMPTY) break;
    rank_idx--;
    file_idx--;
  }
}

static void generate_rook_moves(int rank, int file, Board* board,
                                MoveList* move_list) {
  int file_idx = file + 1;
  Move temp_move;

  while (file_idx < 8 && (board->grid[rank][file_idx] * board->turn) <= 0) {
    temp_move = (Move){rank, file, rank, file_idx};
    add_move_if_legal(move_list, board, temp_move);
    if (board->grid[rank][file_idx] != EMPTY) break;
    file_idx++;
  }

  file_idx = file - 1;
  while (file_idx >= 0 && (board->grid[rank][file_idx] * board->turn) <= 0) {
    temp_move = (Move){rank, file, rank, file_idx};
    add_move_if_legal(move_list, board, temp_move);
    if (board->grid[rank][file_idx] != EMPTY) break;
    file_idx--;
  }

  int rank_idx = rank + 1;
  while (rank_idx < 8 && (board->grid[rank_idx][file] * board->turn) <= 0) {
    temp_move = (Move){rank, file, rank_idx, file};
    add_move_if_legal(move_list, board, temp_move);
    if (board->grid[rank_idx][file] != EMPTY) break;
    rank_idx++;
  }

  rank_idx = rank - 1;
  while (rank_idx >= 0 && (board->grid[rank_idx][file] * board->turn) <= 0) {
    temp_move = (Move){rank, file, rank_idx, file};
    add_move_if_legal(move_list, board, temp_move);
    if (board->grid[rank_idx][file] != EMPTY) break;
    rank_idx--;
  }
}

static void generate_king_moves(int rank, int file, Board* board,
                                MoveList* move_list) {
  Move temp_move;

  for (int rank_idx = rank - 1; rank_idx <= rank + 1; rank_idx++) {
    if (rank_idx < 0 || rank_idx > 7) continue;
    for (int file_idx = file - 1; file_idx <= file + 1; file_idx++) {
      if (file_idx < 0 || file_idx > 7) continue;
      if (file_idx == file && rank_idx == rank) continue;
      if ((board->grid[rank_idx][file_idx] * board->grid[rank][file]) <= 0) {
        temp_move = (Move){rank, file, rank_idx, file_idx};
        add_move_if_legal(move_list, board, temp_move);
      }
    }
  }
}

static void generate_castling_moves(int rank, int file, Board* board,
                                    MoveList* move_list) {
  // Prevent castle out of check
  if (is_in_check(*board)) return;

  bool can_castle_k = (board->turn == 1) ? board->castle_wk : board->castle_bk;
  bool can_castle_q = (board->turn == 1) ? board->castle_wq : board->castle_bq;

  bool move_through_check = false;
  // Ensure clear path between king and rook
  if (can_castle_k && board->grid[rank][file + 1] == EMPTY &&
      board->grid[rank][file + 2] == EMPTY &&
      board->grid[rank][file + 3] == W_ROOK * board->turn) {
    // Prevent castle through check
    Move temp_move1 = (Move){rank, file, rank, file + 1};
    Piece piece_taken1 = apply_move(board, temp_move1);
    if (is_in_check(*board)) {
      move_through_check = true;
    }

    Move temp_move2 = (Move){rank, file + 1, rank, file + 2};
    Piece piece_taken2 = apply_move(board, temp_move2);
    if (is_in_check(*board)) {
      move_through_check = true;
    }

    revert_move(board, temp_move2, piece_taken2);
    revert_move(board, temp_move1, piece_taken1);

    if (!move_through_check) {
      Move castling_move = (Move){rank, file, rank, file + 2};
      add_move_if_legal(move_list, board, castling_move);
    }
  }

  move_through_check = false;
  if (can_castle_q && board->grid[rank][file - 1] == EMPTY &&
      board->grid[rank][file - 2] == EMPTY &&
      board->grid[rank][file - 3] == EMPTY &&
      board->grid[rank][file - 4] == W_ROOK * board->turn) {
    Move temp_move1 = (Move){rank, file, rank, file - 1};
    Piece piece_taken1 = apply_move(board, temp_move1);
    if (is_in_check(*board)) {
      move_through_check = true;
    }

    Move temp_move2 = (Move){rank, file - 1, rank, file - 2};
    Piece piece_taken2 = apply_move(board, temp_move2);
    if (is_in_check(*board)) {
      move_through_check = true;
    }

    revert_move(board, temp_move2, piece_taken2);
    revert_move(board, temp_move1, piece_taken1);

    if (!move_through_check) {
      Move castling_move = (Move){rank, file, rank, file - 2};
      add_move_if_legal(move_list, board, castling_move);
    }
  }
}

static void generate_promotion_moves(int rank, int file, Board* board,
                                     MoveList* move_list) {
  Move temp_move;
  int rank_idx = rank + board->turn;

  for (int promo_piece = 2; promo_piece < 6; promo_piece++) {
    temp_move = (Move){rank, file, rank_idx, file, promo_piece * board->turn};
    if (board->grid[rank_idx][file] == EMPTY) {
      add_move_if_legal(move_list, board, temp_move);
    }

    if ((file - 1 >= 0) &&
        ((board->grid[rank_idx][file - 1] * board->turn) < 0)) {
      temp_move =
          (Move){rank, file, rank_idx, file - 1, promo_piece * board->turn};
      add_move_if_legal(move_list, board, temp_move);
    }
    if (((file + 1) < 8) &&
        ((board->grid[rank_idx][file + 1] * board->turn) < 0)) {
      temp_move =
          (Move){rank, file, rank_idx, file + 1, promo_piece * board->turn};
      add_move_if_legal(move_list, board, temp_move);
    }
  }
}

static void add_move_if_legal(MoveList* move_list, Board* board, Move move) {
  Piece piece_taken = apply_move(board, move);
  if (!is_in_check(*board)) {
    move_list->moves[move_list->count++] = move;
  }
  revert_move(board, move, piece_taken);
}
