#include <stdio.h>
#include <string.h>

#include "display.h"
#include "fen.h"
#include "move.h"
#include "timemanager.h"

#define BUF_SIZE 512

// Functions to handle UCI commands
typedef void (*handler_fn)(char* args, FILE* out, Board* board);
static void handle_uci(char* args, FILE* out, Board* board);
static void handle_isready(char* args, FILE* out, Board* board);
static void handle_position(char* args, FILE* out, Board* board);
static void handle_go(char* args, FILE* out, Board* board);

typedef struct {
  const char* cmd;
  handler_fn fn;
} Command;

const Command commands[] = {
    {"uci", handle_uci},
    {"isready", handle_isready},
    {"position", handle_position},
    {"go", handle_go},
};

void dispatch(char* buf, FILE* out, Board* board) {
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
      commands[i].fn(args, out, board);
      break;
    }
  }
}

static void handle_uci(char* args, FILE* out, Board* board) {
  // Silence warnings
  (void)args;
  (void)board;

  fprintf(out, "id name blunderbot\n");
  fprintf(out, "id author SonnyRowland\n");
  fprintf(out, "uciok\n");
}

static void handle_isready(char* args, FILE* out, Board* board) {
  // Silence warnings
  (void)args;
  (void)board;

  fprintf(out, "readyok\n");
}

static void handle_position(char* args, FILE* out, Board* board) {
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
          commit_move(board, move_from_lan(token));
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
          commit_move(board, move_from_lan(token));
          token = strtok(NULL, " \n");
        }
      }
    }
  }
}

static void handle_go(char* args, FILE* out, Board* board) {
  timemanager_go(board, args);
}