#ifndef PIECE_HPP_INCLUDED
#include "../include/Piece.hpp"
#endif

#ifndef KNIGHT_HPP_INCLUDED
#define KNIGHT_HPP_INCLUDED

#include <iostream>
#include <string>

using namespace std;

/**@brief Class for the Knight, inheriting from Piece
*
*Parameters: Constructor and destructor for Knight, IsMovementPossible, and
*functions inherited from Piece such as GetColor, GetName, GetPositionX, GetPositionY
*
*Description: This class defines the Knight in a standard Chess game. Here, 
*some basic methods for handling an object of this class are defined, 
*such as the method to construct and destroy an object of this class, 
*a method to return its color, name, and position on the board, and another 
*to validate whether the move is possible.
*
*/

class Knight : public Piece
{
  public:
    Knight(bool, int, int);
    ~Knight();
    using Piece::GetColor;
    using Piece::GetName;
    using Piece::GetPositionX;
    using Piece::GetPositionY;
    bool IsMovementPossible(int, int);
};

#endif
