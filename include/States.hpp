#ifndef STATES_HPP_INCLUDED
#define STATES_HPP_INCLUDED

#include "Piece.hpp"
#include "GameState.hpp"


enum class Obstacles{Empty, Friend, Enemy};
enum class GameResult{WhiteWins, BlackWins, Draw, NoContest};
enum class Level{Easy, Medium, Hard};

struct PiecesValues
{
  int max_Value_X = -1;
  int max_Value_Y = -1;
  int value = -20;
};

/**@brief Class that defines states for a piece
*
* Description: This class defines the mechanisms of the chess game,
* such as transforming a pawn into a queen, capturing a piece, checking for checkmate,
* determining the winner of the game, saving the game, loading the game, validating the winner,
* among other methods. Essentially, all the logic of the chess game is defined here,
* making it one of the most important classes in this code.
*
*/

class States
{
  private:
    void SetPawnDiagonalEnemies(bool, Piece *, int, int);  // If true, it checks for enemy pieces and sets the flags; if false, it resets the enemy flags on the diagonals.
    void EatPiece(int, int);    // Kills the piece at position x, y.
    bool pieceTurn;  // True - white's turn, False - black's turn.
    void TransformPawn(Piece * piece);
    Piece * emptyPiece = new Piece();

  public:
    // Array that stores the best moves for each piece:
    PiecesValues white_values[16];
    PiecesValues black_values[16];
    // Array of pieces on the board:
    Piece * white_pieces[16];
    Piece * black_pieces[16];
    States();
    Obstacles IsInTheWay(Piece *, int, int);
    Obstacles IsInTheSpot(Piece *, int, int);
    bool IsCheck(bool, int, int);
    bool MovePiece(Piece *, int, int);  // Moves the piece only if possible, returning true if the move is possible and false otherwise (can capture a piece if an enemy is on the target square).
    bool IsCheckMate(bool);
    GameResult WhoWon(void);
    bool IsPositionValid(Piece *, int, int);  // Function that takes a piece and a position (x, y) and returns whether the move is possible for that piece at that position.
    Piece * GetPiece(int, int); // Function that receives a position X and Y, and returns the piece at that position (returns an empty piece if there is no piece at that position).
    bool SetPiece(Piece *, int, int); // Function that sets the piece at a position (X, Y), returning true if the piece was placed there and false if not (if the location already contained another piece or was outside the board).
    void PlayBestMove(bool, Level);   // Function that plays the best move for the specified color (according to difficulty level: hard, medium, easy).
    void UpdateBestMoves(void); // Function that updates the best moves for the white and black pieces.
    void SetPieceTurn(bool);  // Sets the turn for the piece that will play (used in the Load function).
    bool GetPieceTurn(void);
    void SaveGame(GameMode); // Saves the game to a PGN file according to the game mode.
    void LoadGame(GameMode); // Loads the PGN file into the game.
    PiecesValues GetPieceBestMove(Piece *);  // Function that receives a piece and returns the best move for that piece. If it returns a position (x, y) of -1 and -1, the piece cannot move (there are no available moves).
    void KillAllPieces(void);
};

#endif
