#include <stdio.h>
#include <string.h>

#include "board.h"
#include "display.h"
#include "uci.h"
#include "unity.h"

void setUp(void){}
void tearDown(void){}

static bool boards_equal(Board board1, Board board2){
  for(int rank = 0; rank < 8; rank++){
    for(int file = 0; file < 8; file++){
      if(board1.grid[rank][file] != board2.grid[rank][file]) return 0;
    }
  }

  if (board1.turn != board2.turn) return 0;
  if (board1.castle_wk != board2.castle_wk) return 0;
  if (board1.castle_wq != board2.castle_wq) return 0;
  if (board1.castle_bk != board2.castle_bk) return 0;
  if (board1.castle_bq != board2.castle_bq) return 0;
  if (board1.ep_file != board2.ep_file) return 0;
  if (board1.ep_rank != board2.ep_rank) return 0;
  if (board1.halfmove_clock != board2.halfmove_clock) return 0;
  if (board1.fullmove_count != board2.fullmove_count) return 0;

  return 1;
}

void test_dispatch_uci(void){
  char res[256] = {0};
  char* buf = "uci\n";
  FILE *out = fmemopen(res, sizeof(res), "w");

  dispatch(buf, out, &(Board){0});

  fclose(out);

  TEST_ASSERT_NOT_NULL(strstr(res, "id name blunderbot"));
  TEST_ASSERT_NOT_NULL(strstr(res, "id author SonnyRowland"));
  TEST_ASSERT_NOT_NULL(strstr(res, "uciok"));
}

void test_dispatch_isready(void){
  char res[256] = {0};
  char* buf = "isready\n";
  FILE *out = fmemopen(res, sizeof(res), "w");

  dispatch(buf, out, &(Board){0});

  fclose(out);

  TEST_ASSERT_NOT_NULL(strstr(res, "readyok"));
}

void test_position_startpos(void){
  char buf[] = "position startpos\n";
  Board board = {0};

  dispatch(buf, stdout, &board);

  Board expected_board = get_start_pos();
  TEST_ASSERT_TRUE(boards_equal(expected_board, board));
}

void test_position_startpos_qgd(void){
  char buf[] = "position startpos moves d2d4 d7d5 c2c4 e7e6\n";
  Board board = {0};

  dispatch(buf, stdout, &board);

  TEST_ASSERT_EQUAL_INT(board.grid[3][3], W_PAWN);
  TEST_ASSERT_EQUAL_INT(board.grid[4][3], B_PAWN);
  TEST_ASSERT_EQUAL_INT(board.grid[3][2], W_PAWN);
  TEST_ASSERT_EQUAL_INT(board.grid[5][4], B_PAWN);
}

void test_position_startpos_en_passant(void){
  char buf[] = "position startpos moves a2a3 d7d5 a3a4 d5d4 e2e4 d4e3\n";
  Board board = {0};

  dispatch(buf, stdout, &board);

  TEST_ASSERT_EQUAL_INT(board.grid[2][4], B_PAWN);
  TEST_ASSERT_EQUAL_INT(board.grid[3][4], EMPTY);
  TEST_ASSERT_EQUAL_INT(board.grid[3][3], EMPTY);
}

void test_position_fen_two_knights(void){
  char buf[] = "position fen rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 moves e2e4 e7e5 g1f3 b8c6\n";
  Board board = {0};

  dispatch(buf, stdout, &board);

  TEST_ASSERT_EQUAL_INT(board.grid[3][4], W_PAWN);
  TEST_ASSERT_EQUAL_INT(board.grid[4][4], B_PAWN);
  TEST_ASSERT_EQUAL_INT(board.grid[2][5], W_KNIGHT);
  TEST_ASSERT_EQUAL_INT(board.grid[5][2], B_KNIGHT);
}

void test_position_fen_en_passant(void){
  char buf[] = "position fen r1bqkbnr/pp3ppp/3p4/2pPp3/3nP3/2N2N2/PPP2PPP/R1BQKB1R w KQkq c6 0 6 moves d5c6\n";
  Board board = {0};

  dispatch(buf, stdout, &board);

  TEST_ASSERT_EQUAL_INT(board.grid[5][2], W_PAWN);
  TEST_ASSERT_EQUAL_INT(board.grid[4][2], EMPTY);
  TEST_ASSERT_EQUAL_INT(board.grid[4][3], EMPTY);
}

int main(void){
  UNITY_BEGIN();

  RUN_TEST(test_dispatch_uci);
  RUN_TEST(test_dispatch_isready);
  RUN_TEST(test_position_startpos);
  RUN_TEST(test_position_startpos_qgd);
  RUN_TEST(test_position_startpos_en_passant);
  RUN_TEST(test_position_fen_two_knights);
  RUN_TEST(test_position_fen_en_passant);

  return UNITY_END();
}
