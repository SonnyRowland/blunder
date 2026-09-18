#include "bench.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "perft.h"

#define BENCH_PERFT_ITERS 10

static int64_t elapsed_ns(struct timespec* begin, struct timespec* end) {
  return (int64_t)(end->tv_sec - begin->tv_sec) * INT64_C(1000000000) +
         (int64_t)(end->tv_nsec - begin->tv_nsec);
}

void bench_perft(Board* board, int depth) {
  struct timespec begin;
  struct timespec end;

  int64_t best = INT64_MAX;
  uint64_t leafnodes = 0;

  for (int i = 0; i < BENCH_PERFT_ITERS; i++) {
    clock_gettime(CLOCK_MONOTONIC, &begin);
    leafnodes = perft(board, depth, true);
    clock_gettime(CLOCK_MONOTONIC, &end);

    int64_t ns = elapsed_ns(&begin, &end);
    if (ns < best) {
      best = ns;
    }
  }

  double ms = best / 1e6;
  double knps = ms == 0 ? 0 : leafnodes / ms;

  printf("Depth %i searched over %i iterations\n", depth, BENCH_PERFT_ITERS);
  printf("Best: %" PRIu64 " nodes searched in %.0lfms: %.0f knps\n", leafnodes,
         ms, knps);
}
