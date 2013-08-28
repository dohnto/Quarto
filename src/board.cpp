#include <iostream>
#include <QTextStream>
#include <QString>
#include "board.h"
#include "common.h"

Board::Board(QObject *parent) : QObject(parent)
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

/**
 * @brief Prints current board state with coordinates.
 */
void Board::printMatrix()
{
    QTextStream cout(stdout);

    cout << endl;
    cout << "     X     Y     Z     W   " << endl;
    cout << "  -------------------------" << endl;

    for(unsigned int r = 0; r < MATRIX_SIZE; r++) {
        cout << r + 1 << " |";
        for(unsigned int c = 0; c < MATRIX_SIZE; c++) {
            cout << qSetFieldWidth(6) << left;
            cout << piece2str(matrix[r][c]);
        }
        cout << qSetFieldWidth(0) << endl;
        cout << "  |" << endl;
    }
}

/**
 * @brief Prints current stock with options.
 */
void Board::printStock()
{
    QTextStream cout(stdout);
    cout << endl;

    for(int i = 0; i < stock.size(); i++) {
        cout << i << ':';
        cout << qSetFieldWidth(6) << center;
        cout << piece2str(stock[i]);
        cout << qSetFieldWidth(0);
    }
    cout << endl;
}

/**
 * @brief Creates textual representation of the piece.
 * @param piece Piece pointer
 * @return string representing piece's propeties
 */
QString Board::piece2str(Piece *piece) {
    QString pieceStr(5, ' ');

    if(piece == NULL) {
        pieceStr = "  .  ";
    } else {
        pieceStr[1] = piece->isSquare() ? '[' : '(';
        pieceStr[3] = piece->isSquare() ? ']' : ')';
        pieceStr[2] = piece->isBlue() ? piece->isSmall() ? 'b' : 'B' :
                                        piece->isSmall() ? 'r' : 'R';
        if(piece->isHollow()) pieceStr.insert(3, '*');
    }

    return pieceStr;
}
