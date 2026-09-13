#include <limits.h>
#include <stdio.h>

#include "display.h"
#include "eval.h"
#include "move.h"
#include "movegen.h"
#include "timemanager.h"

static int alphabeta(Board* board, Move* bestmove, int depthlimit, int depth,
                     int alpha, int beta);

void iddfs(Board* board, Move* bestmove) {
  int depthlimit = 1;

  Move candidate;

  while (!stop_search) {
    alphabeta(board, &candidate, depthlimit, depthlimit, INT_MIN, INT_MAX);
    if (!stop_search) *bestmove = candidate;
    depthlimit++;
  }
}

static int alphabeta(Board* board, Move* bestmove, int depthlimit, int depth,
                     int alpha, int beta) {
  if (depth == 0 || stop_search) return eval_material(board);

  MoveList move_list = generate_legal_moves(board);
  Undo undo;

  if (board->turn == TURN_WHITE) {
    int best = INT_MIN;
    for (int i = 0; i < move_list.count; i++) {
      make_move(board, move_list.moves[i], &undo);
      int val = alphabeta(board, bestmove, depthlimit, depth - 1, alpha, beta);
      unmake_move(board, move_list.moves[i], &undo);
      if (val > best) {
        best = val;
        if (depth == depthlimit) *bestmove = move_list.moves[i];
      }
      if (val >= beta) break;
      alpha = alpha > val ? alpha : val;
    }
    return best;
  } else {
    int best = INT_MAX;
    for (int i = 0; i < move_list.count; i++) {
      make_move(board, move_list.moves[i], &undo);
      int val = alphabeta(board, bestmove, depthlimit, depth - 1, alpha, beta);
      unmake_move(board, move_list.moves[i], &undo);
      if (val < best) {
        best = val;
        if (depth == depthlimit) *bestmove = move_list.moves[i];
      }
      if (val <= alpha) break;
      beta = beta < val ? beta : val;
    }
    return best;
  }
}
