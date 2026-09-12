#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "display.h"
#include "fen.h"
#include "move.h"
#include "timemanager.h"

#define BUF_SIZE 512

// Functions to handle UCI commands
typedef void (*handler_fn)(char* args, FILE* out, Board* board, Move* bestmove);
static void handle_uci(char* args, FILE* out, Board* board, Move* bestmove);
static void handle_isready(char* args, FILE* out, Board* board, Move* bestmove);
static void handle_position(char* args, FILE* out, Board* board,
                            Move* bestmove);
static void handle_go(char* args, FILE* out, Board* board, Move* bestmove);
static void handle_stop(char* args, FILE* out, Board* board, Move* bestmove);
static void handle_quit(char* args, FILE* out, Board* board, Move* bestmove);

typedef struct {
  const char* cmd;
  handler_fn fn;
} Command;

const Command commands[] = {
    {"uci", handle_uci},           {"isready", handle_isready},
    {"position", handle_position}, {"go", handle_go},
    {"stop", handle_stop},         {"quit", handle_quit},
};

void dispatch(char* buf, FILE* out, Board* board, Move* bestmove) {
  char* tmp = buf;
  size_t cnt = 0;

  // Get command from buffer
  while (tmp[cnt] != ' ' && tmp[cnt] != '\n' && tmp[cnt] != '\0') cnt++;

  // Get arguments from buffer
  char* args = strchr(buf, ' ');
  if (args)
    while (*args == ' ') args++;

  for (int i = 0; i < sizeof(commands) / sizeof(Command); i++) {
    // TODO: Fix empty buf calling all handler funcs
    if (strncmp(buf, commands[i].cmd, cnt) == 0) {
      commands[i].fn(args, out, board, bestmove);
      break;
    }
  }
}

static void handle_uci(char* args, FILE* out, Board* board, Move* bestmove) {
  (void)args;
  (void)board;
  (void)bestmove;

  fprintf(out, "id name blunderbot\n");
  fprintf(out, "id author SonnyRowland\n");
  fprintf(out, "uciok\n");
}

static void handle_isready(char* args, FILE* out, Board* board,
                           Move* bestmove) {
  (void)args;
  (void)board;
  (void)bestmove;

  fprintf(out, "readyok\n");
}

static void handle_position(char* args, FILE* out, Board* board,
                            Move* bestmove) {
  (void)bestmove;

  if (args) {
    char* token = strtok(args, " \n");

    // Parse 'startpos' argument
    if (token && strcmp(token, "startpos") == 0) {
      *board = get_start_pos();
      token = strtok(NULL, " \n");

      // Apply moves specified to board
      if (token && strcmp(token, "moves") == 0) {
        token = strtok(NULL, " \n");
        while (token) {
          Undo undo;
          make_move(board, move_from_lan(token), &undo);
          token = strtok(NULL, " \n");
        }
      } else {
        *board = get_start_pos();
      }

      // Parse 'fen' argument
    } else if (token && strcmp(token, "fen") == 0) {
      // Tokenise fen string
      token = strtok(NULL, "m\n");
      token[strlen(token) - 1] = '\0';
      *board = fen_to_board(token);
      token = strtok(NULL, " \n");

      // Apply moves specified to board
      if (token && strcmp(token, "oves") == 0) {
        token = strtok(NULL, " \n");
        while (token) {
          Undo undo;
          make_move(board, move_from_lan(token), &undo);
          token = strtok(NULL, " \n");
        }
      }
    }
  }
}

static void handle_go(char* args, FILE* out, Board* board, Move* bestmove) {
  timemanager_go(board, args, bestmove, out);
}

static void handle_stop(char* args, FILE* out, Board* board, Move* bestmove) {
  (void)args;
  (void)out;
  (void)board;
  (void)bestmove;

  timemanager_stop();
}

static void handle_quit(char* args, FILE* out, Board* board, Move* bestmove) {
  (void)args;
  (void)out;
  (void)board;
  (void)bestmove;

  exit(EXIT_SUCCESS);
}
