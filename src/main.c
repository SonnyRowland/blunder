#include "board.h"
#include "display.h"
#include "fen.h"
#include "move.h"

#include <stdio.h>

int main(void)
{
    Board board = fen_to_board("8/8/8/8/8/8/7Q/6k1 b - - 0 1");

    printf("is in check? %i\n", is_in_check(board));
}