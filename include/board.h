#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

typedef enum {
  B_KING = -6, B_QUEEN = -5, B_ROOK = -4, 
  B_BISHOP = -3, B_KNIGHT = -2, B_PAWN = -1, 
  EMPTY = 0,
  W_PAWN = 1, W_KNIGHT = 2, W_BISHOP = 3,
  W_ROOK = 4, W_QUEEN = 5, W_KING = 6
} Piece;

typedef enum {
  TURN_WHITE = 1,
  TURN_BLACK = -1
} Turn;

typedef struct {
  Piece grid[8][8];
  Turn turn;
  int castle_wk; // 1 = white can castle kingside
  int castle_wq; // 1 = white can castle queenside
  int castle_bk;
  int castle_bq;
  int ep_file; // File where en passant available, -1 if none
  int ep_rank; 
  int halfmove_clock;
  int fullmove_count;
} Board;

Board get_start_pos(void);
bool is_in_check(Board board);
static inline int turn_sign(Turn t) { return (int) t; }
static inline void flip_turn(Turn* t) { *t *= -1; }

#endif