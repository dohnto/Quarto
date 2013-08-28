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

bool Piece::checkFinishedFields(QList<Piece *> & fields)
{
    unsigned properties = PIECE_BLUE | PIECE_HOLLOW | PIECE_SMALL | PIECE_SQUARE;

    QList<Piece *>::iterator it = fields.begin();
    for (; it != fields.end(); it++) {
        Piece *piece = *it;
        if (piece == NULL)
            return false;

        properties &= piece->getProperties();
    }

    return properties;
}
