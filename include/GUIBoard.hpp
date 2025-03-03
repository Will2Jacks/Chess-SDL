#include "Piece.hpp"
#include "States.hpp"
#include "common.hpp"

#ifndef GUIBOARD_HPP
#define GUIBOARD_HPP

class GUIBoard{
    public:
//        GUIBoard(void);
        void updateFocus(int x, int y); // updates the clicked position
        int indexToPixel(int index); // Given an index (square), returns the position in pixels on the board
        // color = 0 = white, color = 1 = black
        void renderPieceOnBoard(PieceName piece, int color, int ix, int iy); // renders a piece at the board index
        void renderAllPieces(States* states);
        bool checkMovement(States* states); // checks if a move was made; condition: uses movePiece if the last clicked piece is not empty
        void renderPossibleMoves(States *states); // highlights squares with possible moves
        void renderBestMove(States *states); // highlights the best move square
        bool choosePieceTurn(GameState *gm, States* states);
        void editBoard(GameState *gm, States* states);

        SDL_Rect board[8][8]; // matrix of rectangles (board)
        SDL_Point focus = {-1,-1}; // clicked position
        Piece *focusedPiece = NULL; // last clicked piece
};

#endif
