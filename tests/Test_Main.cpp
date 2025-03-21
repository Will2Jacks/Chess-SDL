#define CATCH_CONFIG_MAIN // This tells Catch to provide a main()

#include "../lib/catch.hpp"
#include "../include/Piece.hpp"
#include "../include/Pawn.hpp"
#include "../include/Knight.hpp"
#include "../include/Bishop.hpp"
#include "../include/Rook.hpp"
#include "../include/Queen.hpp"
#include "../include/King.hpp"
#include "../include/Board.hpp"
#include "../include/States.hpp"

#ifndef STRING_H
#define STRING_H
#include <string.h>
#endif

TEST_CASE("Test of the basic structure class for pieces", "Entire basic structure of the piece")
{
	Piece *piece;
	piece = new Piece();

	REQUIRE(piece->GetColor() == false);
	REQUIRE(piece->GetName() == PieceName::Empty);
	REQUIRE(piece->GetPositionX() == -1);
    REQUIRE(piece->GetPositionY() == -1);
    REQUIRE(piece->IsMovementPossible(5,8) == false);
}

TEST_CASE("Test of the Pawn class", "Entire basic structure of the Pawn piece")
{
	Pawn *pawn;
	pawn = new Pawn(true, 1, 1);

	REQUIRE(pawn->GetColor() == true);
	REQUIRE(pawn->GetName() == PieceName::Pawn);
	REQUIRE(pawn->GetPositionX() == 1);
    REQUIRE(pawn->GetPositionY() == 1);
}

TEST_CASE("Test of the Knight class", "Entire basic structure of the Knight piece")
{
	Knight *knight;
	knight = new Knight(false, 2, 5);

	REQUIRE(knight->GetColor() == false);
	REQUIRE(knight->GetName() == PieceName::Knight);
	REQUIRE(knight->GetPositionX() == 2);
    REQUIRE(knight->GetPositionY() == 5);
}

TEST_CASE("Test of the Bishop class", "Entire basic structure of the Bishop piece")
{
	Bishop *bishop;
	bishop = new Bishop(true, 15, 7);

	REQUIRE(bishop->GetColor() == true);
	REQUIRE(bishop->GetName() == PieceName::Bishop);
	REQUIRE(bishop->GetPositionX() == 15);
    REQUIRE(bishop->GetPositionY() == 7);
}

TEST_CASE("Test of the Rook class", "Entire basic structure of the Rook piece")
{
	Rook *rook;
	rook = new Rook(true, 9, 3);

	REQUIRE(rook->GetColor() == true);
	REQUIRE(rook->GetName() == PieceName::Rook);
	REQUIRE(rook->GetPositionX() == 9);
    REQUIRE(rook->GetPositionY() == 3);
}

TEST_CASE("Test of the Queen class", "Entire basic structure of the Queen piece")
{
	Queen *queen;
	queen = new Queen(false, 21, 6);

	REQUIRE(queen->GetColor() == false);
	REQUIRE(queen->GetName() == PieceName::Queen);
	REQUIRE(queen->GetPositionX() == 21);
    REQUIRE(queen->GetPositionY() == 6);
}

TEST_CASE("Test of the King class", "Entire basic structure of the King piece")
{
	King *king;
	king = new King(true, 8, 12);

	REQUIRE(king->GetColor() == true);
	REQUIRE(king->GetName() == PieceName::King);
	REQUIRE(king->GetPositionX() == 8);
    REQUIRE(king->GetPositionY() == 12);
}

TEST_CASE("Test of Pawn's 'IsMovementPossible' function", "Function correctly determines when the move is or is not possible")
{
  // Testing that when white, it recognizes that it cannot move backwards (only forward) and cannot move to the same position.
  Piece *pawn;
  pawn = new Pawn(true, 0, 6);
  REQUIRE(pawn->IsMovementPossible(0,5) == true);
  REQUIRE(pawn->IsMovementPossible(0,7) == false);
  REQUIRE(pawn->IsMovementPossible(0,6) == false);

  // Testing that on the first move, the pawn can move 2 squares or 1 square (but not more than two)
  REQUIRE(pawn->IsMovementPossible(0,4) == true);
  REQUIRE(pawn->IsMovementPossible(0,3) == false);

  // Testing moving 2 squares when it's not the first move.
  pawn = new Pawn(true, 0, 5);
  REQUIRE(pawn->IsMovementPossible(0,3) == false);

  // Testing moving 1 square when it's not the first move.
  REQUIRE(pawn->IsMovementPossible(0,4) == true);

  // Testing diagonal move when there is an enemy on the right (positive x when white), left (negative x when white) and when there is no enemy.
  pawn = new Pawn(true, 5, 5);
  pawn->SetDiagonalEnemy(false, true);
  REQUIRE(pawn->IsMovementPossible(6,4) == true);
  REQUIRE(pawn->IsMovementPossible(3,4) == false);
  pawn->SetDiagonalEnemy(true, false);
  REQUIRE(pawn->IsMovementPossible(4,4) == true);
  REQUIRE(pawn->IsMovementPossible(6,4) == false);
  pawn->SetDiagonalEnemy(false, false);
  REQUIRE(pawn->IsMovementPossible(6,4) == false);

  // Black piece, testing first move: 2 squares or 1 square, 1 square when not first move, 2 squares when not first move.
  pawn = new Pawn(false, 0, 1);
  REQUIRE(pawn->IsMovementPossible(0,3) == true);
  REQUIRE(pawn->IsMovementPossible(0,4) == false);
  REQUIRE(pawn->IsMovementPossible(0,2) == true);

  pawn = new Pawn(false, 0, 2);
  REQUIRE(pawn->IsMovementPossible(0,3) == true);
  REQUIRE(pawn->IsMovementPossible(0,1) == false);

  // Black piece, testing diagonal move.
  pawn = new Pawn(false, 1, 2);
  pawn->SetDiagonalEnemy(false, true);
  REQUIRE(pawn->IsMovementPossible(0,3) == true);
  REQUIRE(pawn->IsMovementPossible(2,3) == false);
  pawn->SetDiagonalEnemy(true, false);
  REQUIRE(pawn->IsMovementPossible(2,3) == true);
  REQUIRE(pawn->IsMovementPossible(0,1) == false);
  pawn->SetDiagonalEnemy(false, false);
  REQUIRE(pawn->IsMovementPossible(2,3) == false);

  // Test when it's the first move and it tries to move diagonally and move two squares forward.
  pawn = new Pawn(true, 2, 6);
  pawn->SetDiagonalEnemy(false, true);
  REQUIRE(pawn->IsMovementPossible(3,4) == false);

  // Trying to make a move outside the board.
  pawn->SetDiagonalEnemy(false, false);
  REQUIRE(pawn->IsMovementPossible(-1,-2) == false);
  pawn = new Pawn(false, 7, 7);
  REQUIRE(pawn->IsMovementPossible(8,8) == false);
}

TEST_CASE("Test of Pawn's 'SetPosition' function", "Function moves the piece")
{
  Piece *pawn;
  pawn = new Pawn(false, 0, 1);

  // Sets a position
  pawn->SetPosition(0,3);
  REQUIRE(pawn->GetPositionX() == 0);
  REQUIRE(pawn->GetPositionY() == 3);
}

TEST_CASE("Test of Bishop's 'IsMovementPossible' function", "The function determines that the bishop can only move diagonally, back and forth (only diagonally, without making turns)")
{
  Piece *bishop;
  bishop = new Bishop(false, 2, 7);
  // Move from the initial position to the diagonal right (2 squares)
  REQUIRE(bishop->IsMovementPossible(4, 5) == true);

  // Move from the initial position to the diagonal left (2 squares)
  REQUIRE(bishop->IsMovementPossible(0, 5) == true);

  // Attempt to move in a straight line
  REQUIRE(bishop->IsMovementPossible(2, 6) == false);

  // Attempt to remain in the same place
  REQUIRE(bishop->IsMovementPossible(2, 7) == false);

  // Move one step to the right
  REQUIRE(bishop->IsMovementPossible(3, 6) == true);

  // Move one step to the left
  REQUIRE(bishop->IsMovementPossible(1, 6) == true);

  // Move outside the board (negative or greater than 7)
  REQUIRE(bishop->IsMovementPossible(3, 8) == false);
  REQUIRE(bishop->IsMovementPossible(-1, 4) == false);
}

TEST_CASE("Test of Bishop's 'SetPosition' function", "Function moves the piece")
{
  Piece *bishop;
  bishop = new Bishop(false, 2, 7);

  // Move to the diagonal right
  bishop->SetPosition(3,6);
  REQUIRE(bishop->GetPositionX() == 3);
  REQUIRE(bishop->GetPositionY() == 6);

  // From its previous position (3,6), move to the left
  bishop->SetPosition(2,5);
  REQUIRE(bishop->GetPositionX() == 2);
  REQUIRE(bishop->GetPositionY() == 5);
}

TEST_CASE("Test of Rook's 'IsMovementPossible' function", "The function determines that the rook can only move horizontally or vertically (one move per turn), back and forth (only vertically/horizontally, without making turns)")
{
  Piece *rook;
  rook = new Rook(false, 0, 7);
  // Move from the initial position to diagonal right
  REQUIRE(rook->IsMovementPossible(1, 6) == false);

  // Attempt to move vertically (2 squares)
  REQUIRE(rook->IsMovementPossible(0, 5) == true);

  // Attempt to move horizontally (2 squares)
  REQUIRE(rook->IsMovementPossible(2, 7) == true);

  // Attempt to remain in the same place
  REQUIRE(rook->IsMovementPossible(0, 7) == false);

  // Move outside the board (negative or greater than 7)
  REQUIRE(rook->IsMovementPossible(0, 8) == false);
  REQUIRE(rook->IsMovementPossible(0, -1) == false);
}

TEST_CASE("Test of Rook's 'SetPosition' function", "Function moves the piece")
{
  Piece *rook;
  rook = new Rook(false, 0, 7);

  // Move vertically
  rook->SetPosition(0,6);
  REQUIRE(rook->GetPositionX() == 0);
  REQUIRE(rook->GetPositionY() == 6);

  // From its previous position (0,6), move horizontally
  rook->SetPosition(1,6);
  REQUIRE(rook->GetPositionX() == 1);
  REQUIRE(rook->GetPositionY() == 6);
}

TEST_CASE("Test of Knight's 'IsMovementPossible' function", "The function determines that the knight can only move in an 'L' shape, back and forth")
{
  Piece *knight;
  knight = new Knight(false, 1, 7);

  // Move from the initial position (1x7) to all possible squares
  REQUIRE(knight->IsMovementPossible(0, 5) == true);
  REQUIRE(knight->IsMovementPossible(2, 5) == true);
  REQUIRE(knight->IsMovementPossible(3, 6) == true);

  // Move in a straight line (vertical/horizontal) - should not be possible
  REQUIRE(knight->IsMovementPossible(1, 6) == false);
  REQUIRE(knight->IsMovementPossible(2, 7) == false);

  // Remain in the same position as the initial one - should not be possible
  REQUIRE(knight->IsMovementPossible(1, 7) == false);

  // For a piece in the middle of the board (4x4), all possible positions
  knight = new Knight(false, 4, 4);
  REQUIRE(knight->IsMovementPossible(3, 2) == true);
  REQUIRE(knight->IsMovementPossible(5, 2) == true);
  REQUIRE(knight->IsMovementPossible(2, 3) == true);
  REQUIRE(knight->IsMovementPossible(6, 3) == true);
  REQUIRE(knight->IsMovementPossible(3, 6) == true);
  REQUIRE(knight->IsMovementPossible(5, 6) == true);
  REQUIRE(knight->IsMovementPossible(2, 5) == true);
  REQUIRE(knight->IsMovementPossible(6, 5) == true);
}

TEST_CASE("Test of Knight's 'SetPosition' function", "Function moves the piece")
{
  Piece *knight;
  knight = new Knight(false, 1, 7);

  // Move from the initial position (1x7) to (2x5)
  knight->SetPosition(2,5);
  REQUIRE(knight->GetPositionX() == 2);
  REQUIRE(knight->GetPositionY() == 5);

  // From its previous position (2,5), return to the initial position (1x7)
  knight->SetPosition(1,7);
  REQUIRE(knight->GetPositionX() == 1);
  REQUIRE(knight->GetPositionY() == 7);
}

TEST_CASE("Test of Queen's 'IsMovementPossible' function", "The function determines that the queen can move in any direction (per move), back and forth")
{
  Piece *queen;
  queen = new Queen(false, 3, 7);

  // Move from the initial position (3x7) to all possible squares
  REQUIRE(queen->IsMovementPossible(2, 7) == true);
  REQUIRE(queen->IsMovementPossible(2, 6) == true);
  REQUIRE(queen->IsMovementPossible(3, 6) == true);
  REQUIRE(queen->IsMovementPossible(4, 6) == true);
  REQUIRE(queen->IsMovementPossible(4, 7) == true);

  // For a piece in the middle of the board (4x4), all positions around it
  queen = new Queen(false, 4, 4);
  REQUIRE(queen->IsMovementPossible(3, 4) == true);
  REQUIRE(queen->IsMovementPossible(5, 4) == true);
  REQUIRE(queen->IsMovementPossible(5, 3) == true);
  REQUIRE(queen->IsMovementPossible(4, 3) == true);
  REQUIRE(queen->IsMovementPossible(3, 3) == true);
  REQUIRE(queen->IsMovementPossible(3, 5) == true);
  REQUIRE(queen->IsMovementPossible(4, 5) == true);
  REQUIRE(queen->IsMovementPossible(5, 5) == true);

  // Show that it cannot move to the same square it occupies
  REQUIRE(queen->IsMovementPossible(4, 4) == false);

  // Invalid movement
  REQUIRE(queen->IsMovementPossible(2, 5) == false);

  // Show that it can move several squares
  REQUIRE(queen->IsMovementPossible(1, 7) == true);
}

TEST_CASE("Test of Queen's 'SetPosition' function", "Function moves the piece")
{
  Piece *queen;
  queen = new Queen(false, 3, 7);

  // From the previous position (3,7), move to (0,7)
  queen->SetPosition(0,7);
  REQUIRE(queen->GetPositionX() == 0);
  REQUIRE(queen->GetPositionY() == 7);
}

TEST_CASE("Test of King's 'IsMovementPossible' function", "The function determines that the King can move in any direction (per move), back and forth, but only one square per move")
{
  Piece *king;
  king = new King(false, 4, 7);

  // Move from the initial position (4x7) to all possible squares
  REQUIRE(king->IsMovementPossible(3, 7) == true);
  REQUIRE(king->IsMovementPossible(3, 6) == true);
  REQUIRE(king->IsMovementPossible(4, 6) == true);
  REQUIRE(king->IsMovementPossible(5, 6) == true);
  REQUIRE(king->IsMovementPossible(5, 7) == true);

  // For a piece in the middle of the board (4x4), all positions around it
  king = new King(false, 4, 4);
  REQUIRE(king->IsMovementPossible(3, 4) == true);
  REQUIRE(king->IsMovementPossible(5, 4) == true);
  REQUIRE(king->IsMovementPossible(5, 3) == true);
  REQUIRE(king->IsMovementPossible(4, 3) == true);
  REQUIRE(king->IsMovementPossible(3, 3) == true);
  REQUIRE(king->IsMovementPossible(3, 5) == true);
  REQUIRE(king->IsMovementPossible(4, 5) == true);
  REQUIRE(king->IsMovementPossible(5, 5) == true);

  // Show that it cannot move to the same square it occupies
  REQUIRE(king->IsMovementPossible(4, 4) == false);

  // Invalid move - moving more than one square per move
  REQUIRE(king->IsMovementPossible(4, 6) == false);
}

TEST_CASE("Test of King's 'SetPosition' function", "Function moves the piece")
{
  Piece *king;
  king = new King(false, 4, 7);

  // From the previous position (4,7), move to (3,7)
  king->SetPosition(3,7);
  REQUIRE(king->GetPositionX() == 3);
  REQUIRE(king->GetPositionY() == 7);
}

TEST_CASE("Test of 'SetDead' and 'GetIsAlive' functions for each piece", "The function marks the piece as dead and it is not possible to revive it (and its position becomes -1x-1)")
{
  Piece *pawn, *bishop, *rook, *knight, *queen, *king, *piece;
  pawn = new Pawn(false, 0, 1);
  rook = new Rook(false, 0, 0);
  knight = new Knight(false, 1, 0);
  bishop = new Bishop(false, 2, 0);
  queen = new Queen(false, 3, 0);
  king = new King(false, 4, 0);
  piece = new Piece();

  // Initial verification
  REQUIRE(pawn->GetIsAlive() == true);
  REQUIRE(rook->GetIsAlive() == true);
  REQUIRE(knight->GetIsAlive() == true);
  REQUIRE(bishop->GetIsAlive() == true);
  REQUIRE(queen->GetIsAlive() == true);
  REQUIRE(king->GetIsAlive() == true);
  REQUIRE(piece->GetIsAlive() == false);

  // Kill all pieces
  pawn->SetDead();
  rook->SetDead();
  knight->SetDead();
  bishop->SetDead();
  queen->SetDead();
  king->SetDead();

  // Verify that the position of all pieces is now -1x-1
  REQUIRE(pawn->GetPositionX() == -1);
  REQUIRE(pawn->GetPositionY() == -1);
  REQUIRE(rook->GetPositionX() == -1);
  REQUIRE(rook->GetPositionY() == -1);
  REQUIRE(knight->GetPositionX() == -1);
  REQUIRE(knight->GetPositionY() == -1);
  REQUIRE(bishop->GetPositionX() == -1);
  REQUIRE(bishop->GetPositionY() == -1);
  REQUIRE(queen->GetPositionX() == -1);
  REQUIRE(queen->GetPositionY() == -1);
  REQUIRE(king->GetPositionX() == -1);
  REQUIRE(king->GetPositionY() == -1);
  REQUIRE(piece->GetPositionX() == -1);
  REQUIRE(piece->GetPositionY() == -1);

  // Verify that all are dead
  REQUIRE(pawn->GetIsAlive() == false);
  REQUIRE(rook->GetIsAlive() == false);
  REQUIRE(knight->GetIsAlive() == false);
  REQUIRE(bishop->GetIsAlive() == false);
  REQUIRE(queen->GetIsAlive() == false);
  REQUIRE(king->GetIsAlive() == false);
  REQUIRE(piece->GetIsAlive() == false);
}

TEST_CASE("Test of 'States' function", "Function initializes the board in the initial game situation")
{
  States * pieces = new States();

  // Test X positions of black pieces
  REQUIRE(pieces->black_pieces[8]->GetPositionX() == 0);
  REQUIRE(pieces->black_pieces[9]->GetPositionX() == 1);
  REQUIRE(pieces->black_pieces[10]->GetPositionX() == 2);
  REQUIRE(pieces->black_pieces[11]->GetPositionX() == 3);
  REQUIRE(pieces->black_pieces[12]->GetPositionX() == 4);
  REQUIRE(pieces->black_pieces[13]->GetPositionX() == 5);
  REQUIRE(pieces->black_pieces[14]->GetPositionX() == 6);
  REQUIRE(pieces->black_pieces[15]->GetPositionX() == 7);

  // Test Y positions of black pawns
  REQUIRE(pieces->black_pieces[0]->GetPositionY() == 1);
  REQUIRE(pieces->black_pieces[1]->GetPositionY() == 1);
  REQUIRE(pieces->black_pieces[2]->GetPositionY() == 1);
  REQUIRE(pieces->black_pieces[3]->GetPositionY() == 1);
  REQUIRE(pieces->black_pieces[4]->GetPositionY() == 1);
  REQUIRE(pieces->black_pieces[5]->GetPositionY() == 1);
  REQUIRE(pieces->black_pieces[6]->GetPositionY() == 1);
  REQUIRE(pieces->black_pieces[7]->GetPositionY() == 1);

  // Test Y positions of white pawns
  REQUIRE(pieces->white_pieces[0]->GetPositionY() == 6);
  REQUIRE(pieces->white_pieces[1]->GetPositionY() == 6);
  REQUIRE(pieces->white_pieces[2]->GetPositionY() == 6);
  REQUIRE(pieces->white_pieces[3]->GetPositionY() == 6);
  REQUIRE(pieces->white_pieces[4]->GetPositionY() == 6);
  REQUIRE(pieces->white_pieces[5]->GetPositionY() == 6);
  REQUIRE(pieces->white_pieces[6]->GetPositionY() == 6);
  REQUIRE(pieces->white_pieces[7]->GetPositionY() == 6);

  // Test X positions of white pieces
  REQUIRE(pieces->white_pieces[8]->GetPositionX() == 0);
  REQUIRE(pieces->white_pieces[9]->GetPositionX() == 1);
  REQUIRE(pieces->white_pieces[10]->GetPositionX() == 2);
  REQUIRE(pieces->white_pieces[11]->GetPositionX() == 3);
  REQUIRE(pieces->white_pieces[12]->GetPositionX() == 4);
  REQUIRE(pieces->white_pieces[13]->GetPositionX() == 5);
  REQUIRE(pieces->white_pieces[14]->GetPositionX() == 6);
  REQUIRE(pieces->white_pieces[15]->GetPositionX() == 7);
}

TEST_CASE("Test of 'IsInTheSpot' function for all pieces", "Function returns enums about the final position")
{
  States * state;
  state = new States();

  // Knight
  REQUIRE(state->IsInTheSpot(state->white_pieces[9], 3, 6) == Obstacles::Friend);
  REQUIRE(state->IsInTheSpot(state->white_pieces[9], 2, 5) == Obstacles::Empty);

  state->black_pieces[0] = new Pawn(false, 2, 5);
  REQUIRE(state->IsInTheSpot(state->white_pieces[9], 2, 5) == Obstacles::Enemy);

  // Pawn
  state->white_pieces[0] = new Pawn(true, 2, 6);
  state->black_pieces[0] = new Piece();
  REQUIRE(state->IsInTheSpot(state->white_pieces[0], 2, 5) == Obstacles::Empty);

  state->white_pieces[1] = new Pawn(true, 2, 5);
  REQUIRE(state->IsInTheSpot(state->white_pieces[0], 2, 5) == Obstacles::Friend);
}


state->black_pieces[0] = new Pawn(false, 3, 5);
REQUIRE(state->IsInTheSpot(state->white_pieces[0], 3, 5) == Obstacles::Enemy);

// Rook
state->white_pieces[8] = new Rook(true, 0, 4);
REQUIRE(state->IsInTheSpot(state->white_pieces[8], 7, 4) == Obstacles::Empty);

state->white_pieces[0] = new Rook(true, 7, 4);
REQUIRE(state->IsInTheSpot(state->white_pieces[8], 7, 4) == Obstacles::Friend);
state->white_pieces[0] = new Piece();

state->black_pieces[8] = new Rook(false, 7, 4);
REQUIRE(state->IsInTheSpot(state->white_pieces[8], 7, 4) == Obstacles::Enemy);

// Bishop
state->white_pieces[10] = new Bishop(true, 4, 5);
REQUIRE(state->IsInTheSpot(state->white_pieces[10], 5, 4) == Obstacles::Empty);
REQUIRE(state->IsInTheSpot(state->white_pieces[10], 5, 6) == Obstacles::Friend);
state->black_pieces[5] = new Bishop(false, 0, 1);
REQUIRE(state->IsInTheSpot(state->white_pieces[10], 0, 1) == Obstacles::Enemy);

// Queen
state->white_pieces[11] = new Queen(true, 3, 3);
REQUIRE(state->IsInTheSpot(state->white_pieces[11], 0, 3) == Obstacles::Empty);
REQUIRE(state->IsInTheSpot(state->white_pieces[11], 2, 2) == Obstacles::Empty);
REQUIRE(state->IsInTheSpot(state->white_pieces[11], 6, 6) == Obstacles::Friend);
REQUIRE(state->IsInTheSpot(state->white_pieces[11], 1, 1) == Obstacles::Enemy);

// King
state->white_pieces[12] = new King(true, 2, 4);
state->white_pieces[1] = new Piece();
state->black_pieces[0] = new Pawn(false, 1, 4);
REQUIRE(state->IsInTheSpot(state->white_pieces[12], 2, 5) == Obstacles::Empty);
REQUIRE(state->IsInTheSpot(state->white_pieces[12], 3, 3) == Obstacles::Friend);
REQUIRE(state->IsInTheSpot(state->white_pieces[12], 1, 4) == Obstacles::Enemy);
}

TEST_CASE("Test of the 'IsInTheWay' function for all pieces", "Function returns enums about the final position")
{
  States * state;
  state = new States();

  REQUIRE(state->IsInTheWay(state->white_pieces[0], 0, 5) == Obstacles::Empty); // Pawn
  REQUIRE(state->IsInTheWay(state->white_pieces[8], 0, 5) == Obstacles::Friend); // Rook
  REQUIRE(state->IsInTheWay(state->white_pieces[9], 0, 5) == Obstacles::Empty); // Knight
  REQUIRE(state->IsInTheWay(state->white_pieces[10], 4, 5) == Obstacles::Friend); // Bishop
  REQUIRE(state->IsInTheWay(state->white_pieces[11], 3, 5) == Obstacles::Friend); // Queen
  REQUIRE(state->IsInTheWay(state->white_pieces[12], 4, 6) == Obstacles::Empty); // King

  state = new States();
  state->black_pieces[0] = new Pawn(false, 1, 5);
  state->white_pieces[3] = new Piece();
  state->white_pieces[4] = new Piece();

  REQUIRE(state->IsInTheWay(state->white_pieces[1], 1, 4) == Obstacles::Enemy); // Pawn
  state->white_pieces[1] = new Piece();
  state->black_pieces[1] = new Pawn(false, 1, 6);
  REQUIRE(state->IsInTheWay(state->white_pieces[10], 0, 5) == Obstacles::Enemy); // Bishop
  REQUIRE(state->IsInTheWay(state->white_pieces[11], 3, 5) == Obstacles::Empty); // Queen
  REQUIRE(state->IsInTheWay(state->white_pieces[11], 5, 5) == Obstacles::Empty); // Queen
  REQUIRE(state->IsInTheWay(state->white_pieces[12], 4, 6) == Obstacles::Empty); // King
  REQUIRE(state->IsInTheWay(state->white_pieces[10], 4, 5) == Obstacles::Empty); // Bishop
  state->black_pieces[1] = new Pawn(false, 4, 4);
  state->white_pieces[8] = new Rook(true, 2, 4);
  REQUIRE(state->IsInTheWay(state->white_pieces[8], 5, 4) == Obstacles::Enemy); // Rook

  state = new States();
  state->black_pieces[4] = new Pawn(false, 5, 5);
  state->white_pieces[1] = new Piece();

  REQUIRE(state->IsInTheWay(state->white_pieces[10], 0, 5) == Obstacles::Empty); // Bishop
  state->white_pieces[4] = new Piece();
  state->black_pieces[1] = new Pawn(false, 4, 6);
  REQUIRE(state->IsInTheWay(state->white_pieces[11], 5, 5) == Obstacles::Enemy); // Queen
  REQUIRE(state->IsInTheWay(state->white_pieces[12], 4, 6) == Obstacles::Empty); // King - his path doesn't exist, he moves only one square, so it is always Empty

  state = new States();
  state->white_pieces[6] = new Pawn(true, 7, 5);
  REQUIRE(state->IsInTheWay(state->white_pieces[7], 7, 4) == Obstacles::Friend); // Pawn
}

TEST_CASE("Testing the 'IsCheck' function", "Function verifies when a king's move puts him in check (or a position)")
{
  States * states;
  states = new States();

  REQUIRE(states->IsCheck(true, 4, 4) == false);
  REQUIRE(states->IsCheck(true, 4, 2) == true);
  REQUIRE(states->IsCheck(true, 3, 4) == false);
}

TEST_CASE("Testing the 'MovePiece' function", "Piece moves if the position is valid, piece captures an enemy if there is one in the final square, piece does not move if the position is invalid")
{
  States * states;
  states = new States();

  REQUIRE(states->MovePiece(states->white_pieces[9], 2, 5) == true);
  REQUIRE(states->white_pieces[9]->GetPositionX() == 2);
  REQUIRE(states->white_pieces[9]->GetPositionY() == 5);

  REQUIRE(states->MovePiece(states->white_pieces[11], 3, 5) == false);
  REQUIRE(states->white_pieces[11]->GetPositionX() == 3);
  REQUIRE(states->white_pieces[11]->GetPositionY() == 7);
}

TEST_CASE("Testing the 'SetPawnDiagonalEnemies' function", "Function sets or removes the flag if there are enemies on the Pawn's diagonals")
{
  States * states;
  states = new States();

  states->black_pieces[0]->SetPosition(0, 5);
  REQUIRE(states->MovePiece(states->white_pieces[0], 0, 5) == false); // Pawn at 0x6 cannot move because there is an enemy in front
  REQUIRE(states->MovePiece(states->white_pieces[0], 1, 5) == false); // Pawn at 0x6 cannot move because there is no enemy in the diagonal
  REQUIRE(states->MovePiece(states->white_pieces[1], 0, 5) == true);  // Pawn at 1x6 can move because there is an enemy on the left diagonal
  states->black_pieces[0] = new Pawn(false, 0, 5);
  states->white_pieces[1] = new Pawn(true, 1, 6); // Since the piece moved above, it must be recreated in its place...
  states->SetPieceTurn(true);
  REQUIRE(states->MovePiece(states->white_pieces[1], 1, 5) == true); // Pawn at 1x6 can move because there is no one in front
  states->white_pieces[1] = new Pawn(true, 1, 6); // Since the piece moved above, it must be recreated in its place...
  REQUIRE(states->MovePiece(states->white_pieces[1], 2, 5) == false); // Pawn at 1x6 cannot move because there is no enemy on the right diagonal
  states->black_pieces[0] = new Pawn(false, 2, 5);
  states->SetPieceTurn(true);
  REQUIRE(states->MovePiece(states->white_pieces[1], 2, 5) == true); // Pawn at 1x6 can move because there is an enemy on the right diagonal
}

TEST_CASE("Testing the 'IsCheckMate' function", "Function returns True in case of checkmate and False otherwise")
{
  States * states;
  states = new States();

  // Start of the game
  REQUIRE(states->IsCheckMate(true) == false);
  REQUIRE(states->IsCheckMate(false) == false);

  // Move the black king to the white knight's place
  states->white_pieces[4] = new Piece(); // Erase the white knight
  states->black_pieces[12] = new King(false, 4, 6);
  REQUIRE(states->IsCheckMate(false) == true);

  states->black_pieces[12] = new King(false, 6, 2);
  REQUIRE(states->IsCheckMate(false) == false);

  states = new States();
  states->white_pieces[4] = new Piece();
  states->black_pieces[11] = new Queen(false, 4, 4);
  REQUIRE(states->IsCheckMate(true) == true);

  states = new States();
  states->white_pieces[5] = new Piece();
  states->black_pieces[9] = new Bishop(false, 6, 5);
  states->black_pieces[11] = new Queen(false, 5, 6);
  REQUIRE(states->IsCheckMate(true) == true);
}

TEST_CASE("Testing the 'WhoWon' function", "Function returns the winner, draw, or undefined if no result")
{
  States * states;
  states = new States();

  REQUIRE(states->WhoWon() == GameResult::NoContest);

  for(int i = 0; i < 16; i++)
  {
    states->white_pieces[i] = new Piece();
    states->black_pieces[i] = new Piece();
  }

  states->white_pieces[12] = new King(true, 0, 0);
  states->black_pieces[12] = new King(false, 0, 7);
  REQUIRE(states->WhoWon() == GameResult::Draw);

  states->black_pieces[10] = new Queen(false, 1, 1);
  states->black_pieces[14] = new Queen(false, 0, 1);
  states->black_pieces[13] = new Queen(false, 1, 0);
  states->white_pieces[10] = new Queen(true, 0, 6);
  states->white_pieces[11] = new Queen(true, 1, 6);
  states->white_pieces[9] = new Queen(true, 1, 7);
  REQUIRE(states->WhoWon() == GameResult::Draw);

  states->black_pieces[10] = new Piece();
  states->black_pieces[14] = new Piece();
  states->black_pieces[13] = new Piece();
  REQUIRE(states->WhoWon() == GameResult::WhiteWins);

  states->black_pieces[10] = new Queen(false, 1, 1);
  states->black_pieces[14] = new Queen(false, 0, 1);
  states->black_pieces[13] = new Queen(false, 1, 0);
  states->white_pieces[10] = new Piece();
  states->white_pieces[11] = new Piece();
  states->white_pieces[9] = new Piece();
  REQUIRE(states->WhoWon() == GameResult::BlackWins);
}

TEST_CASE("Testing the 'IsPositionValid' function", "Function returns true if the move is valid for the piece, false otherwise")
{
  States * states;
  states = new States();

  // Pawn
  REQUIRE(states->IsPositionValid(states->white_pieces[0], 0, 4) == true);
  REQUIRE(states->IsPositionValid(states->white_pieces[0], 0, 5) == true);
  REQUIRE(states->IsPositionValid(states->white_pieces[0], 0, 6) == false);
  states->white_pieces[0] = new Pawn(true, 0, 2);
  REQUIRE(states->IsPositionValid(states->black_pieces[1], 0, 2) == true);

  // King
  REQUIRE(states->IsPositionValid(states->white_pieces[12], 4, 6) == false);
  states->white_pieces[3] = new Piece();
  states->black_pieces[11] = new Queen(false, 0, 3);
  REQUIRE(states->IsPositionValid(states->white_pieces[12], 3, 6) == false);
  REQUIRE(states->IsPositionValid(states->white_pieces[12], 2, 7) == false);
  REQUIRE(states->IsPositionValid(states->white_pieces[12], 4, 7) == false);
  REQUIRE(states->IsPositionValid(states->white_pieces[12], 2, 6) == false);
  REQUIRE(states->IsPositionValid(states->white_pieces[12], 4, 6) == false);
  REQUIRE(states->IsPositionValid(states->white_pieces[12], 3, 8) == false);
  REQUIRE(states->IsPositionValid(states->white_pieces[12], 4, 8) == false);
  REQUIRE(states->IsPositionValid(states->white_pieces[12], 5, 8) == false);
}

TEST_CASE("Testing the 'GetPiece' function", "Function correctly returns the piece at position x, y")
{
  States * states;
  Piece * piece, * aux;
  states = new States();

  // Getting the black rook at 0x0
  piece = states->GetPiece(0, 0);
  REQUIRE(piece->GetName() == PieceName::Rook);
  REQUIRE(piece->GetPositionX() == 0);
  REQUIRE(piece->GetPositionY() == 0);
  REQUIRE(piece->GetColor() == false);

  // Getting the white rook at 0x7
  piece = states->GetPiece(0, 7);
  REQUIRE(piece->GetName() == PieceName::Rook);
  REQUIRE(piece->GetPositionX() == 0);
  REQUIRE(piece->GetPositionY() == 7);
  REQUIRE(piece->GetColor() == true);

  // Getting the black king at 4x0
  piece = states->GetPiece(4, 0);
  REQUIRE(piece->GetName() == PieceName::King);
  REQUIRE(piece->GetPositionX() == 4);
  REQUIRE(piece->GetPositionY() == 0);
  REQUIRE(piece->GetColor() == false);

  // Getting a non-existent piece (not on the board)
  piece = states->GetPiece(4, 4);
  REQUIRE(piece->GetName() == PieceName::Empty);
  REQUIRE(piece->GetPositionX() == -1);
  REQUIRE(piece->GetPositionY() == -1);
  REQUIRE(piece->GetColor() == false);

  // Getting the black pawn at 1x1
  piece = states->GetPiece(1, 1);
  REQUIRE(piece->GetName() == PieceName::Pawn);
  REQUIRE(piece->GetPositionX() == 1);
  REQUIRE(piece->GetPositionY() == 1);
  REQUIRE(piece->GetColor() == false);

  // Move the pawn piece to 1x3
  states->SetPieceTurn(false);
  states->MovePiece(piece, 1, 3);
  REQUIRE(piece->GetPositionX() == 1);
  REQUIRE(piece->GetPositionY() == 3);

  // Verify that now position 1x3 is no longer empty and contains the pawn, and 1x1 is empty
  aux = states->GetPiece(1, 3);
  REQUIRE(aux->GetName() == PieceName::Pawn);
  REQUIRE(aux->GetPositionX() == 1);
  REQUIRE(aux->GetPositionY() == 3);
  REQUIRE(aux->GetColor() == false);
  aux = states->GetPiece(1, 1);
  REQUIRE(aux->GetName() == PieceName::Empty);
  REQUIRE(aux->GetPositionX() == -1);
  REQUIRE(aux->GetPositionY() == -1);
  REQUIRE(aux->GetColor() == false);
}

TEST_CASE("Testing the 'SetPiece' function", "Function places a piece only if the space is empty and within the board")
{
  States * states;
  Piece * piece;
  states = new States();

  // Get the piece at 0x0 and place it at 4x4 (verify that 0x0 becomes empty and 4x4 now has the black rook)
  piece = states->GetPiece(0, 0);
  REQUIRE(states->SetPiece(piece, 4, 4) == true);
  REQUIRE(piece->GetPositionX() == 4);
  REQUIRE(piece->GetPositionY() == 4);
  piece = states->GetPiece(0, 0);
  REQUIRE(piece->GetName() == PieceName::Empty);

  // Get the piece at 4x7 and place it at 5x7 (verify that 4x7 was not moved because 5x7 already contained a piece)
  piece = states->GetPiece(4, 7);
  REQUIRE(states->SetPiece(piece, 5, 7) == false);
  REQUIRE(piece->GetPositionX() == 4);
  REQUIRE(piece->GetPositionY() == 7);
  piece = states->GetPiece(4, 7);
  REQUIRE(piece->GetName() == PieceName::King);

  // Get the piece at 6x7 and place it at 1x8 (verify that 6x7 was not moved because 1x8 is outside the board)
  piece = states->GetPiece(6, 7);
  REQUIRE(states->SetPiece(piece, 6, 7) == false);
  REQUIRE(piece->GetPositionX() == 6);
  REQUIRE(piece->GetPositionY() == 7);
  piece = states->GetPiece(6, 7);
  REQUIRE(piece->GetName() == PieceName::Knight);
}

TEST_CASE("Test of the 'UpdateBestMoves' function", "The function generates two arrays (white and black) with the best moves for each piece")
{
  States * states;
  states = new States();
  int i;

  states->UpdateBestMoves();
  for(i = 0; i < 8; i++)
  {
    REQUIRE(states->white_values[i].max_Value_Y == 4);
    REQUIRE(states->white_values[i].value == -1);
    REQUIRE(states->black_values[i].max_Value_Y == 2);
    REQUIRE(states->black_values[i].value == -1);
  }

  for(i = 0; i < 8; i++)
  {
    states->white_pieces[i] = new Piece();
    states->black_pieces[i] = new Piece();
  }

  states->UpdateBestMoves();
  REQUIRE(states->white_values[9].value == -3);
  REQUIRE(states->white_values[9].max_Value_X == 0);
  REQUIRE(states->white_values[9].max_Value_Y == 5);

  REQUIRE(states->white_values[11].value == 0);
  REQUIRE(states->white_values[11].max_Value_X == 3);
  REQUIRE(states->white_values[11].max_Value_Y == 0);
}

TEST_CASE("Test of the 'PlayBestMove' function", "Function calculates the best move for the board at the moment and plays the move according to the piece's color and chosen difficulty")
{
  States * states;
  states = new States();
  states->SetPieceTurn(false);
  states->PlayBestMove(false, Level::Hard);
  REQUIRE(states->black_pieces[0]->GetPositionX() == 0);
  REQUIRE(states->black_pieces[0]->GetPositionY() == 2);

  for(int i = 0; i < 8; i++)
  {
    states->white_pieces[i] = new Piece();
    states->black_pieces[i] = new Piece();
  }
  states->SetPieceTurn(false);
  states->PlayBestMove(false, Level::Hard);
  REQUIRE(states->black_pieces[8]->GetPositionX() == 0);
  REQUIRE(states->black_pieces[8]->GetPositionY() == 7);

  states->PlayBestMove(true, Level::Hard);
  REQUIRE(states->white_pieces[11]->GetPositionX() == 3);
  REQUIRE(states->white_pieces[11]->GetPositionY() == 0);

  states->PlayBestMove(false, Level::Hard);
  REQUIRE(states->black_pieces[15]->GetPositionX() == 7);
  REQUIRE(states->black_pieces[15]->GetPositionY() == 7);

  states->PlayBestMove(true, Level::Easy);
  REQUIRE(states->white_pieces[9]->GetPositionX() == 0);
  REQUIRE(states->white_pieces[9]->GetPositionY() == 5);

  states->PlayBestMove(false, Level::Easy);
  REQUIRE(states->black_pieces[8]->GetPositionX() == 0);
  REQUIRE(states->black_pieces[8]->GetPositionY() == 5);

  states->PlayBestMove(true, Level::Medium);
  REQUIRE(states->white_pieces[10]->GetPositionX() == 0);
  REQUIRE(states->white_pieces[10]->GetPositionY() == 5);

  states->PlayBestMove(false, Level::Medium);
  REQUIRE(states->black_pieces[15]->GetPositionX() == 6);
  REQUIRE(states->black_pieces[15]->GetPositionY() == 7);
}

TEST_CASE("Testing the method to insert a piece in the Board class", "Inserts a piece on the board")
{
    Board *board;

    board = new Board();

    board->insert_piece(0, 1, 'k');
    REQUIRE(board->return_piece(0, 1) == 'k');
    board->insert_piece(2, 0, 'p');
    REQUIRE(board->return_piece(2, 0) == 'p');

    delete board;
}

TEST_CASE("Testing the 'SaveGame' and 'LoadGame' functions", "The function saves/loads the turn and the board")
{
  States * states;
  states = new States();

  states->SaveGame(GameMode::GAME_MODE_PVP);
  states->LoadGame(GameMode::GAME_MODE_PVP);

  // Test X positions of black pieces
  REQUIRE(states->black_pieces[8]->GetPositionX() == 0);
  REQUIRE(states->black_pieces[9]->GetPositionX() == 1);
  REQUIRE(states->black_pieces[10]->GetPositionX() == 2);
  REQUIRE(states->black_pieces[11]->GetPositionX() == 3);
  REQUIRE(states->black_pieces[12]->GetPositionX() == 4);
  REQUIRE(states->black_pieces[13]->GetPositionX() == 5);
  REQUIRE(states->black_pieces[14]->GetPositionX() == 6);
  REQUIRE(states->black_pieces[15]->GetPositionX() == 7);

  // Test Y positions of black pawns
  REQUIRE(states->black_pieces[0]->GetPositionY() == 1);
  REQUIRE(states->black_pieces[1]->GetPositionY() == 1);
  REQUIRE(states->black_pieces[2]->GetPositionY() == 1);
  REQUIRE(states->black_pieces[3]->GetPositionY() == 1);
  REQUIRE(states->black_pieces[4]->GetPositionY() == 1);
  REQUIRE(states->black_pieces[5]->GetPositionY() == 1);
  REQUIRE(states->black_pieces[6]->GetPositionY() == 1);
  REQUIRE(states->black_pieces[7]->GetPositionY() == 1);

  // Test Y positions of white pawns
  REQUIRE(states->white_pieces[0]->GetPositionY() == 6);
  REQUIRE(states->white_pieces[1]->GetPositionY() == 6);
  REQUIRE(states->white_pieces[2]->GetPositionY() == 6);
  REQUIRE(states->white_pieces[3]->GetPositionY() == 6);
  REQUIRE(states->white_pieces[4]->GetPositionY() == 6);
  REQUIRE(states->white_pieces[5]->GetPositionY() == 6);
  REQUIRE(states->white_pieces[6]->GetPositionY() == 6);
  REQUIRE(states->white_pieces[7]->GetPositionY() == 6);

  // Test X positions of white pieces
  REQUIRE(states->white_pieces[8]->GetPositionX() == 0);
  REQUIRE(states->white_pieces[9]->GetPositionX() == 1);
  REQUIRE(states->white_pieces[10]->GetPositionX() == 2);
  REQUIRE(states->white_pieces[11]->GetPositionX() == 3);
  REQUIRE(states->white_pieces[12]->GetPositionX() == 4);
  REQUIRE(states->white_pieces[13]->GetPositionX() == 5);
  REQUIRE(states->white_pieces[14]->GetPositionX() == 6);
  REQUIRE(states->white_pieces[15]->GetPositionX() == 7);
}

TEST_CASE("Testing the 'TransformPawn' function", "Function transforms the pawn into a queen when it reaches the last square of the opponent's side")
{
  States * states;

  // White pawn
  states = new States();
  states->black_pieces[0] = new Piece();
  states->black_pieces[8] = new Piece();
  states->white_pieces[0] = new Pawn(true, 0, 1);
  REQUIRE(states->white_pieces[0]->GetName() == PieceName::Pawn);
  REQUIRE(states->MovePiece(states->white_pieces[0], 0, 0) == true);
  REQUIRE(states->white_pieces[0]->GetName() == PieceName::Queen);

  // Black pawn
  states = new States();
  states->white_pieces[0] = new Piece();
  states->white_pieces[8] = new Piece();
  states->black_pieces[0] = new Pawn(false, 0, 6);
  REQUIRE(states->black_pieces[0]->GetName() == PieceName::Pawn);
  REQUIRE(states->GetPieceTurn() == true);
  states->SetPieceTurn(false);
  REQUIRE(states->GetPieceTurn() == false);
  REQUIRE(states->MovePiece(states->black_pieces[0], 0, 7) == true);
  REQUIRE(states->black_pieces[0]->GetName() == PieceName::Queen);
}

TEST_CASE("Test of the 'GetPieceBestMove' function", "Function returns the best move for the piece")
{
  States * states;
  states = new States();
  PiecesValues value;

  value = states->GetPieceBestMove(states->white_pieces[0]);
  REQUIRE(value.max_Value_X == 0);
  REQUIRE(value.max_Value_Y == 4);

  value = states->GetPieceBestMove(states->black_pieces[0]);
  REQUIRE(value.max_Value_X == 0);
  REQUIRE(value.max_Value_Y == 2);
}

TEST_CASE("Test of the 'KillAllPieces' function", "All pieces are killed")
{
  States * states;
  int i;
  states = new States();

  states->KillAllPieces();
  for(i = 0; i < 16; i++)
  {
    REQUIRE(states->white_pieces[i]->GetIsAlive() == false);
    REQUIRE(states->black_pieces[i]->GetIsAlive() == false);
  }
}

