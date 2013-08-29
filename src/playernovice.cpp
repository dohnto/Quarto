#include "playernovice.h"

PlayerNovice::PlayerNovice(QString name, Board *board, QObject *parent):
    PlayerRandom(name, board, parent)
{
}

Piece *PlayerNovice::choosePiece()
{
    return PlayerRandom::choosePiece();
}

QPair<unsigned, unsigned> PlayerNovice::chooseField(Piece *piece)
{
    return PlayerRandom::chooseField(piece);
}
