#include "../include/Piece.hpp"
#include "../include/Pawn.hpp"
#include "../include/Knight.hpp"
#include "../include/Bishop.hpp"
#include "../include/Rook.hpp"
#include "../include/Queen.hpp"
#include "../include/King.hpp"
#include "../include/States.hpp"
#include "../include/GameState.hpp"
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

/**@brief Constructor method for game states
*
*Specification contract: The method should create new pieces, 
*placing them on the board, defining their positions and their colors.
*
*/

States::States(void)
{
  int i;

// Initialization of pawns
  for(i=0;i<=7;i++)
  {
    white_pieces[i] = new Pawn(true, i, 6);
    black_pieces[i] = new Pawn(false, i, 1);
  }


// Initialization of white pieces
  white_pieces[8]  = new Rook(true, 0, 7);
  white_pieces[9]  = new Knight(true, 1, 7);
  white_pieces[10] = new Bishop(true, 2, 7);
  white_pieces[11] = new Queen(true, 3, 7);
  white_pieces[12] = new King(true, 4, 7);
  white_pieces[13] = new Bishop(true, 5, 7);
  white_pieces[14] = new Knight(true, 6, 7);
  white_pieces[15] = new Rook(true, 7, 7);

// Initialization of black pieces
  black_pieces[8]  = new Rook(false, 0, 0);
  black_pieces[9]  = new Knight(false, 1, 0);
  black_pieces[10] = new Bishop(false, 2, 0);
  black_pieces[11] = new Queen(false, 3, 0);
  black_pieces[12] = new King(false, 4, 0);
  black_pieces[13] = new Bishop(false, 5, 0);
  black_pieces[14] = new Knight(false, 6, 0);
  black_pieces[15] = new Rook(false, 7, 0);

  pieceTurn = true;
}

/**@brief Method that determines if there is a piece in the way

It specifically checks whether there is any obstacle in the path between a piece's current position and a given position(important: between, the target position is excluded).  It returns an enumeration value indicating whether the path is clear (Empty), blocked by a friendly piece (Friend), or blocked by an enemy piece (Enemy).
*/

Obstacles States::IsInTheWay(Piece * piece, int position_X, int position_Y)
{
  int i,j;
  Piece ** aux;

  switch(piece->GetName())
  { 
    /* Since knights move in an “L” shape and can jump over other pieces, if the piece is a knight, the function immediately returns Obstacles::Empty (meaning no obstacles are considered). */

    case PieceName::Knight :
      return Obstacles::Empty;
      break;

    default:
      int displacement_x = position_X-piece->GetPositionX();
      int displacement_y = position_Y-piece->GetPositionY();
      int displacement_loop, vertical, horizontal;

      for(i=0;i<=15;i++)
      {
        aux = white_pieces; //first, the white pieces are considered, then the black pieces are considered, the for loop variable 'j' handles this.
        for(j=0;j<=1;j++)
        {
          displacement_loop = 0;
          vertical = 0;
          horizontal = 0;

          displacement_x != 0 ? displacement_loop = displacement_x : displacement_loop = displacement_y;
          displacement_loop = abs(displacement_loop);

          while(displacement_loop > 1)  //since only intermediate squares are checked
          {
            if(abs(displacement_x) != abs(displacement_y))
            {
              displacement_y > 0 ? vertical++ : (displacement_y != 0 ? vertical-- : vertical = 0);
              displacement_x > 0 ? horizontal++ : (displacement_x != 0 ? horizontal-- : horizontal = 0);
            }
            else
            {
              displacement_y > 0 ? vertical++ : (displacement_y != 0 ? vertical-- : vertical = 0);
              displacement_x > 0 ? horizontal++ : (displacement_x != 0 ? horizontal-- : horizontal = 0);
            }

            //the below line is the core obstacle checking logic
            if((aux[i]->GetPositionX() == (piece->GetPositionX() + horizontal)) &&
               (aux[i]->GetPositionY() == (piece->GetPositionY() + vertical)))
            { 
              // if both are of same color, they are friends, else enemies
              if((piece->GetColor() && aux[i]->GetColor()) || (!piece->GetColor() && !aux[i]->GetColor()))
              {
                return Obstacles::Friend;
              }
              else
              {
                return Obstacles::Enemy;
              }
            }
            displacement_loop--;
          }
          aux = black_pieces;
        }
      }
      return Obstacles::Empty;
      break;
  }
}

/**@brief 
*
*Parameters: There are no parameters
*
*Error Handling: There is no error handling
*
*Description:
*
*Preconditions: There are no preconditions
*
*Requirements: 
*
*Assumptions: 
*
*Postconditions: There are no postconditions
*
*Explicit interface: None
*
*Implicit interface: None
*
*Specification contract: 
*
*/

/*
The following function determines what kind of piece (if any) occupies a specific board square
given by position_X and position_Y. Here piece only plays the role of determining the piece(that is one at position_X and position_y) as enemy or friend
*/

Obstacles States::IsInTheSpot(Piece * piece, int position_X, int position_Y)
{
  int i,j;
  Piece ** aux;

  for(i=0;i<=15;i++)
  {
    aux = white_pieces;
    for(j=0;j<=1;j++)
    {
      if((aux[i]->GetPositionX() == position_X) && (aux[i]->GetPositionY() == position_Y))
      {
        if((piece->GetColor() && aux[i]->GetColor()) || (!piece->GetColor() && !aux[i]->GetColor()))
        {
          return Obstacles::Friend;
        }
        else
        {
          return Obstacles::Enemy;
        }
      }
      aux = black_pieces;
    }
  }
  return Obstacles::Empty;
}

/**@brief Method that checks if the king is in check
*
*Parameters: A boolean indicating the king's color and two 
*positions that indicate his position on the board.
*
*Error Handling: It checks whether the move towards the king is possible and whether there are no possible moves for the king.
*
*Description: This method checks if the king is in check by verifying if an enemy piece can reach the king and if the path to the king is clear.
*
*Preconditions: A boolean indicating the king's color and two integers indicating his position on the board.
*
*Requirements: The king's positions must be valid board positions.
*
*Assumptions: If the king is in check, the method should return true.
*
*Postconditions: Returns a boolean (true or false) indicating whether the king is in check.
*
*Explicit interface: None
*
*Implicit interface: None
*
*Specification contract: 
*
*/

bool States::IsCheck(bool kingColor, int position_X, int position_Y)
{ 
  // if King is white, enemy is black and vice versa
  Piece ** aux;
  kingColor ? aux = black_pieces : aux = white_pieces;

  for(int i = 0; i<16; i++)
  { 
    //Pawns have unique movement and capture rules in chess. While most pieces use the same pattern for moving and capturing (like a bishop moving diagonally both for moving and capturing), pawns normally move straight ahead but capture diagonally. This difference means that their move validation requires additional logic to correctly determine when a pawn can capture an enemy piece.

    //For pieces like rooks, bishops, and queens, the standard obstacle checking in IsInTheWay is sufficient because their movement and capture patterns are identical

    SetPawnDiagonalEnemies(true, aux[i], position_X, position_Y); // Sets the pawn's diagonal enemy markers, so that the King is not moved to such a (position_X,position_Y) which can be captured by a pawn
    if(aux[i]->IsMovementPossible(position_X, position_Y) &&
    (IsInTheWay(aux[i], position_X, position_Y) == Obstacles::Empty))  // Checks if enemy pieces can reach the king and if the path is clear.
      return true;
    SetPawnDiagonalEnemies(false, aux[i], -1, -1); // Removes the pawn's diagonal enemy markers
  }

  return false;
}

/**@brief 
*
*Parameters: There are no parameters
*
*Error Handling: There is no error handling
*
*Description:
*
*Preconditions: There are no preconditions
*
*Requirements: 
*
*Assumptions: 
*
*Postconditions: There are no postconditions
*
*Explicit interface: None
*
*Implicit interface: None
*
*Specification contract: 
*
*/

//Function to move piece to (position_X, position_Y)

bool States::MovePiece(Piece * piece, int position_X, int position_Y)
{
  SetPawnDiagonalEnemies(true, piece, -1, -1); // Sets the pawn's diagonal enemy markers
  Obstacles isIntheSpot = IsInTheSpot(piece, position_X, position_Y); //checks the type of piece(if empty, then Empty piece) that is occupying (position_X,position_Y)

  //If piece can (logically,according to rules of the game, not neccessarily the current state of the game) move to that position, and path is free and position is empty or enemy and it is this piece's turn (when moving, the turn also gets important)

  if(piece->IsMovementPossible(position_X, position_Y) &&
  (IsInTheWay(piece, position_X, position_Y) == Obstacles::Empty) &&
  (isIntheSpot != Obstacles::Friend) && (pieceTurn == piece->GetColor()))
  {
    SetPawnDiagonalEnemies(false, piece, -1, -1); // Removes the pawn's diagonal enemy markers

    //If I wanted to move a King to the position, but moving it there causes Check, then I can't move

    if(piece->GetName() == PieceName::King)
      if(IsCheck(piece->GetColor(), position_X, position_Y))
        return false;

    //If I wanted to move a Pawn straight, but I can't move it if it is blocked by enemy
    if(piece->GetName() == PieceName::Pawn)  // In case there is an enemy in front of the pawn and it is trying to move forward (it cannot capture or move)
      if(isIntheSpot == Obstacles::Enemy && (position_X - piece->GetPositionX() == 0))
        return false;

    //If the spot is occupied by enemy, then I eat it
    if(isIntheSpot == Obstacles::Enemy)
      EatPiece(position_X, position_Y);

    //If the spot is empty, that is this piece's new position
    piece->SetPosition(position_X, position_Y);
    TransformPawn(piece); //If pawn reaches the opposite end, transform it
    pieceTurn = !pieceTurn; //toggle pieceTurn
    return true;  //move was successful
  }
  SetPawnDiagonalEnemies(false, piece, -1, -1); // Removes the pawn's diagonal enemy markers
  return false;
}

/**@brief 
*
*Parameters: There are no parameters
*
*Error Handling: There is no error handling
*
*Description:
*
*Preconditions: There are no preconditions
*
*Requirements: 
*
*Assumptions: 
*
*Postconditions: There are no postconditions
*
*Explicit interface: None
*
*Implicit interface: None
*
*Specification contract: 
*
*/

// This function performs the eating of a piece located at (position_X,position_Y)
void States::EatPiece(int position_X, int position_Y)
{
  Piece ** aux;
  int i, j;

  //For all the pieces on the board, (first white and then black), if the piece's position is equal to the position to be Eaten, eat it(that is set it to Dead)

  aux = white_pieces;
  for(i = 0; i < 2; i++)
  {
    for(j = 0; j < 16; j++)
    {
      if((aux[j]->GetPositionX() == position_X) && (aux[j]->GetPositionY() == position_Y))
      {
        aux[j]->SetDead();
      }
    }
    aux = black_pieces;
  }
}

/**@brief 
*
*Parameters: There are no parameters
*
*Error Handling: There is no error handling
*
*Description:
*
*Preconditions: There are no preconditions
*
*Requirements: 
*
*Assumptions: 
*
*Postconditions: There are no postconditions
*
*Explicit interface: None
*
*Implicit interface: None
*
*Specification contract: 
*
*/

/*
This function takes parameters:
check: if true, the function actively checks for enemies, in the left and right diagonal positions of the pawn
futureEnemyX: X position to which King is set to be moved
futureEnemyY: Y position to which King is set to be moved
*/

void States::SetPawnDiagonalEnemies(bool check, Piece * piece, int futureEnemyX, int futureEnemyY)
{ 
  // i==0, sets right Diagonal, i==1, sets left Diagonal
  // verticalDirection is the y-direction of enemy piece, horizontalDirection is the x-direction of enemy piece
  // the left and right, are set to true if there are respective enemies

  int i, verticalDirection, horizontalDirection;
  bool left = false, right = false;

  if(piece->GetName() == PieceName::Pawn) //works only for Pawn
  {
    if(check) //if we have to check
    { 
      // Color 1: White, Color 0: Black. Since White moves forward as y decreases, and vice versa, so if white piece, verticalDirection=piece->GetPositionY() - 1, else verticalDirection=piece->GetPositionY() + 1 

      //for i==0, we check right diagonal, for i==1, left diagonal

      piece->GetColor() ? (verticalDirection = (piece->GetPositionY() - 1)) : (verticalDirection = (piece->GetPositionY() + 1));
      horizontalDirection = (piece->GetPositionX() + 1);
      for(i = 0; i < 2; i++)
      { 
        // If there is an enemy in the pos(hD,vD), then 
        // if i==0
        // if piece is white: then right diagonal means right enemy, else if piece is black, right diagonal, is left enemy

        // if i==1
        // if piece is white: then left diagonal means left enemy, else if piece is black, left diagonal, is right enemy

        if(IsInTheSpot(piece, horizontalDirection, verticalDirection) == Obstacles::Enemy)
          (i == 0) ? (piece->GetColor() ? right = true : left = true) : (piece->GetColor() ? left = true : right = true);

        horizontalDirection = (piece->GetPositionX() -1); // for left diagonal, hD is changed
      }

      // The below check is done only if the futureEnemyX and futureEnemyY is the position to which the king is set to be moved. This is done to avoid moving the king to a check position

      if((abs(futureEnemyX - piece->GetPositionX()) == 1) && (abs(futureEnemyY - piece->GetPositionY()) == 1) && (futureEnemyX != -1) && (futureEnemyY != -1))
      { 
        // if piece is White, then right movement means right enemy, and vice versa
        // if piece is black ,then right movement means left enemy, and vice versa

        piece->GetColor() ? ((futureEnemyX - piece->GetPositionX()) == 1 ? right = true : left = true) : ((futureEnemyX - piece->GetPositionX()) == -1 ? right = true : left = true);
      }
    }
    piece->SetDiagonalEnemy(left, right);
  }
}

/**@brief 
*
*Parameters: There are no parameters
*
*Error Handling: There is no error handling
*
*Description:
*
*Preconditions: There are no preconditions
*
*Requirements: 
*
*Assumptions: 
*
*Postconditions: There are no postconditions
*
*Explicit interface: None
*
*Implicit interface: None
*
*Specification contract: 
*
*/

bool States::IsCheckMate(bool kingColor)
{
  Piece ** aux; //Pieces of friend's color
  Piece ** aux2;  //Pieces of enemy's color
  int i, j, k, x, y;

  //For white pieces, friends are white, enemies are black, for black it's the opposite
  if(kingColor)
  {
    aux = white_pieces;
    aux2 = black_pieces;
  }
  else
  {
    aux = black_pieces;
    aux2 = white_pieces;
  }

  //aux[12] stores the king, its color, its position. If the piece is not King or the King is not in check, then no question of checkMate
  if(IsCheck(aux[12]->GetColor(), aux[12]->GetPositionX(), aux[12]->GetPositionY()))
  {
    x = aux[12]->GetPositionX();
    y = aux[12]->GetPositionY();

  // Possible moves for the King
  // If there is at least one position such that , moving to that position is not check for King, and there is no friend piece at that pos, and there is no Enemy Piece that can reach there and there is no Enemy Piece whose way the King lies in( and the enemy can reach the King), and the King can move there, then the King is not in CheckMate

    for(i=-1;i<2;i++)
      for(j=-1;j<2;j++)
        for(k = 0; k < 16; k++)
          if(!IsCheck(kingColor, x+i, y+j) && IsInTheSpot(aux[12], x+i, y+j) != Obstacles::Friend &&
          (!aux2[k]->IsMovementPossible(x+i,y+j) || IsInTheWay(aux2[k], x+i, y+j) != Obstacles::Empty) &&
          aux[12]->IsMovementPossible(x+i,y+j))
            return false;

    return true;
  }
  return false;
}

/**@brief 
*
*Parameters: There are no parameters
*
*Error Handling: There is no error handling
*
*Description:
*
*Preconditions: There are no preconditions
*
*Requirements: 
*
*Assumptions: 
*
*Postconditions: There are no postconditions
*
*Explicit interface: None
*
*Implicit interface: None
*
*Specification contract: 
*
*/

GameResult States::WhoWon(void)
{
  bool white = false, black = false;
  int i;

  white = IsCheckMate(true) || !white_pieces[12]->GetIsAlive(); //condition for black to win
  black = IsCheckMate(false) || !black_pieces[12]->GetIsAlive();  //condition for white to win

  if(white && black)
    return GameResult::Draw;  //if both have lost , the game is draw

    //If neither is in checkMate or have lost their king, then the game is No contest
    //If neither is in checkMate and only King remains, then the game is Draw
  if(!white && !black)
  {
    for(i = 0; i < 16; i++)
    {
      if((white_pieces[i]->GetIsAlive() && (white_pieces[i]->GetName() != PieceName::King)) || (black_pieces[i]->GetIsAlive() && (black_pieces[i]->GetName() != PieceName::King)))
        return GameResult::NoContest;
    }
    return GameResult::Draw;
  }

  if(white)
    return GameResult::BlackWins;

  if(black)
    return GameResult::WhiteWins;

  return GameResult::NoContest;
}

/**@brief 
*
*Parameters: There are no parameters
*
*Error Handling: There is no error handling
*
*Description:
*
*Preconditions: There are no preconditions
*
*Requirements: 
*
*Assumptions: 
*
*Postconditions: There are no postconditions
*
*Explicit interface: None
*
*Implicit interface: None
*
*Specification contract: 
*
*/

// Just checks whether the movement of 'piece' to (position_X,position_Y) is valid or not

bool States::IsPositionValid(Piece * piece, int position_X, int position_Y)
{
  Obstacles obstacle;
  //A King cannot move to a position if that position creates a check
  if(piece->GetName() == PieceName :: King)
  {
    if(IsCheck(piece->GetColor(), position_X, position_Y))
      return false;
  }
  SetPawnDiagonalEnemies(true, piece, -1, -1); // Sets the pawn's diagonal enemy markers
  obstacle = IsInTheSpot(piece, position_X, position_Y);
  // If piece can move to the pos, and its path is empty, and there is either enemy or empty piece at that pos: 
  if(piece->IsMovementPossible(position_X, position_Y) &&
    (IsInTheWay(piece, position_X, position_Y) == Obstacles::Empty) &&
    (obstacle != Obstacles::Friend))
    {
      SetPawnDiagonalEnemies(false, piece, -1, -1); // Removes the pawn's diagonal enemy 
      // For pawn, movement and eating are different. So if the piece is pawn, and there was an enemy at pos, then pawn can move only if the movement was a diagonal one, and not straight
      if((piece->GetName() == PieceName :: Pawn) && (obstacle == Obstacles::Enemy))
      {
        if(piece->GetPositionX() - position_X != 0)
          return true;
      }
      else
      {
        return true;
      }
    }

  SetPawnDiagonalEnemies(false, piece, -1, -1); // Removes the pawn's diagonal enemy markers
  return false;
}

/**@brief 
*
*Parameters: There are no parameters
*
*Error Handling: There is no error handling
*
*Description:
*
*Preconditions: There are no preconditions
*
*Requirements: 
*
*Assumptions: 
*
*Postconditions: There are no postconditions
*
*Explicit interface: None
*
*Implicit interface: None
*
*Specification contract: 
*
*/

// This function just returns the piece present at (position_X,position_Y). It loops over all the 16 pieces of White and Black colour, returns any matching one, else returns an emptyPiece 
Piece * States::GetPiece(int position_X, int position_Y)
{
  if((position_X >= 0) && (position_Y >=0) && (position_X < 8) && (position_Y < 8))
  {
    for(int i = 0; i < 16; i++)
    {
      if(white_pieces[i]->GetPositionX() == position_X && white_pieces[i]->GetPositionY() == position_Y)
        return white_pieces[i];
      if(black_pieces[i]->GetPositionX() == position_X && black_pieces[i]->GetPositionY() == position_Y)
        return black_pieces[i];
    }
  }
  return emptyPiece;
}

/**@brief 
*
*Parameters: There are no parameters
*
*Error Handling: There is no error handling
*
*Description:
*
*Preconditions: There are no preconditions
*
*Requirements: 
*
*Assumptions: 
*
*Postconditions: There are no postconditions
*
*Explicit interface: None
*
*Implicit interface: None
*
*Specification contract: 
*
*/

// This funciton is used to set up the pieces at the beginning of the game. It sets the 'piece' up at (position_X,position_Y)
bool States::SetPiece(Piece *piece, int position_X, int position_Y)
{
  if((position_X >= 0) && (position_Y >=0) && (position_X < 8) && (position_Y < 8))
    if(IsInTheSpot(piece, position_X, position_Y) == Obstacles::Empty)
    {
      piece->WakeFromDead();
      piece->SetPosition(position_X, position_Y);
      return true;
    }

  return false;
}


/**@brief 
*
*Parameters: There are no parameters
*
*Error Handling: There is no error handling
*
*Description:
*
*Input Assertions: There are no input assertions
*
*Requirements: 
*
*Assumptions: 
*
*Output Assertions: There are no output assertions
*
*Explicit Interface: There is no explicit interface
*
*Implicit Interface: There is no implicit interface
*
*Specification Contract: 
*
*/

// In this function the best move is played(according to difficulty level)
// If color is 1, piece refers to white pieces, else black pieces. 
// Piece Values refer to the value of the best move for each piece of that color
// Now for each piece of the color, if there is a valuable move, its value is set to value of the movement
// According to the difficulty of the game, either the most, 2nd most or 3rd most valuable movement (each corresponding to a different piece, unfortunately) is played

void States::PlayBestMove(bool color, Level difficulty)
{
  Piece ** piece;
  PiecesValues * bestMoves;
  int values[16], i, n, levelSelected;
  bool result;

  if(color)
  {
    piece = white_pieces;
    bestMoves = white_values;
  }
  else
  {
    piece = black_pieces;
    bestMoves = black_values;
  }

  UpdateBestMoves();

  for(i = 0; i < 16; i++)
  {
    if((bestMoves[i].max_Value_X != -1) && (bestMoves[i].max_Value_Y != -1))
    {
      values[i] = bestMoves[i].value;
    }
    else
    {
      values[i] = -2000000000;
    }
  }

  n = sizeof(values)/sizeof(values[0]);
  sort(values, values + n);

  switch(difficulty)
  {
    case Level::Hard:
      levelSelected = 15;
      break;

    case Level::Medium:
      levelSelected = 14;
      break;

    case Level::Easy:
      levelSelected = 13;
      break;
  }

  for(i = 0; i < 16; i++)
  {
    if((bestMoves[i].value == values[levelSelected]) && (bestMoves[i].max_Value_X != -1) && (bestMoves[i].max_Value_Y != -1))
    {
      result = MovePiece(piece[i], bestMoves[i].max_Value_X, bestMoves[i].max_Value_Y);
      return;
    }
  }
}

/**@brief 
*
*Parameters: There are no parameters
*
*Error Handling: There is no error handling
*
*Description:
*
*Input Assertions: There are no input assertions
*
*Requirements: 
*
*Assumptions: 
*
*Output Assertions: There are no output assertions
*
*Explicit Interface: There is no explicit interface
*
*Implicit Interface: There is no implicit interface
*
*Specification Contract: 
*
*/

//This function updates the best moves for all the 32 pieces on the board
// It checks for each piece, all the 64 squares on the board and then moves it to the square with the maximum value for it
//However,unfortunately it prioritises capturing a piece to a strategic movement. In chess winning should be prioritised more than capturing valuable pieces

void States::UpdateBestMoves(void)
{
  int i, x, y, l, maxValue = -20;
  Obstacles obstacle;
  PiecesValues  * aux;
  Piece ** aux2;

  // Clear both arrays of best moves.
  for(i = 0; i < 16; i++)
  {
    white_values[i].max_Value_X = -1;
    white_values[i].max_Value_Y = -1;
    white_values[i].value = -20;
    black_values[i].max_Value_X = -1;
    black_values[i].max_Value_Y = -1;
    black_values[i].value = -20;
  }

  // Calculate the best moves for each piece.
  for(i = 0; i < 16; i++)
  {
    aux = white_values;
    aux2 = white_pieces;
    for(l = 0; l < 2; l++)
    {
      for(x = 0; x < 8; x++)
      {
        for(y = 0; y < 8; y++)
        {
          if(IsPositionValid(aux2[i], x, y))
          {
            obstacle = IsInTheSpot(aux2[i], x, y);
            obstacle == Obstacles::Enemy ? maxValue = GetPiece(x, y)->PieceValue - aux2[i]->PieceValue : maxValue = - aux2[i]->PieceValue;
            if(maxValue > aux[i].value)
            {
              aux[i].max_Value_X = x;
              aux[i].max_Value_Y = y;
              aux[i].value = maxValue;
            }
          }
        }
      }
      maxValue = -10;
      aux = black_values;
      aux2 = black_pieces;
    }
  }
}

/**@brief 
*
*Parameters: There are no parameters
*
*Error Handling: There is no error handling
*
*Description:
*
*Input Assertions: There are no input assertions
*
*Requirements: 
*
*Assumptions: 
*
*Output Assertions: There are no output assertions
*
*Explicit Interface: There is no explicit interface
*
*Implicit Interface: There is no implicit interface
*
*Specification Contract: 
*
*/

// sets which piece's turn is now
void States::SetPieceTurn(bool pieceTurn)
{
  this->pieceTurn = pieceTurn;
}

/**@brief 
*
*Parameters: There are no parameters
*
*Error Handling: There is no error handling
*
*Description:
*
*Input Assertions: There are no input assertions
*
*Requirements: 
*
*Assumptions: 
*
*Output Assertions: There are no output assertions
*
*Explicit Interface: There is no explicit interface
*
*Implicit Interface: There is no implicit interface
*
*Specification Contract: 
*
*/

// returns which piece's turn is now
bool States::GetPieceTurn(void)
{
  return this->pieceTurn;
}

/**@brief 
*
*Parameters: There are no parameters
*
*Error Handling: There is no error handling
*
*Description:
*
*Input Assertions: There are no input assertions
*
*Requirements: 
*
*Assumptions: 
*
*Output Assertions: There are no output assertions
*
*Explicit Interface: There is no explicit interface
*
*Implicit Interface: Pointer manipulations of the piece object
*
*Specification Contract: 
*
*/
void States::SaveGame(GameMode mode)
{
  FILE *fp = NULL;
  int i, j;
  Piece ** aux;
  char print;

  if(mode == GameMode::GAME_MODE_PVP)
    fp = fopen("output_PvP.pgn","w");
  if(mode == GameMode::GAME_MODE_CPU)
    fp = fopen("output_CPU.pgn","w");
  if(mode == GameMode::GAME_MODE_EDIT)
    fp = fopen("output_EDIT.pgn","w");

  if(fp == NULL)
    return;

  fprintf(fp, "%s", "[Piece Turn]:");
  fprintf(fp, "%c%c", pieceTurn ? 'w' : 'b', '\n');
  fprintf(fp, "%s", "[White Piece Board]:");
  aux = white_pieces;
  for(j = 0; j < 2; j++)
  {
    for(i = 0; i < 16; i++)
    {
      if(aux[i]->GetIsAlive())
      {
        switch (aux[i]->GetName())
        {
          case PieceName::Pawn:
            print = 'P';
            break;
          case PieceName::Bishop:
            print = 'B';
            break;
          case PieceName::Rook:
            print = 'R';
            break;
          case PieceName::Knight:
            print = 'N';
            break;
          case PieceName::Queen:
            print = 'Q';
            break;
          case PieceName::King:
            print = 'K';
            break;
        }
        fprintf(fp, "%c,%d,%d,%c", print, aux[i]->GetPositionX(), aux[i]->GetPositionY(), '|');
      }
      else
      {
        fprintf(fp, "%c%c", 'x', '|');
      }
    }
    if(j == 0)
    {
      fprintf(fp, "%c", '\n');
      fprintf(fp, "%s", "[Black Piece Board]:");
      aux = black_pieces;
    }
  }
  fclose(fp);
}

/**@brief 
*
*Parameters: There are no parameters
*
*Error Handling: There is no error handling
*
*Description:
*
*Input Assertions: There are no input assertions
*
*Requirements: 
*
*Assumptions: 
*
*Output Assertions: There are no output assertions
*
*Explicit Interface: There is no explicit interface
*
*Implicit Interface: Pointer manipulations of the piece object
*
*Specification Contract: 
*
*/
void States::LoadGame(GameMode mode)
{
  FILE *fp = NULL;
  int i, j;
  char read[86];
  Piece ** aux;

  if(mode == GameMode::GAME_MODE_PVP)
    fp = fopen("output_PvP.pgn","r");
  if(mode == GameMode::GAME_MODE_CPU)
    fp = fopen("output_CPU.pgn","r");
  if(mode == GameMode::GAME_MODE_EDIT)
    fp = fopen("output_EDIT.pgn","r");

  if(fp == NULL)
    return;

  fscanf(fp, "%86[^\n].", read);

  read[13] == 'w' ? pieceTurn = true : pieceTurn = false;

  aux = white_pieces;
  for(j = 0; j < 2; j++)
  {
    fscanf(fp, "%86[^:].", read);
    read[0] = fgetc(fp);

    for(i = 0; i < 16; i++)
    {
      fscanf(fp, "%86[^|].", read);
      if(read[0] != 'x')
      {
        aux[i]->WakeFromDead();
        aux[i]->SetPosition(atoi(&read[2]), atoi(&read[4]));
      }
      else
        aux[i]->SetDead();

      read[0] = fgetc(fp);
    }
    aux = black_pieces;
  }

  fclose(fp);
}

/**@brief Method that returns the best move for the piece
*
*Parameters: Pointer to an object of class Piece
*
*Error Handling: There is no error handling
*
*Description:
*
*Input Assertions: There are no input assertions
*
*Requirements: 
*
*Assumptions: 
*
*Output Assertions: There are no output assertions
*
*Explicit Interface: Piece * piece
*
*Implicit Interface: Pointer manipulations of the piece object
*
*Specification Contract: 
*
*/

/*
  This function retrieves the best move for a given piece by:

Updating the best moves.
Finding the piece in the color's piece list.
Returning the stored best move for that piece.
*/
PiecesValues States::GetPieceBestMove(Piece * piece)
{
    int i;
    Piece ** aux;
    PiecesValues * pieceValue;

    UpdateBestMoves();

    if(piece->GetColor())
    {
      aux = white_pieces;
      pieceValue = white_values;
    }
    else
    {
      aux = black_pieces;
      pieceValue = black_values;
    }

    for(i = 0; i < 16; i++)
    {
      if((piece->GetPositionX() == aux[i]->GetPositionX()) && (piece->GetPositionY() == aux[i]->GetPositionY()))
        return pieceValue[i];
    }
}

/**@brief Method that transforms a pawn into a queen
*
*Parameters: Pointer to an object of class Piece
*
*Error Handling: It checks if the piece's name is that of a pawn,
*and then verifies if this pawn has crossed the entire board.
*
*Description: This method transforms a pawn that has crossed the entire board into a queen.
*
*Input Assertions: Pointer to an object of class Piece
*
*Requirements: The pawn must have crossed the entire board 
*and there must be available memory to allocate a new queen.
*
*Assumptions: The piece is a pawn and is at the final board position.
*
*Output Assertions: There are no output assertions
*
*Explicit Interface: Piece * piece
*
*Implicit Interface: Pointer manipulations of the piece object
*
*Specification Contract: This method transforms a pawn into a queen,
* verifying if the pawn was able to cross the entire board 
* and reach the last vertical position of the board.
*
*/
void States::TransformPawn(Piece * piece)
{
  int x, y, i;
  bool color;
  Piece ** aux;

  if(piece->GetName() == PieceName::Pawn)
  {
    color = piece->GetColor();
    y = piece->GetPositionY();
    if((color && (y == 0)) || (!color && (y == 7))) //If pawn was able to reach the opposite row of board
    {
      x = piece->GetPositionX();
      color ? aux = white_pieces : aux = black_pieces;
      for(i = 0; i < 16; i++)
      {
        if((aux[i]->GetPositionX() == x) && (aux[i]->GetPositionY() == y))
        {
          aux[i] = new Queen(color, x, y);
          return;
        }
      }
    }
  }
}

// Kills all the pieces, that is makes all of them inactive, to restart the game
void States::KillAllPieces(void)
{
  int i;
  for(i = 0; i < 16; i++)
  {
    white_pieces[i]->SetDead();
    black_pieces[i]->SetDead();
  }
}

