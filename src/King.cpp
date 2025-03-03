#include "../include/King.hpp"

/**@brief King constructor method
 *
*Description: This method assigns a name, color, value, 
*X and Y positions, and sets the piece as alive.
*/

King::King(bool isWhite, int position_X, int position_Y)
{
  this->name = PieceName::King;
  this->isWhite = isWhite;
  this->position_X = position_X;
  this->position_Y = position_Y;
  isAlive = true;
  PieceValue = 1000000000;
}

King::~King()
{
}

/**@brief Function that validates whether the King's movement is possible
*
*Description: This method checks if the final position is within the board, 
*then verifies whether the movement is valid for the King and if the 
*final position is different from the current position.
*/

bool King::IsMovementPossible(int FinalPosition_X, int FinalPosition_Y)
{
  if(FinalPosition_X >= 0 && FinalPosition_Y >= 0 && FinalPosition_X < 8 && FinalPosition_Y < 8 && isAlive) // The piece must be on the board and alive
  {
    int movement_x = abs(FinalPosition_X - position_X);
    int movement_y = abs(FinalPosition_Y - position_Y);

    if(movement_x == 1 || movement_y == 1) // The King can only move one square at a time
    {
      if((movement_x == 0 || movement_y == 0) && movement_x != movement_y) // Moves only vertically/horizontally (not both) and final position is different from the initial one
      {
        return true;
      }

      if(movement_x == movement_y && movement_x > 0) // Validates diagonal movement only and final position is different from the initial one
      {
        return true;
      }
    }
  }
  return false;
}
