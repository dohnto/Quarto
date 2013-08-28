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
    void playPiece(Piece *piece);
};

#endif // PLAYERRANDOM_H
