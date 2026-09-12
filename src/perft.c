#include "perft.h"

#include "movegen.h"

uint64_t perft(Board* board, int depth) {
  if (depth == 0) return 1;

  uint64_t leafnodes = 0;

  MoveList movelist = generate_legal_moves(*board);

  for (int i = 0; i < movelist.count; i++) {
    Undo undo = (Undo){0};

    make_move(board, movelist.moves[i], &undo);
    leafnodes += perft(board, depth - 1);
    unmake_move(board, movelist.moves[i], &undo);
  }

  return leafnodes;
}