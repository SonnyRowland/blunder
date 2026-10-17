#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "board.h"

const char start_pos[] =
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

const Piece char_to_piece[128] = {
    ['k'] = B_KING,   ['q'] = B_QUEEN, ['r'] = B_ROOK,  ['b'] = B_BISHOP,
    ['n'] = B_KNIGHT, ['p'] = B_PAWN,  ['P'] = W_PAWN,  ['N'] = W_KNIGHT,
    ['B'] = W_BISHOP, ['R'] = W_ROOK,  ['Q'] = W_QUEEN, ['K'] = W_KING,
};

// Offset by 6 for non negative array indexing
const char piece_to_fen[13] = {
    [B_KING + 6] = 'k',   [B_QUEEN + 6] = 'q',  [B_ROOK + 6] = 'r',
    [B_BISHOP + 6] = 'b', [B_KNIGHT + 6] = 'n', [B_PAWN + 6] = 'p',
    [EMPTY + 6] = '.',    [W_PAWN + 6] = 'P',   [W_KNIGHT + 6] = 'N',
    [W_BISHOP + 6] = 'B', [W_ROOK + 6] = 'R',   [W_QUEEN + 6] = 'Q',
    [W_KING + 6] = 'K',
};

Board fen_to_board(const char* fen) {
  const char* p = fen;
  Board board = {0};
  int rank = 7, file = 0;

  // Parse board
  for (; *p && *p != ' '; p++) {
    char c = *p;
    if (c == '/') {
      rank--;
      file = 0;
    } else if (c >= '1' && c <= '8') {
      int end = file + c - '0';
      for (; file < end; file++) {
        board.grid[rank][file] = EMPTY;
      }
    } else {
      board.grid[rank][file] = char_to_piece[(unsigned char)c];
      file++;
    }
  }

  // Parse game state
  char side, castling[5], ep[3];
  int halfmove, fullmove;

  sscanf(p, " %c %s %s %i %i", &side, castling, ep, &halfmove, &fullmove);

  board.turn = side == 'w' ? TURN_WHITE : TURN_BLACK;

  board.castle_wk = board.castle_wq = board.castle_bk = board.castle_bq = 0;

  for (const char* c = castling; *c != '\0'; c++) {
    switch (*c) {
      case 'K':
        board.castle_wk = 1;
        break;
      case 'Q':
        board.castle_wq = 1;
        break;
      case 'k':
        board.castle_bk = 1;
        break;
      case 'q':
        board.castle_bq = 1;
        break;
    }
  }

  board.ep_file = board.ep_rank = -1;

  if (strcmp(ep, "-") != 0) {
    board.ep_file = ep[0] - 'a';
    board.ep_rank = ep[1] - '1';
  }

  board.halfmove_clock = halfmove;
  board.fullmove_count = fullmove;

  return board;
}

void board_to_fen(Board board, char* fen) {
  int empty_counter = 0;
  int fen_pointer = 0;

  for (int i = 7; i >= 0; i--) {
    for (int j = 0; j < 8; j++) {
      // Flush empty_counter on first rank and write to FEN string
      if (j == 0 && i != 7) {
        if (empty_counter) {
          fen[fen_pointer++] = (char)('0' + empty_counter);
          empty_counter = 0;
        }
        fen[fen_pointer++] = '/';
      }

      if (board.grid[i][j] == EMPTY) {
        empty_counter++;
      } else {
        if (empty_counter) {
          fen[fen_pointer++] = (char)('0' + empty_counter);
          empty_counter = 0;
        }
        fen[fen_pointer++] = piece_to_fen[board.grid[i][j] + 6];
      }
    }
  }

  // Flush any remaining empty squares from the last rank
  if (empty_counter) {
    fen[fen_pointer++] = (char)('0' + empty_counter);
  }

  // Write game meta data to FEN string
  fen[fen_pointer++] = ' ';

  if (board.turn == 1) {
    fen[fen_pointer++] = 'w';
  } else {
    fen[fen_pointer++] = 'b';
  }

  fen[fen_pointer++] = ' ';

  bool no_castling_rights = true;

  if (board.castle_wk) {
    fen[fen_pointer++] = 'K';
    no_castling_rights = false;
  }
  if (board.castle_wq) {
    fen[fen_pointer++] = 'Q';
    no_castling_rights = false;
  }
  if (board.castle_bk) {
    fen[fen_pointer++] = 'k';
    no_castling_rights = false;
  }
  if (board.castle_bq) {
    fen[fen_pointer++] = 'q';
    no_castling_rights = false;
  }

  if (no_castling_rights) fen[fen_pointer++] = '-';

  fen[fen_pointer++] = ' ';

  if (board.ep_file == -1) {
    fen[fen_pointer++] = '-';
  } else {
    fen[fen_pointer++] = (char)(board.ep_file + 'a');
    fen[fen_pointer++] = (char)('1' + board.ep_rank);
  }

  fen[fen_pointer++] = ' ';

  fen_pointer += sprintf(&fen[fen_pointer], "%d", board.halfmove_clock);
  fen[fen_pointer++] = ' ';
  fen_pointer += sprintf(&fen[fen_pointer], "%d", board.fullmove_count);
  fen[fen_pointer++] = '\0';
}
