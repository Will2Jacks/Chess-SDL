#ifndef PIECE_HPP_INCLUDED
#include "../include/Piece.hpp"
#endif

#ifndef KING_HPP_INCLUDED
#define KING_HPP_INCLUDED

#include <iostream>
#include <string>

using namespace std;

/**@brief King class that inherits from Piece
*
*Parameters: King constructor and destructor, IsMovementPossible, and
*functions inherited from Piece such as GetColor, GetName, GetPositionX, GetPositionY
*
*Description: This class defines the King in a standard Chess game. 
*It includes basic methods for handling an object of this class, 
*such as the constructor and destructor, a method to return its color, 
*name, and position on the board, and another method to validate if 
*a move is possible.
*
*/

class King : public Piece
{
  public:
    King(bool, int, int);
    ~King();
    using Piece::GetColor;
    using Piece::GetName;
    using Piece::GetPositionX;
    using Piece::GetPositionY;
    bool IsMovementPossible(int, int);
};

#endif
