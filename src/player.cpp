#include "player.h"

Player::Player(Board *board, QObject *parent) : QObject(parent), board(board)
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
