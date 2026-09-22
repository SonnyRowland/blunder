#ifndef BENCH_H
#define BENCH_H

#include "board.h"

#define BENCH_DEFAULT_DEPTH 5

void bench(void);
void bench_perft(Board* board, int depth);

#endif