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
  RUN_TEST(test_move_gen_knight_centre);
  RUN_TEST(test_move_gen_knight_corner);
  RUN_TEST(test_move_gen_bishop_centre);
  RUN_TEST(test_move_gen_bishop_corner);
  RUN_TEST(test_move_gen_rook_centre);
  RUN_TEST(test_move_gen_rook_corner);
  RUN_TEST(test_move_gen_queen_centre);
  RUN_TEST(test_move_gen_queen_corner);
  RUN_TEST(test_move_gen_king_centre);
  RUN_TEST(test_move_gen_king_corner);
  RUN_TEST(test_move_gen_rook_takes_pieces);
  RUN_TEST(test_move_gen_bishop_takes_pieces);

  return UNITY_END();
}