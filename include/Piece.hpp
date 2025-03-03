#ifndef PIECE_HPP_INCLUDED
#define PIECE_HPP_INCLUDED

#include <iostream>
#include <string>

enum class PieceName {Empty, Pawn, Knight, Bishop, Rook, Queen, King};

using namespace std;

/**@brief Class that defines a piece
*
*Parameters: Constructor and destructor of Piece, IsMovementPossible
* Name, isWhite, position_X, position_Y, isAlive, PieceValue
*GetPositionX, getPositionY, SetDiagonalEnemy, SetPosition, GetIsAlive
*WakeFromDead and SetDead
*
*Description: This class defines a generic piece, with characteristics 
*common to all pieces, in which other pieces must inherit its methods 
*and characteristics such as position, color, and name, among others.
*
*/

class Piece
{
  protected:
    PieceName name = PieceName::Empty; //Defines which piece it is, according to an enumerator.
    bool isWhite = false; //Defines the color of the piece. NOTE: White pieces start the game and are placed at the top (position 0x0, etc...).
    int position_X = -1; //Defines the piece's position on the X-axis.
    int position_Y = -1; //Defines the piece's position on the Y-axis.
    bool isAlive = false; //True - piece is alive, False - piece is dead.

  public:
    Piece();
    ~Piece();
    int PieceValue = -1;
    bool GetColor(); //Returns true if white, false if black.
    PieceName GetName(); //Returns the name of the piece (identified by an enum).
    int GetPositionX(); //Returns the X position.
    int GetPositionY(); //Returns the Y position.
    virtual bool IsMovementPossible(int, int); //Returns true if movement is possible, false otherwise.
    virtual void SetDiagonalEnemy(bool, bool); //Sets a private variable for the pawn.
    void SetPosition(int, int); //Sets the X and Y position of the piece, respectively.
    bool GetIsAlive(); //Returns True - piece is alive / False - piece is dead.
    void WakeFromDead(); //Revives the piece.
    void SetDead(); //Sets the isAlive flag to dead. When dead, the piece does not revive and its position becomes -1x-1.
};

#endif
