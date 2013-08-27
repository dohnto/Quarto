#include "piece.h"

Piece::Piece(unsigned char properties, QObject *parent) :
    QObject(parent),
    properties(properties)
{
    print();
}

void Piece::print()
{
    qDebug() << "I am piece, my properties are " << isSmall() << isBlue() << isHollow() << isSquare();
}
