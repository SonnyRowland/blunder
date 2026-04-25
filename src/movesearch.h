#ifndef MOVESEARCH_H
#define MOVESEARCH_H

#include "board.h"
#include "move.h"

Move get_best_move(Board* board, int depth);

#endif