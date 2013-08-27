#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QList>

#include "common.h"
#include "piece.h"

class Board : public QObject
{
    Q_OBJECT
public:
    explicit Board(QObject *parent = 0);
    ~Board();

private:
    QList<Piece *> stock;
    Piece ***matrix;

signals:
    
public slots:
    
};

#endif // BOARD_H
