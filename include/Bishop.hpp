#ifndef BISHOP_HPP_INCLUDED
#define BISHOP_HPP_INCLUDED

#include <iostream>
#include <string>
#include "Piece.hpp" // Assuming Piece.hpp is in the include folder

/**@brief Bishop class that inherits from Piece
 *
 * Parameters: Constructor and destructor of Bishop, IsMovementPossible, and
 * functions inherited from Piece such as GetColor, GetName, GetPositionX, GetPositionY.
 *
 * Description: This class defines the bishop in a standard Chess game. 
 * Here, some basic methods are defined to manipulate an object of this class, 
 * such as the method to construct and destroy an object of this class, 
 * a method to return its color, name, and position on the board, 
 * and another to validate whether a move is possible.
 *
 */
class Bishop : public Piece
{
  public:
    Bishop(bool, int, int);
    ~Bishop();
    using Piece::GetColor;
    using Piece::GetName;
    using Piece::GetPositionX;
    using Piece::GetPositionY;
    
    // Original movement check (diagonal move without jump over)
    bool IsMovementPossible(int, int);
    
    // Overloaded movement check that allows bishop to jump over at most one pawn
    // board is an 8x8 array of Piece pointers (nullptr if square is empty)
    bool IsMovementPossible(int FinalPosition_X, int FinalPosition_Y, Piece* board[8][8]);
};

#endif
