#include "playerremote.h"
#include <QPair>
#include <iostream>
#include <cassert>
#include <unistd.h>

PlayerRemote::PlayerRemote(QString name, QString _host, quint16 _port, Board *board, QObject *parent) :
    Player(name, board, parent), host(_host), port(_port), starts(false), lastLine()
{
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()), this, SLOT(socketConnected()));
    //connect(socket, SIGNAL(connectionClosed()), this, SLOT(socketConnectionClosed()));
    //connect(socket, SIGNAL(readyRead()), this, SLOT(socketReadyRead()));
    //connect(socket, SIGNAL(error()), this, SLOT(socketError()));

    // connect to server
    qDebug() << "Connecting to server " << host << "on port " << port << "\n";

    socket->connectToHost(host, port);
    qDebug() << "socket valid: " << socket->isValid() << "\n";

    welcome(QString("grans-lettol"));
}

QString PlayerRemote::getLineFromSocket()
{
    QString data;
    while (data.indexOf('\n') == -1) {
        socket->waitForReadyRead(-1);
        char buffer[500] = {'\0'};
        socket->readLine(buffer, 499);
        data.append(buffer);
    }
    return data;
}

Piece *PlayerRemote::choosePiece()
{
    QString data;
    // SERVER: -1100 please send your move
    if (lastLine.size())
        data = lastLine.remove(0, lastLine.indexOf('-')+1);// '-' //getLineFromSocketWithMin(4);
    else
        data = getLineFromSocket();
    std::cout << "SERVER: " << data.toStdString() << std::endl;


    QString pieceStr(data.left(4));
    Piece p(pieceStr);

    qDebug() << "binary piece = " << p.toBinaryString();

    Piece *candidate = NULL;
    foreach (candidate, board->getStock())
        if(candidate->toBinaryString() == p.toBinaryString())
            break;

    assert(candidate);
    return candidate;
}

void PlayerRemote::sendPosition(QPair<unsigned, unsigned> pos)
{
    QString posStr(5);
    posStr[0] = pos.second + '0';
    posStr[1] = ',';
    posStr[2] = ' ';
    posStr[3] = pos.first  + '0';
    posStr[4] = '\n';

    // send position
    socket->write(posStr.toAscii());
    socket->flush();
    std::cout << "CLIENT:" << posStr.toStdString() << std::endl;
}

void PlayerRemote::sendPiece(Piece *p)
{
    socket->write(p->toBinaryString().append('\n').toAscii());
    socket->flush();
    std::cout << "CLIENT:" << p->toBinaryString().toStdString() << std::endl;

}

QPair<unsigned, unsigned> PlayerRemote::chooseField(Piece *piece)
{
    QPair<unsigned, unsigned> pair;
    pair.second = -1;
    pair.first = -1;

    // only if it is not the first turn in game
    if (board->getFreeFields().size() != MATRIX_SIZE * MATRIX_SIZE) {
        sendPosition(board->lastMove);
    }

    // SERVER: please send piece in binary format
    //socket->waitForReadyRead(-1);
    //QByteArray data = socket->readLine();
    QString data = getLineFromSocket();
    std::cout << "SERVER: " << data.toStdString() << std::endl;
    // send piece
    sendPiece(piece);

    // SERVER: 2, 2
    //socket->waitForReadyRead(-1);
    //data = socket->readLine();

    data.clear();
    data = getLineFromSocket();
    std::cout << "SERVER: " << data.toStdString() << std::endl;


    pair.second = data[0].toAscii() - '0';
    pair.first = data[3].toAscii() - '0';

    lastLine = data;
    qDebug() << "VALGRIND: " << pair.first << pair.second << piece;
//    std::cout << "x,y = " <<  pair.first << "," << pair.second << std::endl;

    return pair;
}

void PlayerRemote::closeConnection()
{
//    socket->close();
//    if ( socket->state() == QSocket::Closing ) {
//        // We have a delayed close.
//        connect( socket, SIGNAL(delayedCloseFinished()),
//                SLOT(socketClosed()) );
//    } else {
//        // The socket is closed.
//        socketClosed();
//    }
}

void PlayerRemote::sendToServer()
{
    // write to the server
//    QTextStream os(socket);
//    os << inputText->text() << "\n";
//    inputText->setText( "" );
}

void PlayerRemote::socketReadyRead()
{
    // read from the server

    QByteArray msg;
    msg = socket->readAll();

    // display message
    std::cout << "readyread " <<  msg.data() << std::endl;
}

void PlayerRemote::socketConnected()
{
    qDebug() << "Connected to server.\n";
}

//void PlayerRemote::socketConnectionClosed()
//{
////    infoText->append( tr("Connection closed by the server\n") );
//}

void PlayerRemote::socketClosed()
{
//    infoText->append( tr("Connection closed\n") );
}

void PlayerRemote::socketError()
{
    throw "ERROR: some error happend";
}

void PlayerRemote::welcome(QString  name)
{
    socket->waitForReadyRead(-1);

    QByteArray data = socket->readLine();
    std::cout << "SERVER: " << data.data();

    socket->write(name.append('\n').toAscii());

    socket->waitForReadyRead(-1);
    data = socket->read(100);
    std::cout << "SERVER: " << data.data() << std::endl;

    if (data.indexOf('1') == -1) // player2
        starts = true;
    qDebug() << starts;
}
