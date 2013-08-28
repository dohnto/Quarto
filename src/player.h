#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QDebug>
#include <QPair>
#include "piece.h"
#include "board.h"

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(Board *board, QObject *parent = 0);

    Piece *move(Piece *);
    virtual Piece *choosePiece() = 0;

protected:
    Board *board;

    void playPiece(Piece *);
    virtual QPair<unsigned, unsigned> chooseField() = 0;

signals:
    
public slots:
    
};

#endif // PLAYER_H
