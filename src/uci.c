#include <stdio.h>
#include <string.h>

#define BUF_SIZE 512

typedef void (*handler_fn)(char* args, FILE* out);
static void handle_uci(char* args, FILE* out);
static void handle_isready(char* args, FILE* out);

typedef struct {
  const char* cmd;
  handler_fn fn;
} Command;

const Command commands[] = {
    {"uci", handle_uci},
    {"isready", handle_isready},
};

void dispatch(char* buf, FILE* out) {
  char* tmp = buf;
  size_t cnt = 0;

  while (tmp[cnt] != ' ' && tmp[cnt] != '\n' && tmp[cnt] != '\0') cnt++;

  for (int i = 0; i < sizeof(commands) / sizeof(Command); i++) {
    if (strncmp(buf, commands[i].cmd, cnt) == 0) {
      commands[i].fn("temp", out);
    }
  }
}

static void handle_uci(char* args, FILE* out) {
  fprintf(out, "id name blunderbot\n");
  fprintf(out, "id author SonnyRowland\n");
  fprintf(out, "uciok\n");
}

static void handle_isready(char* args, FILE* out) { fprintf(out, "readyok\n"); }
