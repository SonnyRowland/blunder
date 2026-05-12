#include "move.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "fen.h"

Piece make_move(Board* board, Move move) {
  Piece piece = board->grid[move.from_rank][move.from_file];
  Piece piece_taken = board->grid[move.to_rank][move.to_file];
  board->grid[move.to_rank][move.to_file] = piece;
  board->grid[move.from_rank][move.from_file] = EMPTY;

  bool is_castle =
      (abs(piece) == W_KING) && (abs(move.from_file - move.to_file) == 2);
  bool is_ep = ((board->ep_rank == move.to_rank) &&
                (board->ep_file == move.to_file) && (piece == board->turn));

  if (is_ep) {
    board->grid[move.to_rank + (-1 * board->turn)][move.to_file] = EMPTY;
  }

  if (is_castle) {
    if (move.to_file - move.from_file > 0) {
      board->grid[move.to_rank][move.to_file - 1] = W_ROOK * board->turn;
      board->grid[move.to_rank][7] = EMPTY;
    } else {
      board->grid[move.to_rank][move.to_file + 1] = W_ROOK * board->turn;
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
    if (board->turn == 1) {
      board->castle_wk = 0;
      board->castle_wq = 0;
    } else {
      board->castle_bk = 0;
      board->castle_bq = 0;
    }
  } else {
    if (piece == W_ROOK && board->turn == 1 && move.from_rank == 0) {
      if (move.from_file == 0)
        board->castle_wq = 0;
      else if (move.from_file == 7)
        board->castle_wk = 0;
    } else if (piece == B_ROOK && board->turn == -1 && move.from_rank == 7) {
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

  board->ep_rank = is_double_push ? move.from_rank + board->turn : -1;
  board->ep_file = is_double_push ? move.from_file : -1;

  // Update move clock metadata
  if (halfmove_reset)
    board->halfmove_clock = 0;
  else
    board->halfmove_clock++;

  if (board->turn == -1) board->fullmove_count++;

  board->turn *= -1;
}

void reverse_move(Board* board, Move move, Piece piece_taken) {
  Piece piece = board->grid[move.to_rank][move.to_file];
  board->grid[move.from_rank][move.from_file] = piece;
  board->grid[move.to_rank][move.to_file] = piece_taken;

  if (move.promotion) {
    board->grid[move.from_rank][move.from_file] = W_PAWN * board->turn;
    return;
  }

  bool is_castle =
      (abs(board->grid[move.from_rank][move.from_file]) == W_KING) &&
      (abs(move.to_file - move.from_file) == 2);
  bool is_ep = ((board->ep_rank == move.to_rank) &&
                (board->ep_file == move.to_file) && (piece == board->turn));

  if (is_castle) {
    if (move.to_file - move.from_file > 0) {
      board->grid[move.to_rank][move.to_file - 1] = EMPTY;
      board->grid[move.to_rank][7] = W_ROOK * board->turn;
    } else {
      board->grid[move.to_rank][move.to_file + 1] = EMPTY;
      board->grid[move.to_rank][0] = W_ROOK * board->turn;
    }
  }

  if (is_ep) {
    board->grid[move.to_rank + (-1 * board->turn)][move.to_file] = -board->turn;
    board->grid[move.to_rank][move.to_file] = piece_taken;
  }
}

Move move_from_lan(const char* lan) {
  Move move;

  move.from_rank = (int)(lan[1] - '1');
  move.from_file = (int)(lan[0] - 'a');
  move.to_rank = (int)(lan[3] - '1');
  move.to_file = (int)(lan[2] - 'a');
  move.promotion = 0;

  if (strlen(lan) == 5) {
    move.promotion = fen_to_piece[lan[4]];

    if (move.to_rank == 7) move.promotion *= -1;
  }

  return move;
}