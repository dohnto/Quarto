#include "playerrandom.h"

#include <time.h>

PlayerRandom::PlayerRandom(QString name, Board *board, QObject *parent) :
    Player(name, board, parent)
{
    srand (time(NULL));
}


Piece *PlayerRandom::choosePiece()
{
    const QList<Piece *> & stock = board->getStock();

    if (stock.size() <= 0)
        return NULL;

    unsigned indexChoosen = rand() % stock.size();
    Piece *choosen = stock[indexChoosen];
    board->removeFromStockAt(indexChoosen);
    return choosen;
}

/**
 * @brief PlayerRandom::chooseField randomly choose field
 * @return
 */
QPair<unsigned, unsigned> PlayerRandom::chooseField(Piece *piece)
{
    QList<QPair<unsigned, unsigned> > freeFields = board->getFreeFields();
    return freeFields[rand() % freeFields.size()];
}
