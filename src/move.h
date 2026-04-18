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

void apply_move(Board* board, Move move);
bool is_player_in_check(Board board);

#endif