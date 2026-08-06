#ifndef FEN_H
#define FEN_H

#include "board.h"

extern const char start_pos[];
extern const Piece fen_to_piece[128];
extern const char piece_to_fen[13];

void board_to_fen(Board board, char* fen);
Board fen_to_board(const char* fen);

#endif