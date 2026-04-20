#include <stdio.h>

#include "board.h"
#include "move.h"

static const char* piece_to_unicode(Piece p) {
  switch (p) {
    case W_KING:
      return "\u2654";
    case W_QUEEN:
      return "\u2655";
    case W_ROOK:
      return "\u2656";
    case W_BISHOP:
      return "\u2657";
    case W_KNIGHT:
      return "\u2658";
    case W_PAWN:
      return "\u2659";
    case B_KING:
      return "\u265A";
    case B_QUEEN:
      return "\u265B";
    case B_ROOK:
      return "\u265C";
    case B_BISHOP:
      return "\u265D";
    case B_KNIGHT:
      return "\u265E";
    case B_PAWN:
      return "\u265F";
    default:
      return " ";
  }
}

void print_grid(Board board) {
  for (int rank = 7; rank >= 0; rank--) {
    for (int file = 0; file < 8; file++) {
      if (board.grid[rank][file] == EMPTY) {
        printf(" ");
      } else {
        printf("%s", piece_to_unicode(board.grid[rank][file]));
      }
    }
    printf("\n");
  }
  printf("\n");
  if (board.turn == 1) {
    printf("White to play\n");
  } else {
    printf("Black to play\n");
  }
  if (board.castle_wk) printf("White can castle kingside\n");
  if (board.castle_wq) printf("White can castle queenside\n");
  if (board.castle_bk) printf("Black can castle kingside\n");
  if (board.castle_bq) printf("Black can castle queenside\n");
  if (board.ep_file != -1) {
    printf("En passant available on %c%i\n", ('a' + board.ep_file),
           board.ep_rank + 1);
  }
  printf("Halfmove clock: %i\n", board.halfmove_clock);
  printf("Fullmove count: %i\n", board.fullmove_count);
  printf("---------------------------\n");
}

void print_movelist(MoveList moveList) {
  for (int i = 0; i < moveList.count; i++) {
    printf("{%i, %i, %i, %i", moveList.moves[i].from_rank,
           moveList.moves[i].from_file, moveList.moves[i].to_rank,
           moveList.moves[i].to_file);

    if (moveList.moves[i].promotion) {
      printf(", %i", moveList.moves[i].promotion);
    }

    printf("}\n");
  }
}
