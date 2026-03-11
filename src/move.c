#include "move.h"
#include "board.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool validate_piece_move(Piece piece, Move move);

Board apply_move(Board board, Move move)
{
  // Check piece exists 
  if(board.grid[move.from_rank][move.from_file] == EMPTY)
  {
    printf("No piece here...\n");
    return board;
  } 
  
  // Check move is actually a move (and not just staying still)
  if(move.from_rank == move.to_rank && move.from_file == move.to_file)
  {
    printf("Move must be a move...\n");
    return board;
  }

  // TODO: Ensure move values are valid (i.e from_rank != 10)

  if (!validate_piece_move(board.grid[move.from_rank][move.from_file], move))
  {
    printf("Move is illegal...\n");
    return board;
  }

  printf("Move is legal...\n");

  // TODO: Validate player is not in check

  board.grid[move.to_rank][move.to_file] = board.grid[move.from_rank][move.from_file];
  board.grid[move.from_rank][move.from_file] = EMPTY;

  return board;
}

bool validate_piece_move(Piece piece, Move move)
{

  // TODO: Check no piece is in the way 
  // TODO: Prevent player taking their own piece

  switch (piece) {
    
    case W_PAWN:
    // TODO: amend the following for the instance when the pawn is taking a piece
    if (move.from_file != move.to_file) return false;
    if (move.to_rank - move.from_rank == 1) 
      {
        return true;
      }
      else if (move.from_rank == 1 && move.to_rank == 3) 
      {
        return true;
      }
      else
      {
        return false;
      }
      
    case B_PAWN:
      // TODO: amend the following for the instance when the pawn is taking a piece
      if (move.from_file != move.to_file) return false;
      if (move.from_rank - move.to_rank == 1)
      {
        return true;
      }
      else if (move.from_rank == 6 && move.to_rank == 4)
      {
        return true;
      }
      else
      {
        return false;
      }

    case W_ROOK:
      if ((move.to_rank == move.from_rank) || (move.to_file == move.from_file)) return true;
    return false;

    case B_ROOK:
      if ((move.to_rank == move.from_rank) || (move.to_file == move.from_file)) return true;
    return false;
    
    case W_BISHOP:
      if (abs(move.to_rank - move.from_rank) == abs(move.to_file - move.from_file)) return true;
    return false;

    case B_BISHOP:
      if (abs(move.to_rank - move.from_rank) == abs(move.to_file - move.from_file)) return true;
    return false;

    case W_KNIGHT:
      if (((abs(move.to_file - move.from_file) == 2) && (abs(move.to_rank - move.from_rank) == 1)) || (abs(move.to_file - move.from_file) == 1) && (abs(move.to_rank - move.from_rank) ==  2)) return true;
    return false;

    case B_KNIGHT:
      if (((abs(move.to_file - move.from_file) == 2) && (abs(move.to_rank - move.from_rank) == 1)) || (abs(move.to_file - move.from_file) == 1) && (abs(move.to_rank - move.from_rank) ==  2)) return true;
    return false;

    case W_QUEEN:
      if (abs(move.to_rank - move.from_rank) == abs(move.to_file - move.from_file)) return true;
      if ((move.to_rank == move.from_rank) || (move.to_file == move.from_file)) return true;
    return false;

    case B_QUEEN:
      if (abs(move.to_rank - move.from_rank) == abs(move.to_file - move.from_file)) return true;
      if ((move.to_rank == move.from_rank) || (move.to_file == move.from_file)) return true;
    return false;
    
    case W_KING:
      if ((abs(move.to_rank - move.from_rank) <= 1) && (abs(move.to_file - move.from_file) <= 1)) return true;
    return false;

    case B_KING:
      if ((abs(move.to_rank - move.from_rank) <= 1) && (abs(move.to_file - move.from_file) <= 1)) return true;
    return false;

    default:
      break;
  }

  return false;
}