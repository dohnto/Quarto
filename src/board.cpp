#include "board.h"

Board::Board(QObject *parent) :
    QObject(parent)
{
    // create all pieces
    for (unsigned char properties = 0; properties < PIECE_COUNT; properties++) {
        stock.push_back(new Piece(properties, this));
    }

    // allocate matrix
    matrix = new Piece**[MATRIX_SIZE];
    for (unsigned i = 0; i < MATRIX_SIZE; i++) {
        matrix[i] = new Piece*[MATRIX_SIZE];
        for (unsigned j = 0; j < MATRIX_SIZE; j++)
            matrix[i][j] = NULL;
    }
}

Board::~Board()
{
    // deallocate whole matrix
    for (unsigned i = 0; i < MATRIX_SIZE; ++i)
        delete[] matrix[i];
    delete[] matrix;
}
