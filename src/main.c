#include "board.h"
#include "display.h"
#include "fen.h"
#include "move.h"

#include <stdio.h>

int main()
{
    Board board = fen_to_board("8/8/8/4n3/8/8/8/8 w - - 0 1");
    MoveList move_list = generate_legal_moves(board);

    print_grid(board);
    print_movelist(move_list);
}