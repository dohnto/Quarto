#include "piece.h"

Piece::Piece(QBitArray properties, QObject *parent) :
    QObject(parent),
    properties(properties)
{
    print();
}

void Piece::print()
{
    qDebug() << "I am piece, my properties are " << properties << "\n";
}
