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

void test_apply_move_castle_k_white(void) {
  const char* fen = "8/8/8/8/8/8/8/4K2R w K - 0 1";
  Board board = fen_to_board(fen);
  Move move = (Move) {0, 4, 0, 6};

  apply_move(&board, move);

  TEST_ASSERT_TRUE(board.grid[0][5] == W_ROOK);
  TEST_ASSERT_TRUE(board.grid[0][6] == W_KING);
}

void test_apply_move_castle_k_black(void) {
  const char* fen = "4k2r/8/8/8/8/8/8/8 b k - 0 1";
  Board board = fen_to_board(fen);
  Move move = (Move) {7, 4, 7, 6};

  apply_move(&board, move);
  
  TEST_ASSERT_TRUE(board.grid[7][5] == B_ROOK);
  TEST_ASSERT_TRUE(board.grid[7][6] == B_KING);
}

void test_apply_move_castle_q_white(void){
  const char* fen = "8/8/8/8/8/8/8/R3K3 w Q - 0 1";
  Board board = fen_to_board(fen);
  Move move = (Move) {0, 4, 0, 2};

  apply_move(&board, move);

  TEST_ASSERT_TRUE(board.grid[0][2] == W_KING);
  TEST_ASSERT_TRUE(board.grid[0][3] == W_ROOK);
}

void test_apply_move_castle_q_black(void){
  const char* fen = "r3k3/8/8/8/8/8/8/8 b q - 0 1";
  Board board = fen_to_board(fen);
  Move move = (Move) {7, 4, 7, 2};

  apply_move(&board, move);

  TEST_ASSERT_TRUE(board.grid[7][2] == B_KING);
  TEST_ASSERT_TRUE(board.grid[7][3] == B_ROOK);
}

void test_apply_move_promotion_knight_white(void) {
  const char* fen = "4P3/8/8/8/8/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);
  Move move = (Move) {7, 4, 7, 4, 2};
  
  apply_move(&board, move);

  TEST_ASSERT_TRUE(board.grid[7][4] == W_KNIGHT);
}

void test_apply_move_promotion_knight_black(void){
  const char* fen = "8/8/8/8/8/8/8/1p6 b - - 0 1";
  Board board = fen_to_board(fen);
  Move move = (Move) {0, 1, 0, 1, -2};

  apply_move(&board, move);

  TEST_ASSERT_TRUE(board.grid[0][1] == B_KNIGHT);
}

void test_apply_move_promotion_bishop_white(void){
  const char* fen = "3P4/8/8/8/8/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);
  Move move = (Move) {7, 3, 7, 3, 3};

  apply_move(&board, move);

  TEST_ASSERT_TRUE(board.grid[7][3] == W_BISHOP);
}

void test_apply_move_promotion_bishop_black(void){
  const char* fen = "8/8/8/8/8/8/8/7p b - - 0 1";
  Board board = fen_to_board(fen);
  Move move = (Move) {0, 7, 0, 7, -3};

  apply_move(&board, move);

  TEST_ASSERT_TRUE(board.grid[0][7] == B_BISHOP);
}

void test_apply_move_promotion_rook_white(void){
  const char* fen = "5P2/8/8/8/8/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);
  Move move = (Move) {7, 5, 7, 5, 4};

  apply_move(&board, move);

  TEST_ASSERT_TRUE(board.grid[7][5] == W_ROOK);
}

void test_apply_move_promotion_rook_black(void){
  const char* fen = "8/8/8/8/8/8/8/4p3 b - - 0 1";
  Board board = fen_to_board(fen);
  Move move = (Move){0, 4, 0, 4, -4};

  apply_move(&board, move);

  TEST_ASSERT_TRUE(board.grid[0][4] == B_ROOK);
}

void test_apply_move_promotion_queen_white(void){
  const char* fen = "7P/8/8/8/8/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);
  Move move = (Move) {7, 7, 7, 7, 5};

  apply_move(&board, move);

  TEST_ASSERT_TRUE(board.grid[7][7] == W_QUEEN);
}

void test_apply_move_promotion_queen_black(void){
  const char* fen = "8/8/8/8/8/8/8/p7 b - - 0 1";
  Board board = fen_to_board(fen);
  Move move = (Move){0, 0, 0, 0, -5};

  apply_move(&board, move);

  TEST_ASSERT_TRUE(board.grid[0][0] == B_QUEEN);
}

void test_reverse_move_en_passant_white(void) {
  const char* fen = "rnbqkbnr/pppp1pp1/7p/3Pp3/8/8/PPP1PPPP/RNBQKBNR w KQkq e6 0 3";
  char fen2[128];
  Board board = fen_to_board(fen);
  Move move = (Move) {4, 3, 5, 4};
  
  Piece piece_taken = apply_move(&board, move);
  reverse_move(&board, move, piece_taken);
  board_to_fen(board, fen2);

  TEST_ASSERT_EQUAL_STRING(fen, fen2);
}

void test_reverse_move_en_passant_black(void) {
  const char* fen = "rnbqkbnr/p1pppppp/8/8/1pP5/P6P/1P1PPPP1/RNBQKBNR b KQkq c3 0 3";
  char fen2[128];
  Board board = fen_to_board(fen);
  Move move = (Move) {3, 1, 2, 2};

  Piece piece_taken = apply_move(&board, move);
  reverse_move(&board, move, piece_taken);
  board_to_fen(board, fen2);

  TEST_ASSERT_EQUAL_STRING(fen, fen2);
}

void test_reverse_move_castle_k_white(void) {
  const char* fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQK2R w KQkq - 0 1";
  char fen2[128];
  Board board = fen_to_board(fen);
  Move move = (Move) {0, 4, 0, 6};

  Piece piece_taken = apply_move(&board, move);
  reverse_move(&board, move, piece_taken);
  board_to_fen(board, fen2);

  TEST_ASSERT_EQUAL_STRING(fen, fen2);
}

void test_reverse_move_castle_k_black(void){
  const char* fen = "rnbqk2r/pppppppp/8/8/8/8/PPPPPPPP/RNBQK2R b KQkq - 0 1";
  char fen2[128];
  Board board = fen_to_board(fen);
  Move move = (Move) {7, 4, 7, 6};

  Piece piece_taken = apply_move(&board, move);
  reverse_move(&board, move, piece_taken);
  board_to_fen(board, fen2);

  TEST_ASSERT_EQUAL_STRING(fen, fen2);
}

void test_reverse_move_castle_q_white(void) {
  const char* fen = "rnbqk2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R w KQkq - 0 1";
  char fen2[128];
  Board board = fen_to_board(fen);
  Move move = (Move) {0, 4, 0, 2};

  Piece piece_taken = apply_move(&board, move);
  reverse_move(&board, move, piece_taken);
  board_to_fen(board, fen2);

  TEST_ASSERT_EQUAL_STRING(fen, fen2);
}

void test_reverse_move_castle_q_black(void) {
  const char* fen = "r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R b KQkq - 0 1";
  char fen2[128];
  Board board = fen_to_board(fen);
  Move move = (Move) {7, 4, 7, 2};

  Piece piece_taken = apply_move(&board, move);
  reverse_move(&board, move, piece_taken);
  board_to_fen(board, fen2);

  TEST_ASSERT_EQUAL_STRING(fen, fen2);
}

void test_reverse_move_promotion_knight_white(void) {
  const char* fen = "8/4P3/8/8/8/8/8/8 w - - 0 1";
  char fen2[128];
  Board board = fen_to_board(fen);
  Move move = (Move) {6, 4, 7, 4, 2};

  Piece piece_taken = apply_move(&board, move);
  reverse_move(&board, move, piece_taken);
  board_to_fen(board, fen2);

  TEST_ASSERT_EQUAL_STRING(fen, fen2);
  TEST_ASSERT_EQUAL_INT(W_PAWN, board.grid[6][4]);
  TEST_ASSERT_EQUAL_INT(EMPTY, board.grid[7][4]);
}

void test_reverse_move_promotion_knight_black(void){
  const char* fen = "8/8/8/8/8/8/7p/8 b - - 0 1";
  char fen2[128];
  Board board = fen_to_board(fen);
  Move move = (Move) {1, 7, 0, 7, -2};

  Piece piece_taken = apply_move(&board, move);
  reverse_move(&board, move, piece_taken);
  board_to_fen(board, fen2);

  TEST_ASSERT_EQUAL_STRING(fen, fen2);
  TEST_ASSERT_EQUAL_INT(B_PAWN, board.grid[6][4]);
  TEST_ASSERT_EQUAL_INT(EMPTY, board.grid[7][4]);
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
  RUN_TEST(test_apply_move_castle_k_white);
  RUN_TEST(test_apply_move_castle_k_black);
  RUN_TEST(test_apply_move_castle_q_white);
  RUN_TEST(test_apply_move_castle_q_black);
  RUN_TEST(test_apply_move_promotion_knight_white);
  RUN_TEST(test_apply_move_promotion_knight_black);
  RUN_TEST(test_apply_move_promotion_bishop_white);
  RUN_TEST(test_apply_move_promotion_bishop_black);
  RUN_TEST(test_apply_move_promotion_rook_white);
  RUN_TEST(test_apply_move_promotion_rook_black);
  RUN_TEST(test_apply_move_promotion_queen_white);
  RUN_TEST(test_apply_move_promotion_queen_black);

  RUN_TEST(test_reverse_move_en_passant_white);
  RUN_TEST(test_reverse_move_en_passant_black);
  RUN_TEST(test_reverse_move_castle_k_white);
  RUN_TEST(test_reverse_move_castle_k_black);
  RUN_TEST(test_reverse_move_castle_q_white);
  RUN_TEST(test_reverse_move_castle_q_black);
  RUN_TEST(test_reverse_move_promotion_knight_white);
  RUN_TEST(test_reverse_move_promotion_knight_black);
  
  // TODO PICKUP: write the tests below
  
  // RUN_TEST(test_reverse_move_promotion_bishop_white);
  // RUN_TEST(test_reverse_move_promotion_bishop_black);
  // RUN_TEST(test_reverse_move_promotion_bishop_white);
  // RUN_TEST(test_reverse_move_promotion_rook_white);
  // RUN_TEST(test_reverse_move_promotion_rook_black);
  // RUN_TEST(test_reverse_move_promotion_queen_white);
  // RUN_TEST(test_reverse_move_promotion_queen_black);

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