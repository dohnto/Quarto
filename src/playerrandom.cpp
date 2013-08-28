#include "playerrandom.h"

#include <time.h>

PlayerRandom::PlayerRandom(Board *board, QObject *parent) :
    Player(board, parent)
{
    srand (time(NULL));
}


Piece *PlayerRandom::choosePiece()
{
    QList<Piece *> & stock = board->getStock();

    if (stock.size() <= 0)
        throw "choosePiece: no piece to choose";

    unsigned indexChoosen = rand() % stock.size();
    Piece *choosen = stock[indexChoosen];
    stock.removeAt(indexChoosen);

    return choosen;
}

/**
 * @brief PlayerRandom::chooseField randomly choose field
 * @return
 */
QPair<unsigned, unsigned> PlayerRandom::chooseField()
{
    QList<QPair<unsigned, unsigned> > freeFields = board->getFreeFields();
    return freeFields[rand() % freeFields.size()];
}


