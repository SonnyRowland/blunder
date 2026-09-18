#ifndef PERFT_H
#define PERFT_H

#include "board.h"

#include <stdbool.h>
#include <stdint.h>

uint64_t perft(Board* board, int depth, bool bulk);
void perft_divide(Board* board, int depth);

#endif