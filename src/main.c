#include "board.h"
#include "display.h"
#include "fen.h"

#include <stdio.h>

int main()
{
    Board board = fen_to_board("r1bqkbnr/pppp1ppp/2n5/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R b KQkq - 3 3");
    print_grid(board);

    char fen[128];

    board_to_fen(board, fen);
    printf("%s\n", fen);
    return 0;
}