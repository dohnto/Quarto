#include "playerrandom.h"

#include <time.h>

#ifdef __unix__
    #include <unistd.h>
#endif

PlayerRandom::PlayerRandom(QString name, Board *board, QObject *parent) :
    Player(name, board, parent)
{
#ifdef __unix__
    srand(time(NULL) * getpid());
#else
    srand(time(NULL));
#endif
}


Piece *PlayerRandom::choosePiece()
{
    const QList<Piece *> & stock = board->getStock();

    if (stock.size() <= 0)
        return NULL;

    unsigned indexChoosen = rand() % stock.size();
    return stock[indexChoosen];
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
