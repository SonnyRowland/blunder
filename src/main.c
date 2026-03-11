#include "board.h"
#include "display.h"
#include "fen.h"
#include "move.h"

#include <stdio.h>

int main(){
  Board board = fen_to_board("rnb1kbnr/pppp1ppp/8/4p3/4P2q/1P3N2/P1PP1PPP/RNBQKB1R b KQkq - 2 3");
  Move move = {
    3,7,3,4,
  };

  print_grid(board);

  board = apply_move(board, move);
  
  print_grid(board);

  return 0;
}