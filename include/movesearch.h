#ifndef MOVESEARCH_H
#define MOVESEARCH_H

#define MAX_PLY 64

#include "board.h"
#include "move.h"

void iddfs(Board* board, Move* bestmove, int max_depth);
uint64_t get_nodecount(void);

#endif