#ifndef PIECE_HPP_INCLUDED
#include "../include/Piece.hpp"
#endif

#ifndef ROOK_HPP_INCLUDED
#define ROOK_HPP_INCLUDED

#include <iostream>
#include <string>

using namespace std;

/**@brief Rook Class that inherits from Piece
*
*Parameters: Constructor and destructor of Rook, IsMovementPossible, and
*functions inherited from Piece such as GetColor, GetName, GetPositionX, GetPositionY
*
*Description: This class defines the Rook in a standard Chess game. 
*Here, some of the basic methods to manipulate an object of this class are defined, 
*such as the method to construct and destroy an object of this class, a method to 
*return its color, its name, and its position on the board, and another to validate 
*if the move is possible.
*
*/

class Rook : public Piece
{
  public:
    Rook(bool, int, int);
    ~Rook();
    using Piece::GetColor;
    using Piece::GetName;
    using Piece::GetPositionX;
    using Piece::GetPositionY;
    bool IsMovementPossible(int, int);
};

#endif
