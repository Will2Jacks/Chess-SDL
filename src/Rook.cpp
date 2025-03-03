#include "../include/Rook.hpp"

/**@brief Rook Constructor Method
*
*/

Rook::Rook(bool isWhite, int position_X, int position_Y)
{
  this->name = PieceName::Rook;
  this->isWhite = isWhite;
  this->position_X = position_X;
  this->position_Y = position_Y;
  isAlive = true;
  PieceValue = 5;
}

Rook::~Rook()
{
}

/**@brief Function that validates if the Rook's movement is possible
*
*/

bool Rook::IsMovementPossible(int FinalPosition_X, int FinalPosition_Y)
{
  if(FinalPosition_X >= 0 && FinalPosition_Y >= 0 && FinalPosition_X < 8 && FinalPosition_Y < 8 && isAlive) //Piece must be on the board and alive
  {
    int movement_x = abs(FinalPosition_X - position_X);
    int movement_y = abs(FinalPosition_Y - position_Y);

    if((movement_x == 0 || movement_y == 0) && movement_x != movement_y) //Movement only in vertical/horizontal (not both) and final position different from initial
    {
      return true;
    }
  }

  return false;
}
