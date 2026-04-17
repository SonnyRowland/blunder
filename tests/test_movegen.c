#include "unity.h"
#include "movegen.h"
#include "board.h"
#include "fen.h"
#include "move.h"

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

void test_move_gen_pawn_pinned_white(void){
  const char* fen = "8/8/8/q3P1K1/8/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  TEST_ASSERT_EQUAL_INT(8, moves.count);
}

void test_move_gen_pawn_pinned_black(void){
  const char* fen = "7B/8/5p2/8/3k4/8/8/8 b - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  TEST_ASSERT_EQUAL_INT(8, moves.count);
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

void test_move_gen_knight_pinned_white(void){
  const char* fen = "3r4/8/8/3N4/8/3K4/8/8 w - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  TEST_ASSERT_EQUAL_INT(8, moves.count);
}

void test_move_gen_knight_pinned_black(void) {
  const char* fen = "8/8/8/8/3Rn1k1/8/8/8 b - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  TEST_ASSERT_EQUAL_INT(8, moves.count);
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

void test_move_gen_bishop_pinned_white(void) {
  const char* fen = "3r4/8/8/8/3B4/8/8/3K4 w - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  TEST_ASSERT_EQUAL_INT(5, moves.count);
}

void test_move_gen_bishop_pinned_black(void) {
  const char* fen = "8/8/8/1k1b2R1/8/8/8/8 b - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  TEST_ASSERT_EQUAL_INT(8, moves.count);
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

void test_move_gen_rook_pinned_white(void) {
  const char* fen = "8/6b1/8/8/8/2R5/1K6/8 w - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  TEST_ASSERT_EQUAL_INT(7, moves.count);
}

void test_move_gen_rook_pinned_black(void) {
  const char* fen = "8/6k1/8/4r3/3Q4/8/8/8 b - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  TEST_ASSERT_EQUAL_INT(8, moves.count);
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

void test_move_gen_queen_pinned_white(void) {
  const char* fen = "8/8/8/8/1KQr4/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  TEST_ASSERT_EQUAL_INT(8, moves.count);
}

void test_move_gen_queen_pinned_black(void) {
  const char* fen = "8/8/8/8/1R2q1k1/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  TEST_ASSERT_EQUAL_INT(11, moves.count);
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
  const char* fen = "8/8/2n1n3/3K4/2n1n3/8/8/8 w - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  Move test_move = (Move){4,3,5,4};

  TEST_ASSERT_EQUAL_INT(4, moves.count);
  TEST_ASSERT_TRUE(move_list_contains(moves, test_move));
}

void test_move_gen_king_takes_black(void) {
  const char* fen = "8/8/2N1N3/3k4/2N1N3/8/8/8 b - - 0 1";
  Board board = fen_to_board(fen);
  MoveList moves = generate_legal_moves(board);

  Move test_move = (Move){4,3,3,2};

  TEST_ASSERT_EQUAL_INT(4, moves.count);
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
  RUN_TEST(test_move_gen_pawn_pinned_white);
  RUN_TEST(test_move_gen_pawn_pinned_black);
  RUN_TEST(test_move_gen_knight_centre);
  RUN_TEST(test_move_gen_knight_corner);
  RUN_TEST(test_move_gen_knight_takes_white);
  RUN_TEST(test_move_gen_knight_takes_black);
  RUN_TEST(test_move_gen_knight_blocked_white);
  RUN_TEST(test_move_gen_knight_blocked_black);
  RUN_TEST(test_move_gen_knight_pinned_white);
  RUN_TEST(test_move_gen_knight_pinned_black);
  RUN_TEST(test_move_gen_bishop_centre);
  RUN_TEST(test_move_gen_bishop_corner);
  RUN_TEST(test_move_gen_bishop_pinned_white);
  RUN_TEST(test_move_gen_bishop_pinned_black);
  RUN_TEST(test_move_gen_rook_centre);
  RUN_TEST(test_move_gen_rook_corner);
  RUN_TEST(test_move_gen_rook_pinned_white);
  RUN_TEST(test_move_gen_rook_pinned_black);
  RUN_TEST(test_move_gen_queen_centre);
  RUN_TEST(test_move_gen_queen_corner);
  RUN_TEST(test_move_gen_queen_pinned_white);
  RUN_TEST(test_move_gen_queen_pinned_black);
  RUN_TEST(test_move_gen_king_centre);
  RUN_TEST(test_move_gen_king_corner);
  RUN_TEST(test_move_gen_king_takes_white);
  RUN_TEST(test_move_gen_king_takes_black);
  RUN_TEST(test_move_gen_rook_takes_pieces);
  RUN_TEST(test_move_gen_bishop_takes_pieces);

  return UNITY_END();
}