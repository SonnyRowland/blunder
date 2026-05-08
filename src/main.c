#include <stdio.h>

#include "uci.h"

#define UCI_BUF_SIZE 512

static void gameloop(FILE* in, FILE* out);

int main(void) { gameloop(stdin, stdout); }

static void gameloop(FILE* in, FILE* out) {
  char buf[UCI_BUF_SIZE];

  for (;;) {
    char* input = fgets(buf, UCI_BUF_SIZE, in);
    if (!input) {
      return;
    } else {
      dispatch(buf, out);
      fflush(out);
    }
  }
}
