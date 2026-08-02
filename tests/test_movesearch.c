#include <stdbool.h>

#include "unity.h"
#include "movesearch.h"
#include "fen.h"
#include "move.h"

void setUp(void) {}
void tearDown(void) {}

bool moves_equal(Move move1, Move move2) {
  return move1.from_rank == move2.from_rank && move1.from_file == move2.from_file && move1.to_rank == move2.to_rank && move1.to_file == move2.to_file;
}

int main(void) {
  UNITY_BEGIN();

  return UNITY_END();
}