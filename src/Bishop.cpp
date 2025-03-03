#include "../include/Bishop.hpp"

/**@brief Constructor method for the Bishop
*/

Bishop::Bishop(bool isWhite, int position_X, int position_Y)
{
  this->name = PieceName::Bishop;
  this->isWhite = isWhite;
  this->position_X = position_X;
  this->position_Y = position_Y;
  isAlive = true;
  PieceValue = 3;
}

Bishop::~Bishop()
{
}

/**@brief Function that validates whether the Bishop's movement is possible
*/

bool Bishop::IsMovementPossible(int FinalPosition_X, int FinalPosition_Y)
{
  if(FinalPosition_X >= 0 && FinalPosition_Y >= 0 && FinalPosition_X < 8 && FinalPosition_Y < 8 && isAlive) // The piece must be on the board and alive
  {
    int movement_x = abs(FinalPosition_X - position_X);
    int movement_y = abs(FinalPosition_Y - position_Y);

    if(movement_x == movement_y && movement_x > 0) // Checks only diagonal movement and ensures the final position is different from the initial one
    {
      return true;
    }
  }

  return false;
}
