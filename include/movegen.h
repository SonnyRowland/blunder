#ifndef MOVEGEN_H
#define MOVEGEN_H

#include "move.h"
#include "board.h"

MoveList generate_legal_moves(Board* board);
void score_moves(const MoveList* movelist, Board* board, int scores[256]);
Move pickmove(MoveList* movelist, int scores[256], int index);

#endif