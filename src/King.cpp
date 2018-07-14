#include "../include/King.hpp"

/**@brief Método construtor do Rei
 *
*Descrição: O método atribui um nome, uma cor, um valor, 
*posições X e Y e atribuí à peça o estado de vida
*/

King::King(bool isWhite, int position_X, int position_Y)
{
  this->name = PieceName::King;
  this->isWhite = isWhite;
  this->position_X = position_X;
  this->position_Y = position_Y;
  isAlive = true;
  PieceValue = 1000000000;
}

King::~King()
{
}

/**@brief Função que valida se o movimento do Rei é possível
*
*Descrição: O método verifica se a posição final pertence ao tabuleiro, 
*e em seguida verifica se o movimento é possível para o Rei e se a 
*posição final é diferente da posição em que ele já está
*/

bool King::IsMovementPossible(int FinalPosition_X, int FinalPosition_Y)
{
  if(FinalPosition_X >= 0 && FinalPosition_Y >= 0 && FinalPosition_X < 8 && FinalPosition_Y < 8 && isAlive) //Peça tem que estar no tabuleiro e estar viva
  {
    int movement_x = abs(FinalPosition_X - position_X);
    int movement_y = abs(FinalPosition_Y - position_Y);

    if(movement_x == 1 || movement_y == 1) //Rei pode andar apenas 1 casa por vez
    {
      if((movement_x == 0 || movement_y == 0) && movement_x != movement_y) //Movimento na vertical/horizontal apenas (não ambos) e posição final diferente da inicial
      {
        return true;
      }

      if(movement_x == movement_y && movement_x > 0) //Verificação do movimento na diagonal apenas e posição final diferente da inicial
      {
        return true;
      }
    }
  }
  return false;
}
