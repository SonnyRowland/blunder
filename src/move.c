#include "move.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "board.h"

Piece apply_move(Board* board, Move move) {
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
