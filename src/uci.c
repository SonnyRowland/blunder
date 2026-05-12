#include <stdio.h>
#include <string.h>

#include "display.h"
#include "fen.h"
#include "move.h"

#define BUF_SIZE 512

// Functions to handle UCI commands
typedef void (*handler_fn)(char* args, FILE* out);
static void handle_uci(char* args, FILE* out);
static void handle_isready(char* args, FILE* out);
static void handle_position(char* args, FILE* out);

typedef struct {
  const char* cmd;
  handler_fn fn;
} Command;

const Command commands[] = {
    {"uci", handle_uci},
    {"isready", handle_isready},
    {"position", handle_position},
};

void dispatch(char* buf, FILE* out) {
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
      commands[i].fn(args, out);
      break;
    }
  }
}

static void handle_uci(char* args, FILE* out) {
  (void)args;  // Silence warnings

  fprintf(out, "id name blunderbot\n");
  fprintf(out, "id author SonnyRowland\n");
  fprintf(out, "uciok\n");
}

static void handle_isready(char* args, FILE* out) {
  (void)args;  // Silence warnings

  fprintf(out, "readyok\n");
}

static void handle_position(char* args, FILE* out) {
  if (args) {
    char* token = strtok(args, " \n");
    if (!token) return;
    if (strcmp(token, "startpos") == 0) {
      token = strtok(NULL, " \n");
      if (token) {
        if (strcmp(token, "moves") == 0) {
          // TODO: Parse LAN moves after startpos
        }
      } else {
        // TODO: Initialise new game with startpos
      }
    } else if (strcmp(token, "fen") == 0) {
      token = strtok(NULL, " \n");
      if (token) {
        // TODO: Parse LAN moves after FEN string parse
      }
    } else {
      // TODO: Initialise new game with FEN string
    }
  }
}
