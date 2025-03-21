#include "../include/Piece.hpp"

Piece::Piece()
  : isAlive(true), position_X(0), position_Y(0), hasMoved(false)
{
}

Piece::~Piece()
{
}

/**@brief Method that returns the color of the piece.
*/
bool Piece::GetColor()
{
  return isWhite;
}

/**@brief Method that returns the name of the piece.
*/
PieceName Piece::GetName()
{
  return name;
}

/**@brief Method that returns the piece's position on the X-axis of the board.
*/
int Piece::GetPositionX()
{
  return position_X;
}

/**@brief Method that returns the piece's position on the Y-axis of the board.
*/
int Piece::GetPositionY()
{
  return position_Y;
}

/**@brief Method that returns a boolean indicating whether the movement is possible.
*/
bool Piece::IsMovementPossible(int FinalPosition_X, int FinalPosition_Y)
{
  return false;
}

void Piece::SetDiagonalEnemy(bool hasDiagonalEnemyRight, bool hasDiagonalEnemyLeft)
{
}

/**@brief Method that sets the X and Y positions of the piece on the board.
*/
void Piece::SetPosition(int position_X, int position_Y)
{
  if(isAlive)
  {
    this->position_X = position_X;
    this->position_Y = position_Y;
    // When a piece is moved, we mark it as having moved.
    hasMoved = true;
  }
}

/**@brief Method that indicates whether the piece is alive or not.
*/
bool Piece::GetIsAlive()
{
  return isAlive;
}

/**@brief Method that kills the piece.
*/
void Piece::SetDead()
{
  isAlive = false;
  this->position_X = -1;
  this->position_Y = -1;
}

/**@brief Method to bring a dead piece back to life.
*/
void Piece::WakeFromDead()
{
  isAlive = true;
}

/**@brief Returns whether the piece has moved.
*/
bool Piece::GetHasMoved()
{
  return hasMoved;
}

/**@brief Sets the moved status for the piece.
*/
void Piece::SetHasMoved(bool moved)
{
  hasMoved = moved;
}
