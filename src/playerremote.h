#ifndef PLAYERREMOTE_H
#define PLAYERREMOTE_H
#include "player.h"

class PlayerRemote : public Player
{
public:
    PlayerRemote(QString name, QString ip_port, Board *board, QObject *parent);
    Piece *choosePiece();

protected:
    QPair<unsigned, unsigned> chooseField(Piece *piece);

};

#endif // PLAYERREMOTE_H
