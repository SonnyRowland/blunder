#include <string.h>
#include <stdio.h>
#include <math.h>

#include "board.h"

static const Piece fen_to_piece[128] = {
  ['k'] = B_KING,
  ['q'] = B_QUEEN,
  ['r'] = B_ROOK,
  ['b'] = B_BISHOP,
  ['n'] = B_KNIGHT,
  ['p'] = B_PAWN,
  ['P'] = W_PAWN,
  ['N'] = W_KNIGHT,
  ['B'] = W_BISHOP,
  ['R'] = W_ROOK,
  ['Q'] = W_QUEEN,
  ['K'] = W_KING,
};

// Offset by 6 for non negative array indexing
static const char piece_to_fen[13] = {
    [B_KING   + 6] = 'k',
    [B_QUEEN  + 6] = 'q',
    [B_ROOK   + 6] = 'r',
    [B_BISHOP + 6] = 'b',
    [B_KNIGHT + 6] = 'n',
    [B_PAWN   + 6] = 'p',
    [EMPTY    + 6] = '.',
    [W_PAWN   + 6] = 'P',
    [W_KNIGHT + 6] = 'N',
    [W_BISHOP + 6] = 'B',
    [W_ROOK   + 6] = 'R',
    [W_QUEEN  + 6] = 'Q',
    [W_KING   + 6] = 'K',
};

Board fen_to_board(const char* fen){
  Board board;
  int fen_length = strlen(fen);

  int rank = 7;
  int file = 0;
  int emptySquares;
  int i = 0;

  // Fill grid with pieces
  for(; i < fen_length; i++)
  {
    if(fen[i] == ' ') break;

    if (fen[i] > 65)
    {
      board.grid[rank][file] = fen_to_piece[fen[i]];
      file++;
    }
    else if (47 < fen[i] && fen[i] < 65)
    {
      emptySquares = fen[i] - '0';

      for (int j = 0; j < emptySquares; j++)
      {
        board.grid[rank][file] = EMPTY;
        file++;
      }
    }
    else
    {
      rank--;
      file = 0;
    }
  }

  // Extract game meta data (turn, castling rights, move count etc.)
  board.turn = (fen[++i] == 'w');
  i++;

  board.castle_wk = board.castle_wq = board.castle_bk = board.castle_bq = 0;

  if (fen[i++] != '-')
  {
    while(fen[i] != ' ')
    {
      switch (fen[i])
      { 
        case 'K': board.castle_wk = 1; break;
        case 'Q': board.castle_wq = 1; break;
        case 'k': board.castle_bk = 1; break;
        case 'q': board.castle_bq = 1; break;
        default: break;
      }
      i++;
    }
  }

  // Google en passant
  if (fen[++i] != '-')
  {
    board.ep_file = fen[i] - 'a';
    board.ep_rank = fen[++i] - '0';
  }
  else
  {
    board.ep_file = board.ep_rank = -1;
  }

  i++;

  board.halfmove_clock = fen[++i] - '0';

  if (fen[++i] != ' ')
  {
    board.halfmove_clock = (10 * board.halfmove_clock) + (fen[i++] - '0');
  }

  i++;

  board.fullmove_count = 0;

  while (fen_length - i > 0)
  {
    board.fullmove_count += pow(10, fen_length - i - 1) * (fen[i] - '0');
    i++;
  }

  return board;
}

void board_to_fen(Board board, char* fen)
{
  int emptyCounter = 0;
  int fenPointer = 0;

  for (int i = 7; i >= 0; i--)
  {
    for (int j = 0; j < 8; j++)
    {
      // Flush emptyCounter on first rank and write to FEN string
      if (j == 0 && i != 7) 
      {
        if (emptyCounter)
        {
          fen[fenPointer++] = (char)('0' + emptyCounter);
          emptyCounter = 0;
        }
        fen[fenPointer++] = '/';
      }

      if (board.grid[i][j] == EMPTY)
      {
        emptyCounter++;
      }
      else
      {
        if(emptyCounter)
        {
          fen[fenPointer++] = (char)('0' + emptyCounter);
          emptyCounter = 0;
        }
        fen[fenPointer++] = piece_to_fen[board.grid[i][j] + 6];
      }
    }
  }

  // Write game meta data to FEN string
  fen[fenPointer++] = ' ';

  if (board.turn == 1)
  {
    fen[fenPointer++] = 'w';
  }
  else
  {
    fen[fenPointer++] = 'b';
  }

  fen[fenPointer++] = ' ';

  if (board.castle_wk) fen[fenPointer++] = 'K';
  if (board.castle_wq) fen[fenPointer++] = 'Q';
  if (board.castle_bk) fen[fenPointer++] = 'k';
  if (board.castle_bq) fen[fenPointer++] = 'q';

  fen[fenPointer++] = ' ';

  if (board.ep_file == -1)
  {
    fen[fenPointer++] = '-';
  }
  else
  {
    fen[fenPointer++] = (char)(board.ep_file + 'a');
    fen[fenPointer++] = (char)('0' + board.ep_rank);
  }

  fen[fenPointer++] = ' ';

  fenPointer += sprintf(&fen[fenPointer], "%d", board.halfmove_clock);
  fen[fenPointer++] = ' ';
  fenPointer += sprintf(&fen[fenPointer], "%d", board.fullmove_count);
  fen[fenPointer++] = '\0';
}