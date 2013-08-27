#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QVector>

#include "common.h"
#include "piece.h"

class Board : public QObject
{
    Q_OBJECT
public:
    explicit Board(QObject *parent = 0);
    
private:
    QVector<Piece *> stock;

signals:
    
public slots:
    
};

#endif // BOARD_H
