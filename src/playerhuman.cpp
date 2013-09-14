#include "playerhuman.h"
#include <iostream>
#include <QTextStream>

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

    while(!correctChoice) {
        std::cout << "Choose piece: ";
        input = streamIn.readLine();
        if(input.isNull())
            continue;

        choice = input.toInt(&ok, 10);
        if(!ok)
            continue;
    }

    return board->getStock()[choice];
}

QPair<unsigned, unsigned> PlayerHuman::chooseField(Piece *piece)
{

}
