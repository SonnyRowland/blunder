#include "board.h"
#include "fen.h"
#include "move.h"
#include "unity.h"

#include <stdbool.h>

void setUp(void) {}
void tearDown(void) {}

void test_king_checking_king_white(void){
  Board board = fen_to_board("q7/8/2k5/8/4K3/8/8/8 w - - 0 1");
  Move move = (Move){3, 4, 4, 3, 0};

  apply_move(&board, move);
  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_king_checking_king_black(void){
  Board board = fen_to_board("3r4/p1p3pR/1p3kP1/7K/8/5R2/8/8 b - - 6 49");
  Move move = (Move){5, 5, 5, 6, 0};

  apply_move(&board, move);
  TEST_ASSERT_TRUE(is_in_check(board));
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_king_checking_king_white);
  RUN_TEST(test_king_checking_king_black);

  return UNITY_END();
}