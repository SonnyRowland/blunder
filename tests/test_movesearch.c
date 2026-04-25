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

void test_best_move_obvious_capture_depth_1_white(void){
  const char* fen = "k7/8/3q4/8/4N3/8/5K2/8 w - - 0 1";
  Board board = fen_to_board(fen);

  Move move_returned = get_best_move(&board, 1);
  Move move_expected = (Move) {3, 4, 5, 3};

  TEST_ASSERT_TRUE(moves_equal(move_returned, move_expected));
}

void test_best_move_obvious_capture_depth_1_black(void) {
  const char* fen = "k1r5/8/8/8/2Q5/8/5K2/8 b - - 0 1";
  Board board = fen_to_board(fen);

  Move move_returned = get_best_move(&board, 1);
  Move move_expected = (Move) {7, 2, 3, 2};

  TEST_ASSERT_TRUE(moves_equal(move_returned, move_expected));
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_best_move_obvious_capture_depth_1_white);
  RUN_TEST(test_best_move_obvious_capture_depth_1_black);

  return UNITY_END();
}