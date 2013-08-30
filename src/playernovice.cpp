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
    QList<QPair<unsigned, unsigned> > freeFields = board->getFreeFields();

    QList<QPair<unsigned, unsigned> >::iterator it = freeFields.begin();
    for (; it != freeFields.end(); it++) {
        Board possibleBoard(*board);
        possibleBoard.getMatrix()[it->first][it->second] = piece;

        if (possibleBoard.checkVictory()) {
            return *it;
        }
    }
    return PlayerRandom::chooseField(piece);
}
