#ifndef PIECE_HPP_INCLUDED
#include "../include/Piece.hpp"
#endif

#ifndef BISHOP_HPP_INCLUDED
#define BISHOP_HPP_INCLUDED

#include <iostream>
#include <string>

using namespace std;

/**@brief Bishop class that inherits from Piece
*
*Parameters: Constructor and destructor of Bishop, IsMovementPossible, and
*functions inherited from Piece such as GetColor, GetName, GetPositionX, GetPositionY.
*
*Description: This class defines the bishop in a standard Chess game. 
*Here, some basic methods are defined to manipulate an object of this class, 
*such as the method to construct and destroy an object of this class, 
*a method to return its color, name, and position on the board, 
*and another to validate whether a move is possible.
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
    bool IsMovementPossible(int, int);
};

#endif
