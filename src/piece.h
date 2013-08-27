#ifndef PIECE_H
#define PIECE_H

#include <QObject>
#include <QBitArray>
#include <QDebug>

class Piece : public QObject
{
    Q_OBJECT
public:
    explicit Piece(QBitArray properties, QObject *parent = 0);
    
private:
    QBitArray properties;
    void print();

signals:
    
public slots:
    
};

#endif // PIECE_H
