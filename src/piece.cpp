#include "piece.h"

Piece::Piece(unsigned char properties, QObject *parent) :
    QObject(parent),
    properties(properties)
{
}

/**
 * @brief Piece::toString serialize piece to string
 * @return
 */
QString Piece::toString()
{
    QString pieceStr(5, ' ');

    pieceStr[1] = isSquare() ? '[' : '(';
    pieceStr[3] = isSquare() ? ']' : ')';
    pieceStr[2] = isBlue() ? isSmall() ? 'b' : 'B' : isSmall() ? 'r' : 'R';
    if(isHollow())
        pieceStr.insert(3, '*');

    return pieceStr;
}
