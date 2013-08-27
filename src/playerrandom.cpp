#include "playerrandom.h"

PlayerRandom::PlayerRandom(Board *board, QObject *parent) :
    Player(board, parent)
{

}


Piece *PlayerRandom::choosePiece()
{
    qDebug() << "Vybiram figurku";
    return NULL;
}

/**
 * @brief Player::playPiece plays given piece
 */
void PlayerRandom::playPiece(Piece *piece)
{
    qDebug() << "Hraju figurku";
}

