#include "../include/Queen.hpp"

/**@brief Queen constructor method
*/

Queen::Queen(bool isWhite, int position_X, int position_Y)
{
  this->name = PieceName::Queen;
  this->isWhite = isWhite;
  this->position_X = position_X;
  this->position_Y = position_Y;
  isAlive = true;
  PieceValue = 9;
}

Queen::~Queen()
{
}

/**@brief Function that validates whether the Queen's move is possible
*
*/

bool Queen::IsMovementPossible(int FinalPosition_X, int FinalPosition_Y)
{
  if(FinalPosition_X >= 0 && FinalPosition_Y >= 0 && FinalPosition_X < 8 && FinalPosition_Y < 8 && isAlive) //Piece must be on the board and alive
  {
    int movement_x = abs(FinalPosition_X - position_X);
    int movement_y = abs(FinalPosition_Y - position_Y);

    if((movement_x == 0 || movement_y == 0) && movement_x != movement_y) //Movement only in vertical/horizontal (not both) and final position different from the initial
    {
      return true;
    }

    if(movement_x == movement_y && movement_x > 0) //Check for diagonal movement only and final position different from the initial
    {
      return true;
    }
  }

  return false;
}
