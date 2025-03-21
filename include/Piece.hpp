#ifndef PIECE_HPP_INCLUDED
#define PIECE_HPP_INCLUDED

#include <iostream>
#include <string>

enum class PieceName {Empty, Pawn, Knight, Bishop, Rook, Queen, King};

using namespace std;

/**@brief Class that defines a piece
*
* Parameters: Constructor and destructor of Piece, IsMovementPossible,
* Name, isWhite, position_X, position_Y, isAlive, PieceValue,
* GetPositionX, GetPositionY, SetDiagonalEnemy, SetPosition, GetIsAlive,
* WakeFromDead, SetDead, and the new GetHasMoved/SetHasMoved methods.
*
* Description: This class defines a generic piece with characteristics
* common to all pieces. Other pieces must inherit from it to gain common
* methods and attributes such as position, color, and name.
*
*/

class Piece
{
  protected:
    PieceName name = PieceName::Empty; // Defines which piece it is, according to an enumerator.
    bool isWhite = false;               // Defines the color of the piece. NOTE: White pieces start the game and are placed at the top.
    int position_X = -1;                // Defines the piece's position on the X-axis.
    int position_Y = -1;                // Defines the piece's position on the Y-axis.
    bool isAlive = false;               // True if the piece is alive, false if dead.
    bool hasMoved = false;              // New member: tracks whether the piece has moved.

  public:
    Piece();
    ~Piece();
    int PieceValue = -1;
    bool GetColor();                   // Returns true if white, false if black.
    PieceName GetName();               // Returns the name of the piece (via the enum).
    int GetPositionX();                // Returns the X position.
    int GetPositionY();                // Returns the Y position.
    virtual bool IsMovementPossible(int, int); // Returns true if the movement is possible.
    virtual void SetDiagonalEnemy(bool, bool);   // Sets a variable for pawn diagonal capture logic.
    void SetPosition(int, int);        // Sets the X and Y position of the piece.
    bool GetIsAlive();                 // Returns true if the piece is alive.
    void WakeFromDead();               // Revives the piece.
    void SetDead();                    // Marks the piece as dead and resets its position.

    // New functions to track movement status.
    bool GetHasMoved();                // Returns whether the piece has moved.
    void SetHasMoved(bool moved);      // Sets the moved status.
};

#endif
