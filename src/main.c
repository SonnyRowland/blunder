#include <stdio.h>

#include "board.h"
#include "uci.h"

#define UCI_BUF_SIZE 512

static void gameloop(FILE* in, FILE* out);

#ifdef DEBUG
int main(void) { printf("debug\n"); }

#else
int main(void) { gameloop(stdin, stdout); }
#endif

static void gameloop(FILE* in, FILE* out) {
  Board board = {0};
  char buf[UCI_BUF_SIZE];

  for (;;) {
    char* input = fgets(buf, UCI_BUF_SIZE, in);
    if (!input) {
      return;
    } else {
      dispatch(buf, out, &board);
      fflush(out);
    }
  }
}
