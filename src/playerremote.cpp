#include "playerremote.h"
#include <QPair>

PlayerRemote::PlayerRemote(QString name, QString ip_port, Board *board, QObject *parent) :
    Player(name, board, parent)
{
}

Piece *PlayerRemote::choosePiece()
{
    // TODO
    return NULL;
}

QPair<unsigned, unsigned> PlayerRemote::chooseField(Piece *piece)
{

    // TODO
    QPair<unsigned, unsigned> pair;
    return pair;
}
