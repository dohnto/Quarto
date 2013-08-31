#include "playernovice.h"

PlayerNovice::PlayerNovice(QString name, Board *board, QObject *parent):
    PlayerRandom(name, board, parent)
{
}

Piece *PlayerNovice::choosePiece()
{
    const QList<Piece *> & stock = board->getStock();

    if (stock.size() <= 0)
        return NULL;

    QList<Piece *>::const_iterator it = stock.begin();
    for (; it != stock.end(); it++) {
        Board possibleBoard(*board);
        possibleBoard.putPiece(chooseField(*it), *it);
        if (!possibleBoard.checkVictory()) {
//            qDebug() << "====================";
//            qDebug() << (*it)->toString();
            return *it;
        }
    }

    return PlayerRandom::choosePiece();
}

QPair<unsigned, unsigned> PlayerNovice::chooseField(Piece *piece)
{
    QList<QPair<unsigned, unsigned> > freeFields = board->getFreeFields();

    QList<QPair<unsigned, unsigned> >::iterator it = freeFields.begin();
    for (; it != freeFields.end(); it++) {
        Board possibleBoard(*board);
        possibleBoard.putPiece(*it, piece);

        if (possibleBoard.checkVictory()) {
            return *it;
        }
    }
    return PlayerRandom::chooseField(piece);
}
