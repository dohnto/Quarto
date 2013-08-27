#include "playerrandom.h"

PlayerRandom::PlayerRandom(QObject *parent) :
    Player(parent)
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

