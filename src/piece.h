#ifndef PIECE_H
#define PIECE_H

#include <QObject>
#include <QDebug>

const unsigned char PIECE_SMALL     = 1;
const unsigned char PIECE_BLUE      = 2;
const unsigned char PIECE_HOLLOW    = 4;
const unsigned char PIECE_SQUARE    = 8;

class Piece : public QObject
{
    Q_OBJECT
public:
    explicit Piece(unsigned char properties, QObject *parent = 0);
    
    bool isSmall()  { return properties & PIECE_SMALL; }
    bool isBlue()   { return properties & PIECE_BLUE; }
    bool isHollow() { return properties & PIECE_HOLLOW; }
    bool isSquare() { return properties & PIECE_SQUARE; }

private:
    const unsigned char properties;
    void print();

signals:
    
public slots:
    
};

#endif // PIECE_H
