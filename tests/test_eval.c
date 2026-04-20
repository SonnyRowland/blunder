#include "eval.h"
#include "unity.h"
#include "board.h"
#include "fen.h"

void setUp(void) {}
void tearDown(void) {}

void test_eval_start_pos(void) {
  Board board = get_start_pos();

  TEST_ASSERT_EQUAL_INT16(0, eval_material(&board));
}

void test_eval_symmetric_position(void) {
  const char* fen1 = "r2q2k1/5pp1/p2b1n1p/2pN4/1p5B/3Q4/PPP2PPP/4R1K1 b - - 1 20";
  const char* fen2 = "1k1r4/ppp2ppp/4q3/b5P1/4nP2/P1N1B2P/1PP5/1K2Q2R w - - 0 20";

  Board board1 = fen_to_board(fen1);
  Board board2 = fen_to_board(fen2);

  TEST_ASSERT_EQUAL_INT16(0, eval_material(&board1) + eval_material(&board2));
}

int main(void){
  UNITY_BEGIN();

  RUN_TEST(test_eval_start_pos);
  RUN_TEST(test_eval_symmetric_position);

  return UNITY_END();
}