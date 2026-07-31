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

typedef struct {
  Piece piece_taken;
  int castle_wk, castle_wq, castle_bk, castle_bq;
  int ep_rank, ep_file;
  int halfmove_clock;
  int fullmove_count;
} Undo;

Piece apply_move(Board* board, Move move);
void revert_move(Board* board, Move move, Piece piece_taken);
void make_move(Board* board, Move move, Undo* undo);
void unmake_move(Board* board, Move move, const Undo* undo);
Move move_from_lan(const char* lan);

#endif
