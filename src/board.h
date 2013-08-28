#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QList>
#include <QPair>

#include "common.h"
#include "piece.h"

class Board : public QObject
{
    Q_OBJECT
public:
    explicit Board(QObject *parent = 0);
    ~Board();  
    /** Prints current board state with coordinates */
    void printMatrix();
    /** Prints current stock with options */
    void printStock();

    QList<Piece *> & getStock() { return stock; }
    Piece ***getMatrix() { return matrix; }

    QList<QPair<unsigned, unsigned> > getFreeSpots();

    /** TODO smazat! */
    void debugFillMatrix() {
        matrix[0][0] = stock[0];
        matrix[0][2] = stock[1];
        matrix[1][0] = stock[3];
        matrix[1][3] = stock[5];
        matrix[2][1] = stock[7];
        matrix[2][2] = stock[9];
        matrix[3][0] = stock[12];
        matrix[3][3] = stock[13];
        matrix[3][1] = stock[14];
        matrix[3][2] = stock[15];
    }



private:
    QList<Piece *> stock;
    Piece ***matrix;

    /** Creates textual representation of the piece */
    QString piece2str(Piece *piece);

signals:
    
public slots:
    
};

#endif // BOARD_H
