#ifndef PLAYERRANDOM_H
#define PLAYERRANDOM_H

#include <QPair>

#include "player.h"

class PlayerRandom : public Player
{
public:
    explicit PlayerRandom(Board *board, QObject *parent = 0);
    Piece *choosePiece();

private:
    QPair<unsigned, unsigned> chooseField();

};

#endif // PLAYERRANDOM_H
