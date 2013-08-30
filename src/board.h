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
    Board(Board & other);

    ~Board();  
    /** Prints current board state with coordinates */
    void printMatrix();
    /** Prints current stock with options */
    void printStock();

    QList<Piece *> & getStock() { return stock; }
    Piece ***getMatrix() { return matrix; }

    QList<QPair<unsigned, unsigned> > getFreeFields();
    bool checkVictory();

private:
    QList<Piece *> stock;
    Piece ***matrix;

    /** Creates textual representation of the piece */
    QString piece2str(Piece *piece);

signals:
    
public slots:
    
};

#endif // BOARD_H
