#include "board.h"
#include "display.h"
#include "fen.h"
#include "move.h"

#include <stdio.h>

int main(){
  Board board = get_start_pos();
  print_grid(board);
}