#include "player.h"

Player::Player(QString name, Board *board, QObject *parent) :
    QObject(parent), board(board), name(name)
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

/**
 * @brief PlayerRandom::playPiece plays given piece
 */
void Player::playPiece(Piece *piece)
{
    QPair<unsigned, unsigned> choosen = chooseField(piece);
    board->putPiece(choosen, piece);
}
