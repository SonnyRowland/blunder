#include "perft.h"

#include "fen.h"
#include "board.h"

#include "unity.h"

#include <stdint.h>

void setUp(void){}
void tearDown(void){}

// Helper functions
// Kiwipete is a notoriously complex test position used to test move generation, see README for information
Board get_kiwipete(void){
  return fen_to_board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - ");
}

void perft_startpos_1(void){
  Board board = get_start_pos();
  uint64_t leafnodes = perft(&board, 1, false);

  TEST_ASSERT_EQUAL_INT(20, leafnodes);
}

void perft_startpos_2(void){
  Board board = get_start_pos();
  uint64_t leafnodes = perft(&board, 2, false);

  TEST_ASSERT_EQUAL_INT(400, leafnodes);
}

void perft_startpos_3(void){
  Board board = get_start_pos();
  uint64_t leafnodes = perft(&board, 3, false);

  TEST_ASSERT_EQUAL_INT(8902, leafnodes);
}

void perft_startpos_4(void){
  Board board = get_start_pos();
  uint64_t leafnodes = perft(&board, 4, false);

  TEST_ASSERT_EQUAL_UINT64(197281, leafnodes);
}

void perft_startpos_5(void){
  Board board = get_start_pos();
  uint64_t leafnodes = perft(&board, 5, false);

  TEST_ASSERT_EQUAL_UINT64(4865609, leafnodes);
}

void perft_kiwipete_1(void){
  Board board = get_kiwipete();
  uint64_t leafnodes = perft(&board, 1, false);

  TEST_ASSERT_EQUAL_UINT64(48, leafnodes);
}

void perft_kiwipete_2(void){
  Board board = get_kiwipete();
  uint64_t leafnodes = perft(&board, 2, false);

  TEST_ASSERT_EQUAL_UINT64(2039, leafnodes);
}

void perft_kiwipete_3(void){
  Board board = get_kiwipete();
  uint64_t leafnodes = perft(&board, 3, false);

  TEST_ASSERT_EQUAL_UINT64(97862, leafnodes);
}

void perft_kiwipete_4(void){
  Board board = get_kiwipete();
  uint64_t leafnodes = perft(&board, 4, false);

  TEST_ASSERT_EQUAL_UINT64(4085603, leafnodes);
}

int main(void){
  UNITY_BEGIN();

  RUN_TEST(perft_startpos_1);
  RUN_TEST(perft_startpos_2);
  RUN_TEST(perft_startpos_3);
  RUN_TEST(perft_startpos_4);
  RUN_TEST(perft_startpos_5);

  RUN_TEST(perft_kiwipete_1);
  RUN_TEST(perft_kiwipete_2);
  RUN_TEST(perft_kiwipete_3);
  RUN_TEST(perft_kiwipete_4);

  return(UNITY_END());
}