#include "playerremote.h"
#include <QPair>
#include <iostream>
#include <cassert>

PlayerRemote::PlayerRemote(QString name, QString _host, quint16 _port, Board *board, QObject *parent) :
    Player(name, board, parent), host(_host), port(_port), starts(false)
{
    socket = new QTcpSocket(this);

    // TODO
//    host = "localhost";
//    port = 4545;

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

QString PlayerRemote::getLineFromSocketWithMin(int min)
{
    QString data;
    while (data.size() < min) {
        socket->waitForReadyRead(-1);
        char buffer[500] = {'\0'};
        socket->readLine(buffer, 499);
        data.append(buffer);
    }

    return data;
}

Piece *PlayerRemote::choosePiece()
{
    // SERVER: -1100 please send your move
    QString data = getLineFromSocketWithMin(5);
//    while (data.size() < 5) {
//        socket->waitForReadyRead(-1);
//        char buffer[500] = {'\0'};
//        rc = socket->readLine(buffer, 499);
//        data.append(buffer);
//    }
    std::cout << "SERVER: " << data.toStdString() << std::endl;

    assert(data.size() > 4);

    QString pieceStr(data.left(5).right(4));
    Piece p(pieceStr);

    qDebug() << "binary piece = " << p.toBinaryString();

    Piece *candidate = NULL;
    foreach (candidate, board->getStock())
        if(candidate->toBinaryString() == p.toBinaryString())
            break;

    assert(candidate);
    return candidate;
}

QPair<unsigned, unsigned> PlayerRemote::chooseField(Piece *piece)
{
    QPair<unsigned, unsigned> pair;
    pair.second = -1;
    pair.first = -1;

    // only first turn in game
    if (board->getFreeFields().size() != MATRIX_SIZE * MATRIX_SIZE) {
        QString posStr(5);
        posStr[0] = board->lastMove.second + '0';
        posStr[1] = ',';
        posStr[2] = ' ';
        posStr[3] = board->lastMove.first  + '0';
        posStr[4] = '\n';

//        qDebug() << piece->toBinaryString().toAscii();

        // send position
        socket->write(posStr.toAscii());
        std::cout << "CLIENT:" << posStr.toStdString() << std::endl;
    }

    // SERVER: please send piece in binary format
    //socket->waitForReadyRead(-1);
    //QByteArray data = socket->readLine();
    QString data = getLineFromSocketWithMin(5);
    std::cout << "SERVER: " << data.toStdString() << std::endl;

    // send piece
    socket->write(piece->toBinaryString().append('\n').toAscii());
    std::cout << "CLIENT:" << piece->toBinaryString().toStdString() << std::endl;

<<<<<<< HEAD
    socket->waitForReadyRead(-1);
=======
    // SERVER: 2, 2
    //socket->waitForReadyRead(-1);
    //data = socket->readLine();

    data.clear();
    data = getLineFromSocketWithMin(4);
    std::cout << "SERVER: " << data.toStdString() << std::endl;


    pair.second = data[0].toAscii() - '0';
    pair.first = data[3].toAscii() - '0';

    qDebug() << "VALGRIND: " << pair.first << pair.second << piece;
//    std::cout << "x,y = " <<  pair.first << "," << pair.second << std::endl;
>>>>>>> f8b187831663af6c2f4c462d24e83cd5e1ab1a7a

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
    socket->waitForReadyRead(-1);
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
