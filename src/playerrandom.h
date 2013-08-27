#ifndef PLAYERRANDOM_H
#define PLAYERRANDOM_H

#include "player.h"

class PlayerRandom : public Player
{
public:
    explicit PlayerRandom(QObject *parent = 0);
    Piece *choosePiece();

private:
    void playPiece(Piece *piece);
};

#endif // PLAYERRANDOM_H
