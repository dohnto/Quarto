#include "board.h"

Board::Board(QObject *parent) :
    QObject(parent)
{
    // create all pieces
    //for (properties; properties < PIECE_COUNT; properties++) {
//        stock.push_back(new Piece(this, properties));

//    }

    QBitArray properties;
    properties.clear();
    for (unsigned index = 0; index < 4; index++) {
        properties.setBit(index, true);
        stock.push_back(new Piece(properties, this));
        properties.setBit(index, false);
        stock.push_back(new Piece(properties, this));
    }
}
