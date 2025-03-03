#include "../include/Pawn.hpp"

/**@brief Pawn's constructor method
*/

Pawn::Pawn(bool isWhite, int position_X, int position_Y)
{
  this->name = PieceName::Pawn;
  this->isWhite = isWhite;
  this->position_X = position_X;
  this->position_Y = position_Y;
  isAlive = true;
  PieceValue = 1;
}

Pawn::~Pawn()
{
}

/**@brief Function that validates if the Pawn's movement is possible
*/

bool Pawn::IsMovementPossible(int FinalPosition_X, int FinalPosition_Y)
{
  if(FinalPosition_X >= 0 && FinalPosition_Y >= 0 && FinalPosition_X < 8 && FinalPosition_Y < 8 && isAlive)  //Input assertions, X and Y must be positive and greater than or equal to zero and less than 8 (to be on the board) and be alive
  {
    //Calculation of displacement between the piece's position and the new move
    int movement_x = FinalPosition_X - position_X;
    int movement_y = FinalPosition_Y - position_Y;

    if(movement_x == 0 || ((movement_x == -1 && hasDiagonalEnemyLeft) || (movement_x == 1 && hasDiagonalEnemyRight))) //Checks if the Pawn can capture diagonally
    {
      if((isWhite && movement_y < 0) || (!isWhite && movement_y > 0)) //Prevents the Pawn from moving backward.
      {
        movement_y = abs(movement_y);
        if(movement_y == 2 && movement_x == 0) //Move two squares (cannot do this when capturing a piece diagonally)
        {
          if(isWhite && position_Y == 6) //Checks if it's white and if it's the first move
          {
            return true;
          }

          if(!isWhite && position_Y == 1) //Checks if it's black and if it's the first move
          {
            return true;
          }

          return false; //If it's not the first move, it cannot move two squares.
        }

        if(movement_y == 1) //Move only one square(either straight or diagonally-to capture)
        {
          return true;
        }
      }
    }
  }

  return false;
}

/**@brief Method that sets an enemy in the diagonal position relative to the Pawn's position
*
*Description: If the color of the piece in the left or right diagonal 
*relative to the Pawn's position is different from the Pawn's color, 
*then the diagonal piece is considered an enemy and a true value is set 
*in the class variable indicating if there is an enemy in the left or 
*right diagonal
*/

void Pawn::SetDiagonalEnemy(bool hasDiagonalEnemyLeft, bool hasDiagonalEnemyRight)
{
  if(isWhite)
  {
    this->hasDiagonalEnemyRight = hasDiagonalEnemyRight;
    this->hasDiagonalEnemyLeft = hasDiagonalEnemyLeft;
  }
  else
  {
    this->hasDiagonalEnemyRight = hasDiagonalEnemyLeft;
    this->hasDiagonalEnemyLeft = hasDiagonalEnemyRight;
  }

}
