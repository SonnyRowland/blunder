#include "unity.h"
#include "move.h"
#include "fen.h"
#include "display.h"

void setUp(void) {}
void tearDown(void) {}

// Helper function for verifying MoveList contains certain move
static int move_list_contains(MoveList move_list, Move move) {
  for (int i = 0; i < move_list.count; i++) {
    Move m = move_list.moves[i];
    if (m.from_rank == move.from_rank && m.from_file == move.from_file && m.to_rank == move.to_rank && m.to_file == move.to_file)
    {
      return 1;
    }
  }
  return 0;
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

void test_move_gen_empty_board(void) {
  const char* fen = "8/8/8/8/8/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  TEST_ASSERT_EQUAL_INT(0, moves.count);
}

void test_move_gen_start_pos(void) {
  Board board = get_start_pos();
  MoveList moves = generate_legal_moves(board);

  TEST_ASSERT_EQUAL_INT(20, moves.count);
}

void test_move_gen_e4(void) {
  const char* fen = "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1";
  Board board = fen_to_board(fen);

  MoveList moves = generate_legal_moves(board);
  TEST_ASSERT_EQUAL_INT(20, moves.count);
}

void test_move_gen_pawn_moves(void) {
  const char* fen = "8/pppppppp/8/8/8/8/PPPPPPPP/8 w - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  Move test_move = (Move){1, 3, 3, 3};

  TEST_ASSERT_EQUAL_INT(16, moves.count);
  TEST_ASSERT_TRUE(move_list_contains(moves, test_move));
}

void test_move_gen_pawn_at_end(void) {
  const char* fen = "P7/8/8/8/8/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  TEST_ASSERT_EQUAL_INT(0, moves.count);
}

void test_move_gen_pawn_double_push_white(void) {
  const char* fen = "8/8/8/8/8/1P6/P1PPPPPP/8 w - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  TEST_ASSERT_EQUAL_INT(15, moves.count);
}

void test_move_gen_pawn_double_push_black(void) {
  const char* fen = "8/p1pppppp/1p6/8/8/8/8/8 b - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  TEST_ASSERT_EQUAL_INT(15, moves.count);
}

void test_move_gen_pawn_takes_white(void) {
  const char* fen = "8/8/8/2ppp3/3P4/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  Move test_move = (Move){3, 3, 4, 2};

  TEST_ASSERT_EQUAL_INT(2, moves.count);
  TEST_ASSERT_TRUE(move_list_contains(moves, test_move));
}

void test_move_gen_pawn_takes_black(void) {
  const char* fen = "8/8/8/3p4/2PPP3/8/8/8 b - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  Move test_move = (Move){4, 3, 3, 4};

  TEST_ASSERT_EQUAL_INT(2, moves.count);
  TEST_ASSERT_TRUE(move_list_contains(moves, test_move));
}

void test_move_gen_pawn_takes_en_passant_white(void) {
  const char* fen = "8/8/8/3pP3/8/8/8/8 w - d6 0 3";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  Move test_move = (Move){4,4,5,3};

  TEST_ASSERT_EQUAL_INT(2, moves.count);
  TEST_ASSERT_TRUE(move_list_contains(moves, test_move));
}

void test_move_gen_pawn_takes_en_passant_black(void) {
  const char* fen = "8/8/8/8/3pP3/8/8/8 b - e3 0 3";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  Move test_move = (Move) {3, 3, 2, 4};

  TEST_ASSERT_EQUAL_INT(2, moves.count);
  TEST_ASSERT_TRUE(move_list_contains(moves, test_move));
}

void test_move_gen_pawn_edge_case_white(void) {
  const char* fen = "PPPPPPPP/8/8/8/8/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  TEST_ASSERT_EQUAL_INT(0, moves.count);
}

void test_move_gen_pawn_edge_case_black(void) {
  const char* fen = "8/8/8/8/8/8/8/pppppppp b - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  TEST_ASSERT_EQUAL_INT(0, moves.count);
}

void test_move_gen_knight_centre(void) {
  const char* fen = "8/8/8/4N3/8/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  Move test_move = (Move){4, 4, 5, 6};

  TEST_ASSERT_EQUAL_INT(8, moves.count);
  TEST_ASSERT_TRUE(move_list_contains(moves, test_move));
}

void test_move_gen_knight_corner(void) {
  const char* fen = "8/8/8/8/8/8/8/N7 w - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  Move test_move = (Move){0, 0, 1, 2};

  TEST_ASSERT_EQUAL_INT(2, moves.count);
  TEST_ASSERT_TRUE(move_list_contains(moves, test_move));
}

void test_move_gen_knight_takes_white(void) {
  const char* fen = "8/2p1p3/1p3p2/3N4/1p3p2/2p1p3/8/8 w - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  Move test_move = (Move) {4, 3, 2, 2};

  TEST_ASSERT_EQUAL_INT(8, moves.count);
  TEST_ASSERT_TRUE(move_list_contains(moves, test_move));
}

void test_move_gen_knight_takes_black(void) {
  const char* fen = "8/2P1P3/1P3P2/3n4/1P3P2/2P1P3/8/8 b - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  Move test_move = (Move) {4, 3, 5, 5};

  TEST_ASSERT_EQUAL_INT(8, moves.count);
  TEST_ASSERT_TRUE(move_list_contains(moves, test_move));
}

void test_move_gen_knight_blocked_white(void) {
  const char* fen = "8/2p1p3/1pP1Pp2/1P3P2/1p1N1p2/1Pp1pP2/2P1P3/8 w - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  TEST_ASSERT_EQUAL_INT(0, moves.count);
}

void test_move_gen_knight_blocked_black(void) {
  const char* fen = "8/2p1p3/1pP1Pp2/1P1n1P2/1p3p2/1Pp1pP2/2P1P3/8 b - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  TEST_ASSERT_EQUAL_INT(0, moves.count);
}

void test_move_gen_bishop_centre(void) {
  const char* fen = "8/8/8/4B3/8/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  Move test_move = (Move){4, 4, 7, 1};

  TEST_ASSERT_EQUAL_INT(13, moves.count);
  TEST_ASSERT_TRUE(move_list_contains(moves, test_move));
}

void test_move_gen_bishop_corner(void) {
  const char* fen = "B7/8/8/8/8/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  Move test_move = (Move){7, 0, 0, 7};

  TEST_ASSERT_EQUAL_INT(7, moves.count);
  TEST_ASSERT_TRUE(move_list_contains(moves, test_move));
}

void test_move_gen_rook_centre(void) {
  const char* fen = "8/8/8/4R3/8/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  Move test_move = (Move){4, 4, 4, 7};

  TEST_ASSERT_EQUAL_INT(14, moves.count);
  TEST_ASSERT_TRUE(move_list_contains(moves, test_move));
}

void test_move_gen_rook_corner(void) {
  const char* fen = "8/8/8/8/8/8/8/7R w - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  Move test_move = (Move){0, 7, 0, 0};

  TEST_ASSERT_EQUAL_INT(14, moves.count);
  TEST_ASSERT_TRUE(move_list_contains(moves, test_move));
}

void test_move_gen_queen_centre(void) {
  const char* fen = "8/8/8/4Q3/8/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  Move test_move_diag = (Move){4, 4, 6, 6};
  Move test_move_horiz = (Move){4, 4, 0, 4};

  TEST_ASSERT_EQUAL_INT(27, moves.count);
  TEST_ASSERT_TRUE(move_list_contains(moves, test_move_diag));
  TEST_ASSERT_TRUE(move_list_contains(moves, test_move_horiz));
}

void test_move_gen_queen_corner(void) {
  const char* fen = "7Q/8/8/8/8/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  Move test_move_diag = (Move){7, 7, 3, 3};
  Move test_move_horiz = (Move){7, 7, 7, 3};

  TEST_ASSERT_EQUAL_INT(21, moves.count);
  TEST_ASSERT_TRUE(move_list_contains(moves, test_move_diag));
  TEST_ASSERT_TRUE(move_list_contains(moves, test_move_horiz));
}

void test_move_gen_king_centre(void) {
  const char* fen = "8/8/8/4K3/8/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  Move test_move_diag = (Move){4, 4, 5, 5};
  Move test_move_horiz = (Move){4, 4, 3, 4};

  TEST_ASSERT_EQUAL_INT(8, moves.count);
  TEST_ASSERT_TRUE(move_list_contains(moves, test_move_diag));
  TEST_ASSERT_TRUE(move_list_contains(moves, test_move_horiz));
}

void test_move_gen_king_corner(void) {
  const char* fen = "K7/8/8/8/8/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  Move test_move_diag = (Move){7, 0, 6, 1};
  Move test_move_horiz = (Move){7, 0, 7, 1};

  TEST_ASSERT_EQUAL_INT(3, moves.count);
  TEST_ASSERT_TRUE(move_list_contains(moves, test_move_diag));
  TEST_ASSERT_TRUE(move_list_contains(moves, test_move_horiz));
}

void test_move_gen_king_takes_white(void) {
  const char* fen = "8/8/2nnn3/2nKn3/2nnn3/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  Move test_move = (Move){4,3,5,4};

  TEST_ASSERT_EQUAL_INT(8, moves.count);
  TEST_ASSERT_TRUE(move_list_contains(moves, test_move));
}

void test_move_gen_king_takes_black(void) {
  const char* fen = "8/8/2NNN3/2NkN3/2NNN3/8/8/8 b - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  Move test_move = (Move){4,3,3,3};

  TEST_ASSERT_EQUAL_INT(8, moves.count);
  TEST_ASSERT_TRUE(move_list_contains(moves, test_move));
}

void test_move_gen_rook_takes_pieces(void) {
  const char* fen = "3n4/8/8/8/1b1Rq3/8/3p4/8 w - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  Move test_move = (Move){3, 3, 7, 3};

  TEST_ASSERT_EQUAL_INT(9, moves.count);
  TEST_ASSERT_TRUE(move_list_contains(moves, test_move));
}

void test_move_gen_bishop_takes_pieces(void) {
  const char* fen = "7P/2R5/8/4b3/5N2/8/1Q6/8 b - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  Move test_move = (Move) {4, 4, 3, 5};

  TEST_ASSERT_EQUAL_INT(9, moves.count);
  TEST_ASSERT_TRUE(move_list_contains(moves, test_move));
}

int main(void) {
  UNITY_BEGIN();

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

  RUN_TEST(test_move_gen_empty_board);
  RUN_TEST(test_move_gen_start_pos);
  RUN_TEST(test_move_gen_e4);
  RUN_TEST(test_move_gen_pawn_at_end);
  RUN_TEST(test_move_gen_pawn_moves);
  RUN_TEST(test_move_gen_pawn_double_push_white);
  RUN_TEST(test_move_gen_pawn_double_push_black);
  RUN_TEST(test_move_gen_pawn_takes_white);
  RUN_TEST(test_move_gen_pawn_takes_black);
  RUN_TEST(test_move_gen_pawn_takes_en_passant_white);
  RUN_TEST(test_move_gen_pawn_takes_en_passant_black);
  RUN_TEST(test_move_gen_pawn_edge_case_white);
  RUN_TEST(test_move_gen_pawn_edge_case_black);
  RUN_TEST(test_move_gen_knight_centre);
  RUN_TEST(test_move_gen_knight_corner);
  RUN_TEST(test_move_gen_knight_takes_white);
  RUN_TEST(test_move_gen_knight_takes_black);
  RUN_TEST(test_move_gen_knight_blocked_white);
  RUN_TEST(test_move_gen_knight_blocked_black);
  RUN_TEST(test_move_gen_bishop_centre);
  RUN_TEST(test_move_gen_bishop_corner);
  RUN_TEST(test_move_gen_rook_centre);
  RUN_TEST(test_move_gen_rook_corner);
  RUN_TEST(test_move_gen_queen_centre);
  RUN_TEST(test_move_gen_queen_corner);
  RUN_TEST(test_move_gen_king_centre);
  RUN_TEST(test_move_gen_king_corner);
  RUN_TEST(test_move_gen_king_takes_white);
  RUN_TEST(test_move_gen_king_takes_black);
  RUN_TEST(test_move_gen_rook_takes_pieces);
  RUN_TEST(test_move_gen_bishop_takes_pieces);

  return UNITY_END();
}