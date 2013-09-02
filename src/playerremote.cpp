#include "playerremote.h"

PlayerRemote::PlayerRemote(QString name, QString ip_port, Board *board, QObject *parent) :
    Player(name, board, parent)
{
}

Piece *PlayerRemote::choosePiece()
{
}

QPair<unsigned, unsigned> PlayerRemote::chooseField(Piece *piece)
{

}
