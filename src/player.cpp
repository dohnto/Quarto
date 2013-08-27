#include "player.h"

Player::Player(QObject *parent) :
    QObject(parent)
{
}

/**
 * @brief Player::move plays given piece and choose another piece for opponent
 * @param piece to be placed
 * @return Choosen piece for opponent
 */
Piece *Player::move(Piece *piece)
{
    playPiece(piece);
    return choosePiece();
}
