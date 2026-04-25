#include <limits.h>

#include "eval.h"
#include "move.h"
#include "movegen.h"

static int minimax(Board* board, int depth);

Move get_best_move(Board* board, int depth) {
  MoveList move_list = generate_legal_moves(*board);
  if (!move_list.count) return (Move){0};
  int best;
  int best_idx;

  if (board->turn == 1) {
    best = INT_MIN;
    for (int i = 0; i < move_list.count; i++) {
      Piece piece_taken = apply_move(board, move_list.moves[i]);
      int val = minimax(board, depth - 1);
      if (val > best) {
        best = val;
        best_idx = i;
      }
      reverse_move(board, move_list.moves[i], piece_taken);
    }
  } else {
    best = INT_MAX;
    for (int i = 0; i < move_list.count; i++) {
      Piece piece_taken = apply_move(board, move_list.moves[i]);
      int val = minimax(board, depth - 1);
      if (val < best) {
        best = val;
        best_idx = i;
      }
      reverse_move(board, move_list.moves[i], piece_taken);
    }
  }

  return move_list.moves[best_idx];
}

static int minimax(Board* board, int depth) {
  if (depth == 0) return eval_material(board);

  MoveList move_list = generate_legal_moves(*board);

  if (board->turn == 1) {
    int best = INT_MIN;
    for (int i = 0; i < move_list.count; i++) {
      Piece piece_taken = apply_move(board, move_list.moves[i]);
      int val = minimax(board, depth - 1);
      reverse_move(board, move_list.moves[i], piece_taken);
      if (val > best) best = val;
    }
    return best;
  } else {
    int best = INT_MAX;
    for (int i = 0; i < move_list.count; i++) {
      Piece piece_taken = apply_move(board, move_list.moves[i]);
      int val = minimax(board, depth - 1);
      reverse_move(board, move_list.moves[i], piece_taken);
      if (val < best) best = val;
    }
    return best;
  }
}