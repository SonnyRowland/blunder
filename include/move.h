#ifndef MOVE_H
#define MOVE_H

#include <stdbool.h>

#include "board.h"

typedef struct {
  int from_rank, from_file;
  int to_rank, to_file;
  int promotion;
} Move;

typedef struct {
  Move moves[256];
  int count;
} MoveList;

Piece make_move(Board* board, Move move);
void commit_move(Board* board, Move move);
void reverse_move(Board* board, Move move, Piece piece_taken);

#endif