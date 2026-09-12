#ifndef PERFT_H
#define PERFT_H

#include "board.h"

#include <stdint.h>

uint64_t perft(Board* board, int depth);

#endif