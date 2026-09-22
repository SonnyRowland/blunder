#include <stdio.h>
#include <string.h>

#include "bench.h"
#include "board.h"
#include "move.h"
#include "uci.h"

#define UCI_BUF_SIZE 512

static void gameloop(FILE* in, FILE* out);

#ifdef DEBUG
int main(void) { printf("debug\n"); }

#else
int main(int argc, char* argv[]) {
  if (argc > 1 && strcmp(argv[1], "bench") == 0) {
    bench();
    return 0;
  }

  gameloop(stdin, stdout);

  return 0;
}
#endif

static void gameloop(FILE* in, FILE* out) {
  Board board = {0};
  Move bestmove = {0};
  char buf[UCI_BUF_SIZE];

  for (;;) {
    char* input = fgets(buf, UCI_BUF_SIZE, in);
    if (!input) {
      return;
    } else {
      dispatch(buf, out, &board, &bestmove);
      fflush(out);
    }
  }
}
