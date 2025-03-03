#ifndef PIECE_HPP_INCLUDED
#include "../include/Piece.hpp"
#endif

#ifndef QUEEN_HPP_INCLUDED
#define QUEEN_HPP_INCLUDED

#include <iostream>
#include <string>

using namespace std;

/**@brief Queen class that inherits from Piece
*
*Parameters: Constructor and destructor of Queen, IsMovementPossible, and
*functions inherited from Piece such as GetColor, GetName, GetPositionX, GetPositionY
*
*Description: This class defines the Queen in a standard Chess game. 
*Here, some of the basic methods for handling an object of this class are defined, 
*such as the method to construct and destroy an object of this class, 
*a method to return its color, name, and position on the board, 
*and another to validate if a move is possible.
*
*/

class Queen : public Piece
{
  public:
    Queen(bool, int, int);
    ~Queen();
    using Piece::GetColor;
    using Piece::GetName;
    using Piece::GetPositionX;
    using Piece::GetPositionY;
    bool IsMovementPossible(int, int);
};

#endif
