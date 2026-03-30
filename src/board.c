#include "board.h"
#include "fen.h"

Board get_start_pos()
{
    return fen_to_board(start_pos);
}