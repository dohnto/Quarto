#include "playerhuman.h"
#include <iostream>
#include <QTextStream>
#include <assert.h>

PlayerHuman::PlayerHuman(QString name, Board *board, QObject *parent) :
    Player(name, board, parent)
{    
}

Piece* PlayerHuman::choosePiece()
{
    bool correctChoice = false;
    bool ok;
    int choice;
    QTextStream streamIn(stdin);
    QString input;

    do {
        std::cout << "Choose piece: ";
        input = streamIn.readLine();
        if(input.isNull())
            continue;

        choice = input.toInt(&ok, 10);
        if (!ok || choice < 0 || choice >= board->getStock().size())
            continue;

        correctChoice = true;
    } while (!correctChoice);

    return board->getStock()[choice];
}

unsigned PlayerHuman::getCoordToPutPiece(bool row)
{
    bool correctChoice;
    bool ok;
    unsigned coord;

    QTextStream streamIn(stdin);
    QString input;

    do {
        std::cout << "Choose " << ((row) ? "row" : "column") << " where to put piece: ";
        input = streamIn.readLine();
        if (input.isNull() || input.size() == 0)
            continue;

        coord = (row) ? input.toInt(&ok, 10) - 1: (input.at(0).toAscii() - 'X');

        if (!ok || coord < 0 || coord >= MATRIX_SIZE)
            continue;

        correctChoice = true;
    } while (!correctChoice);

    return coord;
}

QPair<unsigned, unsigned> PlayerHuman::chooseField(Piece *piece)
{

    unsigned row = getCoordToPutPiece(true);
    unsigned col = getCoordToPutPiece(false);



//    if (board->getMatrix()[row][col])

    return QPair<unsigned, unsigned> (0, 0);
}
