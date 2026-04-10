#include "board.h"
#include "display.h"
#include "fen.h"
#include "move.h"

#include <stdio.h>

int main(void)
{
    Board board = fen_to_board("2P1P3/1Pp1pP2/1p3p2/1P1n1P2/1pP1Pp2/2p1p3/8/8 b - - 0 1");

    MoveList move_list = generate_legal_moves(board);

    print_grid(board);
    print_movelist(move_list);
}