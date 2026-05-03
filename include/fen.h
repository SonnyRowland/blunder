#ifndef FEN_H
#define FEN_H

#include "board.h"

extern char start_pos[];

void board_to_fen(Board board, char* fen);
Board fen_to_board(const char* fen);

#endif