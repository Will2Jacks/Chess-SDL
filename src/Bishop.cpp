#include "../include/Bishop.hpp"
#include "../include/Pawn.hpp"  // Needed to detect pawn obstacles
#include <cstdlib>              // For abs()

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

/**@brief Function that validates whether the Bishop's movement is possible (standard diagonal move)
*/
bool Bishop::IsMovementPossible(int FinalPosition_X, int FinalPosition_Y)
{
  if(FinalPosition_X >= 0 && FinalPosition_Y >= 0 && FinalPosition_X < 8 && FinalPosition_Y < 8 && isAlive)
  {
    int movement_x = abs(FinalPosition_X - position_X);
    int movement_y = abs(FinalPosition_Y - position_Y);

    if(movement_x == movement_y && movement_x > 0)
    {
      return true;
    }
  }

  return false;
}

/**@brief Overloaded function that validates whether the Bishop's movement is possible,
 * allowing it to jump over at most one pawn.
 *
 * @param FinalPosition_X The target column (0 to 7)
 * @param FinalPosition_Y The target row (0 to 7)
 * @param board An 8x8 array of Piece pointers representing the board (nullptr means empty square)
 *
 * @return true if the move is legal under the new rule, false otherwise.
 */
 bool Bishop::IsMovementPossible(int FinalPosition_X, int FinalPosition_Y, Piece* board[8][8])
 {
   // Check board bounds and piece is alive
   if(FinalPosition_X >= 0 && FinalPosition_Y >= 0 && FinalPosition_X < 8 && FinalPosition_Y < 8 && isAlive)
   {
     int movement_x = abs(FinalPosition_X - position_X);
     int movement_y = abs(FinalPosition_Y - position_Y);
 
     // Must be a diagonal move and not a stationary move
     if(movement_x == movement_y && movement_x > 0)
     {
       // Determine the direction of movement for x and y.
       int stepX = (FinalPosition_X - position_X) > 0 ? 1 : -1;
       int stepY = (FinalPosition_Y - position_Y) > 0 ? 1 : -1;
       
       int pawnCount = 0;
       int x = position_X + stepX;
       int y = position_Y + stepY;
       
       // Traverse the diagonal path from the starting square (excluding) to the final square (excluding)
       while(x != FinalPosition_X && y != FinalPosition_Y)
       {
         if(board[y][x] != nullptr)  // If there is a piece on the square
         {
           // Check if the piece is a Pawn using dynamic_cast.
           Pawn* pawn = dynamic_cast<Pawn*>(board[y][x]);
           if(pawn)
           {
             // Only count if the pawn is of the same color.
             if(pawn->GetColor() == isWhite)
               pawnCount++;
             else
               return false;  // Enemy pawn encountered, cannot jump over.
           }
           else
           {
             // There is a non-pawn piece in the way; move is not allowed.
             return false;
           }
         }
         x += stepX;
         y += stepY;
       }
       // Allow the move if there are no obstacles or exactly one same-color pawn in the path.
       if(pawnCount <= 1)
       {
         return true;
       }
     }
   }
 
   return false;
 }
 
