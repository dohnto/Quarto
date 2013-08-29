#ifndef PLAYERRANDOM_H
#define PLAYERRANDOM_H

#include <QPair>

#include "player.h"

class PlayerRandom : public Player
{
public:
    explicit PlayerRandom(QString name, Board *board, QObject *parent = 0);
    Piece *choosePiece();

protected:
    QPair<unsigned, unsigned> chooseField(Piece *piece);

};

#endif // PLAYERRANDOM_H
