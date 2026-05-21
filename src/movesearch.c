#include <limits.h>

#include "eval.h"
#include "move.h"
#include "movegen.h"

static int alphabeta(Board* board, int depth, int alpha, int beta);

Move get_best_move(Board* board, int depth) {
  MoveList move_list = generate_legal_moves(*board);
  if (!move_list.count) return (Move){0};
  int best;
  int best_idx;
  int alpha = INT_MIN;
  int beta = INT_MAX;

  if (board->turn == TURN_WHITE) {
    best = INT_MIN;
    for (int i = 0; i < move_list.count; i++) {
      Piece piece_taken = make_move(board, move_list.moves[i]);
      int val = alphabeta(board, depth - 1, alpha, beta);
      if (val > best) {
        best = val;
        best_idx = i;
      }
      reverse_move(board, move_list.moves[i], piece_taken);
      if (val >= beta) break;
      alpha = alpha > val ? alpha : val;
    }
  } else {
    best = INT_MAX;
    for (int i = 0; i < move_list.count; i++) {
      Piece piece_taken = make_move(board, move_list.moves[i]);
      int val = alphabeta(board, depth - 1, alpha, beta);
      if (val < best) {
        best = val;
        best_idx = i;
      }
      reverse_move(board, move_list.moves[i], piece_taken);
      if (val <= alpha) break;
      beta = beta < val ? beta : val;
    }
  }

  return move_list.moves[best_idx];
}

static int alphabeta(Board* board, int depth, int alpha, int beta) {
  if (depth == 0) return eval_material(board);

  MoveList move_list = generate_legal_moves(*board);

  if (board->turn == TURN_WHITE) {
    int best = INT_MIN;
    for (int i = 0; i < move_list.count; i++) {
      Piece piece_taken = make_move(board, move_list.moves[i]);
      int val = alphabeta(board, depth - 1, alpha, beta);
      reverse_move(board, move_list.moves[i], piece_taken);
      if (val > best) best = val;
      if (val >= beta) break;
      alpha = alpha > val ? alpha : val;
    }
    return best;
  } else {
    int best = INT_MAX;
    for (int i = 0; i < move_list.count; i++) {
      Piece piece_taken = make_move(board, move_list.moves[i]);
      int val = alphabeta(board, depth - 1, alpha, beta);
      reverse_move(board, move_list.moves[i], piece_taken);
      if (val < best) best = val;
      if (val <= alpha) break;
      beta = beta < val ? beta : val;
    }
    return best;
  }
}