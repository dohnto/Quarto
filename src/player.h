#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QDebug>
#include "piece.h"

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = 0);

    Piece *move(Piece *);
    Piece *choosePiece();

private:
    void playPiece(Piece *);

signals:
    
public slots:
    
};

#endif // PLAYER_H
