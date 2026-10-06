#include <limits.h>
#include <stdint.h>
#include <stdio.h>

#include "display.h"
#include "eval.h"
#include "move.h"
#include "movegen.h"
#include "timemanager.h"

static uint64_t nodecount = 0;

uint64_t get_nodecount(void) { return nodecount; }

static int alphabeta(Board* board, Move* bestmove, int depthlimit, int depth,
                     int alpha, int beta);

void iddfs(Board* board, Move* bestmove, int max_depth) {
  nodecount = 0;

  Move candidate;

  for (int depthlimit = 1; depthlimit <= max_depth && !stop_search;
       depthlimit++) {
    alphabeta(board, &candidate, depthlimit, depthlimit, INT_MIN, INT_MAX);
    if (!stop_search) *bestmove = candidate;
  }
}

static int alphabeta(Board* board, Move* bestmove, int depthlimit, int depth,
                     int alpha, int beta) {
  nodecount++;
  if (depth == 0 || stop_search) return eval_material(board);

  int scores[256];
  MoveList move_list = generate_legal_moves(board);
  score_moves(&move_list, board, scores);
  Undo undo;

  if (board->turn == TURN_WHITE) {
    int best = INT_MIN;
    for (int i = 0; i < move_list.count; i++) {
      Move move = pickmove(&move_list, scores, i);
      make_move(board, move, &undo);
      int val = alphabeta(board, bestmove, depthlimit, depth - 1, alpha, beta);
      unmake_move(board, move, &undo);
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
      Move move = pickmove(&move_list, scores, i);
      make_move(board, move, &undo);
      int val = alphabeta(board, bestmove, depthlimit, depth - 1, alpha, beta);
      unmake_move(board, move, &undo);
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
