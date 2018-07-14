#include "../include/Piece.hpp"

Piece::Piece()
{
}

Piece::~Piece()
{
}

/**@brief Método que retorna a cor da peça.
*/

bool Piece::GetColor()
{
  return isWhite;
}

/**@brief Método que retorna o nome da peça.
*/

PieceName Piece::GetName()
{
  return name;
}

/**@brief Método que retorna a posição da peça no eixo X do tabuleiro.
*/

int Piece::GetPositionX()
{
  return position_X;
}

/**@brief Método que retorna a posição da peça no eixo Y do tabuleiro.
*/

int Piece::GetPositionY()
{
  return position_Y;
}

/**@brief Método que retorna um booleano indicando se o movimento é possível
*/

bool Piece::IsMovementPossible(int FinalPosition_X, int FinalPosition_Y)
{
  return false;
}

void Piece::SetDiagonalEnemy(bool hasDiagonalEnemyRight, bool hasDiagonalEnemyLeft)
{
}

/**@brief Método que seta as posições X e Y da peça no tabuleiro
*/

void Piece::SetPosition(int position_X, int position_Y)
{
  if(isAlive)
  {
    this->position_X = position_X;
    this->position_Y = position_Y;
  }
}

/**@brief Método que diz se a peça está viva ou não
*/

bool Piece::GetIsAlive()
{
  return isAlive;
}

/**@brief Método que mata a peça
*/

void Piece::SetDead()
{
  isAlive = false;
  this->position_X = -1;
  this->position_Y = -1;
}

void Piece::WakeFromDead()
{
  isAlive = true;
}
