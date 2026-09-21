#include "bench.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "fen.h"
#include "movesearch.h"
#include "perft.h"

#define BENCH_PERFT_ITERS 10

// Benchmark positions taken from Stockfish
static const char* bench_fens[] = {
    // --- opening / early middlegame ---
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
    "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 10",

    // --- middlegame ---
    "4rrk1/pp1n3p/3q2pQ/2p1pb2/2PP4/2P3N1/P2B2PP/4RRK1 b - - 7 19",
    "r3r1k1/2p2ppp/p1p1bn2/8/1q2P3/2NPQN2/PPP3PP/R4RK1 b - - 2 15",
    "r1bq1rk1/ppp1nppp/4n3/3p3Q/3P4/1BP1B3/PP1N2PP/R4RK1 w - - 1 16",
    "2rqkb1r/ppp2p2/2npb1p1/1N1Nn2p/2P1PP2/8/PP2B1PP/R1BQK2R b KQ - 0 11",
    "3r1rk1/p5pp/bpp1pp2/8/q1PP1P2/b3P3/P2NQRPP/1R2B1K1 b - - 6 22",
    "r3k2r/3nnpbp/q2pp1p1/p7/Pp1PPPP1/4BNN1/1P5P/R2Q1RK1 w kq - 0 16",

    // --- tactical ---
    "4rrk1/1p1nq3/p7/2p1P1pp/3P2bp/3Q1Bn1/PPPB4/1K2R1NR w - - 40 21",
    "4k3/3q1r2/1N2r1b1/3ppN2/2nPP3/1B1R2n1/2R1Q3/3K4 w - - 5 1",

    // --- endgame ---
    "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 11",
    "8/2p5/8/2kPKp1p/2p4P/2P5/3P4/8 w - - 0 1",
    "8/pp2r1k1/2p1p3/3pP2p/1P1P1P1P/P5KR/8/8 w - - 0 1",
    "6k1/6p1/P6p/r1N5/5p2/7P/1b3PP1/4R1K1 w - - 0 1",
};

#define NUM_BENCH_FENS (sizeof(bench_fens) / sizeof(*bench_fens))

static int64_t elapsed_ns(struct timespec* begin, struct timespec* end) {
  return (int64_t)(end->tv_sec - begin->tv_sec) * INT64_C(1000000000) +
         (int64_t)(end->tv_nsec - begin->tv_nsec);
}

void bench(int depth) {
  struct timespec begin, end;
  uint64_t nodecount = 0;
  int64_t totaltime_ns = 0;

  for (int i = 0; i < NUM_BENCH_FENS; i++) {
    Board board = fen_to_board(bench_fens[i]);
    Move bestmove;

    clock_gettime(CLOCK_MONOTONIC, &begin);
    iddfs(&board, &bestmove, depth);
    clock_gettime(CLOCK_MONOTONIC, &end);

    totaltime_ns += elapsed_ns(&begin, &end);
    nodecount += get_nodecount();
  }

  double totaltime_ms = totaltime_ns / 1e6;
  printf("\n================================\n");
  printf("Depth: %i\n", depth);
  printf("Total nodes: %" PRIu64 "\n", nodecount);
  printf("Total time: %.0f ms\n", totaltime_ms);
  printf("Nodes per second: %.0f\n",
         totaltime_ms == 0 ? 0 : nodecount / totaltime_ms * 1000);
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
  printf("Best: %" PRIu64 " nodes searched in %.0fms: %.0f knps\n", leafnodes,
         ms, knps);
}
