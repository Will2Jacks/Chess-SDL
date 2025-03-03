#ifndef PIECE_HPP_INCLUDED
#include "../include/Piece.hpp"
#endif

#ifndef PAWN_HPP_INCLUDED
#define PAWN_HPP_INCLUDED

#include <iostream>
#include <string>

using namespace std;

/**@brief Pawn class that inherits from Piece
*
*Parameters: Constructor and destructor of Pawn, IsMovementPossible, and
*functions inherited from Piece such as GetColor, GetName, GetPositionX, GetPositionY.
*
*Description: This class defines the Pawn in a standard Chess game. 
*Here, some basic methods are defined to manipulate an object of this class, 
*such as the method to construct and destroy an object of this class, 
*a method to return its color, name, and position on the board, 
*and another to validate whether a move is possible.
*
*/

class Pawn : public Piece
{
  private:
    bool hasDiagonalEnemyRight = false;
    bool hasDiagonalEnemyLeft = false;

  public:
    Pawn(bool, int, int);
    ~Pawn();
    using Piece::GetColor;
    using Piece::GetName;
    using Piece::GetPositionX;
    using Piece::GetPositionY;
    bool IsMovementPossible(int, int);
    void SetDiagonalEnemy(bool, bool);
};

#endif
