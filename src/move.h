#ifndef MOVE_H
#define MOVE_H

#include "board.h"

typedef struct {
  int from_rank, from_file;
  int to_rank, to_file;
} Move;

Board apply_move(Board board, Move move);

#endif