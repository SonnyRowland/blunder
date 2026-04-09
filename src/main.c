#include "board.h"
#include "display.h"
#include "fen.h"
#include "move.h"

#include <stdio.h>

int main(void)
{
    Board board = fen_to_board("7P/2R5/8/4b3/5N2/8/1Q6/8 b - - 0 1");
    MoveList move_list = generate_legal_moves(board);

    print_grid(board);
    print_movelist(move_list);
}