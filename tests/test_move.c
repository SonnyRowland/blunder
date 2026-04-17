#include "unity.h"
#include "move.h"
#include "fen.h"
#include "display.h"

void setUp(void) {}
void tearDown(void) {}

void test_apply_move_en_passant_white(void) {
  const char* fen = "rnbqkbnr/1pp1pppp/p7/3pP3/8/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 3";
  Board board = fen_to_board(fen);
  Move move = (Move) {4, 4, 5, 3};

  apply_move(&board, move);

  TEST_ASSERT_TRUE(board.grid[4][3] == EMPTY);
}

void test_apply_move_en_passant_black(void) {
  const char* fen = "rnbqkbnr/pppp1ppp/8/8/3Pp3/P6P/1PP1PPP1/RNBQKBNR b KQkq d3 0 3";
  Board board = fen_to_board(fen);
  Move move = (Move){3, 4, 2, 3};

  apply_move(&board, move);

  TEST_ASSERT_TRUE(board.grid[3][3] == EMPTY);
}

void test_check_start_pos(void) {
  Board board = get_start_pos();

  TEST_ASSERT_FALSE(is_in_check(board));
}

void test_check_pawn_1_white(void){
  const char* fen = "8/8/8/2p5/3K4/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_pawn_1_white_turn_swap(void){
  const char* fen = "8/8/8/2p5/3K4/8/8/8 b - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_FALSE(is_in_check(board));
}

void test_check_pawn_1_black(void){
  const char* fen = "k7/1P6/8/8/8/8/8/8 b - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_pawn_2_white(void){
  const char* fen = "8/8/8/8/8/8/1p6/K7 w - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_pawn_2_black(void){
  const char* fen = "1k6/P7/8/8/8/8/8/8 b - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_pawn_2_black_turn_swap(void) {
  const char* fen = "1k6/P7/8/8/8/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_FALSE(is_in_check(board));
  
}

void test_check_knight_move_1_white(void) {
  const char* fen = "8/8/3n4/8/2K5/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_knight_move_1_black(void) {
  const char* fen = "8/8/8/8/8/1N6/8/k7 b - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_knight_move_2_white(void) {
  const char* fen = "8/8/8/8/8/8/2n5/K7 w - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_knight_move_2_white_turn_swap(void) {
  const char* fen = "8/8/8/8/8/8/2n5/K7 b - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_FALSE(is_in_check(board));
}

void test_check_knight_move_2_black(void) {
  const char* fen = "7N/5k2/8/8/8/8/8/8 b - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_knight_move_3_white (void){
  const char* fen = "8/K7/2n5/8/8/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_knight_move_3_black (void){
  const char* fen = "8/8/8/8/8/8/5k2/7N b - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_knight_move_4_white(void) {
  const char* fen = "K7/8/1n6/8/8/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_knight_move_4_black(void) {
  const char* fen = "8/8/8/8/8/6k1/8/7N b - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_knight_move_4_black_turn_swap(void) {
  const char* fen = "8/8/8/8/8/6k1/8/7N w - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_FALSE(is_in_check(board));
}

void test_check_knight_move_5_white(void) {
  const char* fen = "8/8/8/8/8/7K/8/6n1 w - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_knight_move_5_black(void) {
  const char* fen = "8/8/8/8/8/1k6/8/N7 b - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_knight_move_6_white(void) {
  const char* fen = "8/8/8/8/8/8/6K1/4n3 w - - 0 1";
  Board board = fen_to_board(fen);
  
  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_knight_move_6_black(void){
  const char* fen = "2k5/N7/8/8/8/8/8/8 b - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_knight_move_7_white(void) {
  const char* fen = "8/8/8/8/2n5/4K3/8/8 w - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_knight_move_7_black(void) {
  const char* fen = "8/8/8/8/8/8/5N2/7k b - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_knight_move_8_white(void) {
  const char* fen = "8/8/8/8/8/n7/8/1K6 w - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_knight_move_8_black(void) {
  const char* fen = "8/8/3N4/8/4k3/8/8/8 b - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_bishop_rank_decrease_file_decrease_white(void) {
  const char* fen = "8/8/5K2/8/8/8/1b6/8 w - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_bishop_rank_decrease_file_decrease_black(void) {
  const char* fen = "8/8/8/7k/8/8/4Q3/8 b - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_bishop_rank_decrease_file_increase_white(void) {
  const char* fen = "8/8/8/8/4K3/8/8/1b6 w - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_bishop_rank_decrease_file_increase_white_turn_swap(void) {
  const char* fen = "8/8/8/8/4K3/8/8/1b6 b - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_FALSE(is_in_check(board));
}

void test_check_bishop_rank_decrease_file_increase_black(void) {
  const char* fen = "8/8/5k2/8/8/2B5/8/8 b - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_bishop_rank_increase_file_decrease_white(void) {
  const char* fen = "8/1q6/8/8/8/8/6K1/8 w - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_bishop_rank_increase_file_decrease_black(void) {
  const char* fen = "8/8/8/8/Q7/1k6/8/8 b - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_bishop_rank_increase_file_increase_white(void) {
  const char* fen = "8/8/3b4/8/1K6/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_bishop_rank_increase_file_increase_black(void) {
  const char* fen = "8/8/8/7B/8/8/8/3k4 b - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_bishop_rank_increase_file_increase_black_turn_swap(void) {
  const char* fen = "8/8/8/7B/8/8/8/3k4 w - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_FALSE(is_in_check(board));
}

void test_check_rook_rank_decrease_white(void) {
  const char* fen = "8/8/3K4/8/8/8/8/3r4 w - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_rook_rank_decrease_white_turn_swap(void) {
  const char* fen = "8/8/3K4/8/8/8/8/3r4 b - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_FALSE(is_in_check(board));
}

void test_check_rook_rank_decrease_black(void) {
  const char* fen = "4k3/8/8/8/8/8/4R3/8 b - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_rook_rank_increase_white(void) {
  const char* fen = "1r6/8/8/8/8/8/8/1K6 w - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_rook_rank_increase_black(void) {
  const char* fen = "8/8/8/8/8/8/4R3/4k3 b - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_rook_rank_increase_black_turn_swap(void) {
  const char* fen = "8/8/8/8/8/8/4R3/4k3 w - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_FALSE(is_in_check(board));
}

void test_check_rook_file_decrease_white(void) {
  const char* fen = "8/8/8/8/8/8/8/3rK3 w - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_rook_file_decrease_black(void) {
  const char* fen = "8/8/4R2k/8/8/8/8/8 b - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_rook_file_increase_white(void) {
  const char* fen = "8/8/8/8/K6r/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_rook_file_increase_black(void) {
  const char* fen = "8/8/k6R/8/8/8/8/8 b - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_queen_rank_decrease_white (void) {
  const char* fen = "8/8/K7/q7/8/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_queen_rank_decrease_black (void) {
  const char* fen = "7k/8/7Q/8/8/8/8/8 b - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_queen_rank_increase_white(void) {
  const char* fen = "8/q7/8/8/8/8/K7/8 w - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_queen_rank_increase_white_turn_swap(void) {
  const char* fen = "8/q7/8/8/8/8/K7/8 b - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_FALSE(is_in_check(board));
}

void test_check_queen_rank_increase_black(void) {
  const char* fen = "8/8/8/2Q5/8/8/2k5/8 b - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_queen_file_decrease_white(void) {
  const char* fen = "8/q1K5/8/8/8/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_queen_file_decrease_black(void) {
  const char* fen = "8/8/Q5k1/8/8/8/8/8 b - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_queen_file_decrease_black_turn_swap(void) {
  const char* fen = "8/8/Q5k1/8/8/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_FALSE(is_in_check(board));
}

void test_check_queen_file_increase_white(void) {
  const char* fen = "8/8/8/8/8/8/8/1Kq5 w - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_queen_file_increase_black(void) {
  const char* fen = "8/8/8/8/8/2kQ4/8/8 b - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_queen_rank_decrease_file_decrease_white(void) {
  const char* fen = "3K4/8/8/q7/8/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_queen_rank_decrease_file_decrease_black(void) {
  const char* fen = "8/8/6k1/5Q2/8/8/8/8 b - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_queen_rank_decrease_file_increase_white(void) {
  const char* fen = "8/8/4K3/8/8/8/q7/8 w - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_queen_rank_decrease_file_increase_black(void) {
  const char* fen = "8/8/6k1/8/4Q3/8/8/8 b - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_queen_rank_increase_file_decrease_white(void) {
  const char* fen = "8/5q2/8/7K/8/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_queen_rank_increase_file_decrease_black(void){
  const char* fen = "8/8/8/2Q5/3k4/8/8/8 b - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_queen_rank_increase_file_increase_white(void) {
  const char* fen = "7q/8/8/8/8/2K5/8/8 w - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

void test_check_queen_rank_increase_file_increase_black(void) {
  const char* fen = "8/8/8/8/8/8/7Q/6k1 b - - 0 1";
  Board board = fen_to_board(fen);

  TEST_ASSERT_TRUE(is_in_check(board));
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_apply_move_en_passant_white);
  RUN_TEST(test_apply_move_en_passant_black);

  RUN_TEST(test_check_start_pos);
  RUN_TEST(test_check_pawn_1_white);
  RUN_TEST(test_check_pawn_1_white_turn_swap);
  RUN_TEST(test_check_pawn_1_black);
  RUN_TEST(test_check_pawn_2_white);
  RUN_TEST(test_check_pawn_2_black);
  RUN_TEST(test_check_pawn_2_black_turn_swap);
  RUN_TEST(test_check_knight_move_1_white);
  RUN_TEST(test_check_knight_move_1_black);
  RUN_TEST(test_check_knight_move_2_white);
  RUN_TEST(test_check_knight_move_2_white_turn_swap);
  RUN_TEST(test_check_knight_move_2_black);
  RUN_TEST(test_check_knight_move_3_white);
  RUN_TEST(test_check_knight_move_3_black);
  RUN_TEST(test_check_knight_move_4_white);
  RUN_TEST(test_check_knight_move_4_black);
  RUN_TEST(test_check_knight_move_4_black_turn_swap);
  RUN_TEST(test_check_knight_move_5_white);
  RUN_TEST(test_check_knight_move_5_black);
  RUN_TEST(test_check_knight_move_6_white);
  RUN_TEST(test_check_knight_move_6_black);
  RUN_TEST(test_check_knight_move_7_white);
  RUN_TEST(test_check_knight_move_7_black);
  RUN_TEST(test_check_knight_move_8_white);
  RUN_TEST(test_check_knight_move_8_black);
  RUN_TEST(test_check_bishop_rank_decrease_file_decrease_white);
  RUN_TEST(test_check_bishop_rank_decrease_file_decrease_black);
  RUN_TEST(test_check_bishop_rank_decrease_file_increase_white);
  RUN_TEST(test_check_bishop_rank_decrease_file_increase_white_turn_swap);
  RUN_TEST(test_check_bishop_rank_decrease_file_increase_black);
  RUN_TEST(test_check_bishop_rank_increase_file_decrease_white);
  RUN_TEST(test_check_bishop_rank_increase_file_decrease_black);
  RUN_TEST(test_check_bishop_rank_increase_file_increase_white);
  RUN_TEST(test_check_bishop_rank_increase_file_increase_black);
  RUN_TEST(test_check_bishop_rank_increase_file_increase_black_turn_swap);
  RUN_TEST(test_check_rook_rank_decrease_white);
  RUN_TEST(test_check_rook_rank_decrease_white_turn_swap);
  RUN_TEST(test_check_rook_rank_decrease_black);
  RUN_TEST(test_check_rook_rank_increase_white);
  RUN_TEST(test_check_rook_rank_increase_black);
  RUN_TEST(test_check_rook_rank_increase_black_turn_swap);
  RUN_TEST(test_check_rook_file_decrease_white);
  RUN_TEST(test_check_rook_file_decrease_black);
  RUN_TEST(test_check_rook_file_increase_white);
  RUN_TEST(test_check_rook_file_increase_black);
  RUN_TEST(test_check_queen_rank_decrease_white);
  RUN_TEST(test_check_queen_rank_decrease_black);
  RUN_TEST(test_check_queen_rank_increase_white);
  RUN_TEST(test_check_queen_rank_increase_white_turn_swap);
  RUN_TEST(test_check_queen_rank_increase_black);
  RUN_TEST(test_check_queen_file_decrease_white);
  RUN_TEST(test_check_queen_file_decrease_black);
  RUN_TEST(test_check_queen_file_decrease_black_turn_swap);
  RUN_TEST(test_check_queen_file_increase_white);
  RUN_TEST(test_check_queen_file_increase_black);
  RUN_TEST(test_check_queen_rank_decrease_file_decrease_white);
  RUN_TEST(test_check_queen_rank_decrease_file_decrease_black);
  RUN_TEST(test_check_queen_rank_decrease_file_increase_white);
  RUN_TEST(test_check_queen_rank_decrease_file_increase_black);
  RUN_TEST(test_check_queen_rank_increase_file_decrease_white);
  RUN_TEST(test_check_queen_rank_increase_file_decrease_black);
  RUN_TEST(test_check_queen_rank_increase_file_increase_white);
  RUN_TEST(test_check_queen_rank_increase_file_increase_black);

  return UNITY_END();
}