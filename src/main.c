#include "board.h"

#include <stdio.h>

int main(){
  Board board = fen_to_board("r1bqkbnr/pppp1ppp/2n5/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R b KQ - 3 3");
  print_grid(board);

  return 0;
}

