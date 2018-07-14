#include "../include/Pawn.hpp"

/**@brief Método construtor do Peão
*/

Pawn::Pawn(bool isWhite, int position_X, int position_Y)
{
  this->name = PieceName::Pawn;
  this->isWhite = isWhite;
  this->position_X = position_X;
  this->position_Y = position_Y;
  isAlive = true;
  PieceValue = 1;
}

Pawn::~Pawn()
{
}

/**@brief Função que valida se o movimento do Peão é possível
*/

bool Pawn::IsMovementPossible(int FinalPosition_X, int FinalPosition_Y)
{
  if(FinalPosition_X >= 0 && FinalPosition_Y >= 0 && FinalPosition_X < 8 && FinalPosition_Y < 8 && isAlive)  //Assertivas de entrada, X e Y precisam ser positivos e maiores ou iguais a zero e menores que 8 (para estarem no tabuleiro). e estar viva
  {
    //Calculo do deslocamento entre a posição da peça e a nova jogada
    int movement_x = FinalPosition_X - position_X;
    int movement_y = FinalPosition_Y - position_Y;

    if(movement_x == 0 || ((movement_x == -1 && hasDiagonalEnemyLeft) || (movement_x == 1 && hasDiagonalEnemyRight))) //Checa se Peao pode comer na diagonal
    {
      if((isWhite && movement_y < 0) || (!isWhite && movement_y > 0)) //Impede do Peao andar para trás.
      {
        movement_y = abs(movement_y);
        if(movement_y == 2 && movement_x == 0) //Andar duas vezes (não pode fazer isso caso esteja 'comendo' uma peça na diagonal)
        {
          if(isWhite && position_Y == 6) //Checa se é branca e se é a primeira jogada
          {
            return true;
          }

          if(!isWhite && position_Y == 1) //Checa se é preta e se é a primeira jogada
          {
            return true;
          }

          return false; //Caso não seja a primeira jogada, não se pode andar duas vezes.
        }

        if(movement_y == 1) //Andar apenas uma casa
        {
          return true;
        }
      }
    }
  }

  return false;
}

/**@brief Método que seta um inimigo na posição 
*diagonal em relação à posição do peão
*
*Descrição: Se a cor da peça que está na diagonal esquerda ou direita
*em relação à posição do peão for diferente da cor do peão, então a peça 
*da diagonal é considerada inimiga e é setado um valor true na variável 
*da classe que indica se há um inimigo na diagonal esquerda ou direita
*/

void Pawn::SetDiagonalEnemy(bool hasDiagonalEnemyLeft, bool hasDiagonalEnemyRight)
{
  if(isWhite)
  {
    this->hasDiagonalEnemyRight = hasDiagonalEnemyRight;
    this->hasDiagonalEnemyLeft = hasDiagonalEnemyLeft;
  }
  else
  {
    this->hasDiagonalEnemyRight = hasDiagonalEnemyLeft;
    this->hasDiagonalEnemyLeft = hasDiagonalEnemyRight;
  }

}
