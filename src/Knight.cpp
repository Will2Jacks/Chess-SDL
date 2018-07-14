#include "../include/Knight.hpp"

/**@brief Método construtor do Cavalo
*/

Knight::Knight(bool isWhite, int position_X, int position_Y)
{
  this->name = PieceName::Knight;
  this->isWhite = isWhite;
  this->position_X = position_X;
  this->position_Y = position_Y;
  isAlive = true;
  PieceValue = 3;
}

Knight::~Knight()
{
}

/**@brief Função que valida se o movimento do Cavalo é possível
 *
*Descrição: O método verifica se a posição final pertence ao tabuleiro, 
*e em seguida verifica se o movimento é possível para o Cavalo e se a 
*posição final é diferente da posição em que ele já está
*/

bool Knight::IsMovementPossible(int FinalPosition_X, int FinalPosition_Y)
{
  if(FinalPosition_X >= 0 && FinalPosition_Y >= 0 && FinalPosition_X < 8 && FinalPosition_Y < 8 && isAlive) //Peça tem que estar no tabuleiro e estar viva
  {
    int movement_x = abs(FinalPosition_X - position_X);
    int movement_y = abs(FinalPosition_Y - position_Y);

    if((movement_x == 1 && movement_y == 2) || (movement_x == 2 && movement_y == 1)) //Movimento em 'L' e posição final diferente da inicial
    {
      return true;
    }
  }

  return false;
}
