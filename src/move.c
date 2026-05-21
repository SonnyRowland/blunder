#include "move.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "board.h"

Piece make_move(Board* board, Move move) {
  Piece piece = board->grid[move.from_rank][move.from_file];
  Piece piece_taken = board->grid[move.to_rank][move.to_file];
  board->grid[move.to_rank][move.to_file] = piece;
  board->grid[move.from_rank][move.from_file] = EMPTY;

  bool is_castle =
      (abs(piece) == W_KING) && (abs(move.from_file - move.to_file) == 2);
  bool is_ep =
      ((board->ep_rank == move.to_rank) && (board->ep_file == move.to_file) &&
       (piece == (Piece)turn_sign(board->turn)));

  if (is_ep) {
    board->grid[move.to_rank + (-1 * turn_sign(board->turn))][move.to_file] =
        EMPTY;
  }

  if (is_castle) {
    if (move.to_file - move.from_file > 0) {
      board->grid[move.to_rank][move.to_file - 1] =
          (Piece)W_ROOK * turn_sign(board->turn);
      board->grid[move.to_rank][7] = EMPTY;
    } else {
      board->grid[move.to_rank][move.to_file + 1] =
          (Piece)W_ROOK * turn_sign(board->turn);
      board->grid[move.to_rank][0] = EMPTY;
    }
  }

  if (move.promotion) board->grid[move.to_rank][move.to_file] = move.promotion;

  return piece_taken;
}

// Use make_move() then update game metadata
void commit_move(Board* board, Move move) {
  Piece piece = board->grid[move.from_rank][move.from_file];
  bool halfmove_reset =
      board->grid[move.to_rank][move.to_file] != EMPTY || abs(piece) == W_PAWN;

  Piece piece_taken = make_move(board, move);

  // Update castling rights game metadata
  bool is_castle =
      (abs(piece) == W_KING) && (abs(move.from_file - move.to_file) == 2);

  if (is_castle) {
    if (board->turn == TURN_WHITE) {
      board->castle_wk = 0;
      board->castle_wq = 0;
    } else {
      board->castle_bk = 0;
      board->castle_bq = 0;
    }
  } else {
    if (piece == W_ROOK && move.from_rank == 0) {
      if (move.from_file == 0)
        board->castle_wq = 0;
      else if (move.from_file == 7)
        board->castle_wk = 0;
    } else if (piece == B_ROOK && move.from_rank == 7) {
      if (move.from_file == 0) board->castle_bq = 0;
      if (move.from_file == 7) board->castle_bk = 0;
    } else if (piece == W_KING) {
      board->castle_wk = 0;
      board->castle_wq = 0;
    } else if (piece == B_KING) {
      board->castle_bk = 0;
      board->castle_bq = 0;
    }
  }

  // Update en passant metadata
  bool is_double_push =
      abs(piece) == W_PAWN && abs(move.from_rank - move.to_rank) == 2;

  board->ep_rank =
      is_double_push ? move.from_rank + turn_sign(board->turn) : -1;
  board->ep_file = is_double_push ? move.from_file : -1;

  // Update move clock metadata
  if (halfmove_reset)
    board->halfmove_clock = 0;
  else
    board->halfmove_clock++;

  if (board->turn == TURN_BLACK) board->fullmove_count++;

  flip_turn(&board->turn);
}

void reverse_move(Board* board, Move move, Piece piece_taken) {
  Piece piece = board->grid[move.to_rank][move.to_file];
  board->grid[move.from_rank][move.from_file] = piece;
  board->grid[move.to_rank][move.to_file] = piece_taken;

  if (move.promotion) {
    board->grid[move.from_rank][move.from_file] =
        (Piece)W_PAWN * turn_sign(board->turn);
    return;
  }

  bool is_castle =
      (abs(board->grid[move.from_rank][move.from_file]) == W_KING) &&
      (abs(move.to_file - move.from_file) == 2);
  bool is_ep =
      ((board->ep_rank == move.to_rank) && (board->ep_file == move.to_file) &&
       (piece == (Piece)turn_sign(board->turn)));

  if (is_castle) {
    if (move.to_file - move.from_file > 0) {
      board->grid[move.to_rank][move.to_file - 1] = EMPTY;
      board->grid[move.to_rank][7] = (Piece)W_ROOK * turn_sign(board->turn);
    } else {
      board->grid[move.to_rank][move.to_file + 1] = EMPTY;
      board->grid[move.to_rank][0] = (Piece)W_ROOK * turn_sign(board->turn);
    }
  }

  if (is_ep) {
    board->grid[move.to_rank + (-1 * turn_sign(board->turn))][move.to_file] =
        (Piece)(-turn_sign(board->turn));
    board->grid[move.to_rank][move.to_file] = piece_taken;
  }
}
