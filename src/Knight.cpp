#include "../include/Knight.hpp"

/**@brief Knight's constructor method
*/

Knight::Knight(bool isWhite, int position_X, int position_Y)
{
  this->name = PieceName::Knight;
  this->isWhite = isWhite;
  this->position_X = position_X;
  this->position_Y = position_Y;
  isAlive = true;
  PieceValue = 3;
}

Knight::~Knight()
{
}

/**@brief Function that validates if the Knight's movement is possible
 *
*Description: The method checks if the final position is within the board, 
*then verifies if the movement is valid for the Knight and if the 
*final position is different from the position it is already in.
*/

bool Knight::IsMovementPossible(int FinalPosition_X, int FinalPosition_Y)
{
  if(FinalPosition_X >= 0 && FinalPosition_Y >= 0 && FinalPosition_X < 8 && FinalPosition_Y < 8 && isAlive) //The piece must be on the board and alive
  {
    int movement_x = abs(FinalPosition_X - position_X);
    int movement_y = abs(FinalPosition_Y - position_Y);

    if((movement_x == 1 && movement_y == 2) || (movement_x == 2 && movement_y == 1)) //L-shaped movement and final position different from the initial
    {
      return true;
    }
  }

  return false;
}
