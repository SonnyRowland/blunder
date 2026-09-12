#include "move.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "fen.h"

Piece apply_move(Board* board, Move move) {
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

void revert_move(Board* board, Move move, Piece piece_taken) {
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

void make_move(Board* board, Move move, Undo* undo) {
  undo->castle_wk = board->castle_wk;
  undo->castle_wq = board->castle_wq;
  undo->castle_bk = board->castle_bk;
  undo->castle_bq = board->castle_bq;
  undo->ep_rank = board->ep_rank;
  undo->ep_file = board->ep_file;
  undo->halfmove_clock = board->halfmove_clock;
  undo->fullmove_count = board->fullmove_count;

  Piece piece = board->grid[move.from_rank][move.from_file];
  bool halfmove_reset =
      board->grid[move.to_rank][move.to_file] != EMPTY || abs(piece) == W_PAWN;

  undo->piece_taken = apply_move(board, move);

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

  bool is_double_push =
      abs(piece) == W_PAWN && abs(move.from_rank - move.to_rank) == 2;

  board->ep_rank =
      is_double_push ? move.from_rank + turn_sign(board->turn) : -1;
  board->ep_file = is_double_push ? move.from_file : -1;

  if (halfmove_reset)
    board->halfmove_clock = 0;
  else
    board->halfmove_clock++;

  if (board->turn == TURN_BLACK) board->fullmove_count++;

  flip_turn(&board->turn);
}

void unmake_move(Board* board, Move move, const Undo* undo) {
  flip_turn(&board->turn);
  board->castle_wk = undo->castle_wk;
  board->castle_wq = undo->castle_wq;
  board->castle_bk = undo->castle_bk;
  board->castle_bq = undo->castle_bq;
  board->ep_rank = undo->ep_rank;
  board->ep_file = undo->ep_file;
  board->halfmove_clock = undo->halfmove_clock;
  board->fullmove_count = undo->fullmove_count;

  revert_move(board, move, undo->piece_taken);
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

void lan_from_move(Move move, char* lan) {
  lan[0] = (char)('a' + move.from_file);
  lan[1] = (char)('1' + move.from_rank);
  lan[2] = (char)('a' + move.to_file);
  lan[3] = (char)('1' + move.to_rank);
  lan[4] = move.promotion ? tolower(piece_to_fen[move.promotion + 6]) : '\0';
  lan[5] = '\0';
}
