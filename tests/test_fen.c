#include "unity.h"
#include "fen.h"
#include <string.h>

void setUp(void) {}
void tearDown(void) {}

// Helper function for fen to board then back to fen
static int fen_round_trip(const char* fen)
{
  char result[128];
  Board board = fen_to_board(fen);
  board_to_fen(board, result);

  return strcmp(fen, result) == 0;
}

void test_starting_position_round_trip(void)
{
  const char* fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  TEST_ASSERT_TRUE(fen_round_trip(fen));
}

void test_en_passant_round_trip(void) {
  const char* fen = "rnbqkbnr/1pp1pppp/p7/3pP3/8/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 3";
  TEST_ASSERT_TRUE(fen_round_trip(fen));
}

int main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_starting_position_round_trip);
  RUN_TEST(test_en_passant_round_trip);

  return UNITY_END();
}