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
 * @brief PlayerRandom::playPiece plays given piece
 */
void PlayerRandom::playPiece(Piece *piece)
{
    QList<QPair<unsigned, unsigned> > freeSpots = board->getFreeSpots();
    QPair<unsigned, unsigned> choosen = freeSpots[rand() % freeSpots.size()];

    Piece ***matrix = board->getMatrix();
    matrix[choosen.first][choosen.second] = piece;
}

