#include "../include/Rook.hpp"
#include "../include/King.hpp"
#include <cstdlib>
#include <cmath>

King::King(bool isWhite, int position_X, int position_Y)
{
  this->name = PieceName::King;
  this->isWhite = isWhite;
  this->position_X = position_X;
  this->position_Y = position_Y;
  isAlive = true;
  // A very high value to prevent the king from being "captured"
  PieceValue = 1000000000;
}

King::~King()
{
}

/**@brief Function that validates whether the King's movement is possible.
 *
 * This version supports two kinds of moves:
 *  - Normal move: one square in any direction.
 *  - Castling move: a two-square horizontal move (with no vertical displacement)
 *    provided the King has not previously moved.
 *
 * Note: Path clearance, ensuring that no squares the King passes through are attacked,
 * and verifying the unmoved status of the involved rook must be handled by your
 * higher-level game logic.
 *
 * @param FinalPosition_X The target column (0 to 7).
 * @param FinalPosition_Y The target row (0 to 7).
 *
 * @return true if the move fits one of the patterns above and the King is allowed to move;
 *         false otherwise.
 */
bool King::IsMovementPossible(int FinalPosition_X, int FinalPosition_Y)
{
  // Ensure target square is on board and King is alive.
  if(FinalPosition_X < 0 || FinalPosition_Y < 0 || FinalPosition_X >= 8 || FinalPosition_Y >= 8 || !isAlive)
    return false;

  int dx = abs(FinalPosition_X - position_X);
  int dy = abs(FinalPosition_Y - position_Y);

  // Normal king move: one square in any direction (and not stationary).
  if(dx <= 1 && dy <= 1 && (dx + dy != 0))
  {
    return true;
  }

  // Castling move: must be a two-square horizontal move with no vertical displacement.
  if(dx == 2 && dy == 0)
  {
    // Verify that the King has not moved.
    if(GetHasMoved())
      return false;

    // At this point, we assume that the higher-level game logic will verify:
    // - That the path between the King and the rook is clear.
    // - That the involved rook is present, alive, and has not moved.
    // - That the King does not pass through or end in check.
    return true;
  }

  return false;
}
