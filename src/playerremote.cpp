#include "playerremote.h"
#include <QPair>
#include <iostream>

PlayerRemote::PlayerRemote(QString name, QString _host, quint16 _port, Board *board, QObject *parent) :
    Player(name, board, parent), host(_host), port(_port)
{
    socket = new QTcpSocket(this);

    // TODO
//    host = "localhost";
//    port = 4545;

    connect(socket, SIGNAL(connected()), this, SLOT(socketConnected()));
    //connect(socket, SIGNAL(connectionClosed()), this, SLOT(socketConnectionClosed()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(socketReadyRead()));
    //connect(socket, SIGNAL(error()), this, SLOT(socketError()));

    // connect to server
    qDebug() << "Connecting to server " << host << "on port " << port << "\n";

    socket->connectToHost(host, port);
    int er = socket->error();
    qDebug() << "socket error: " << er << "\n";
}

Piece *PlayerRemote::choosePiece()
{
    // TODO
    return NULL;
}

QPair<unsigned, unsigned> PlayerRemote::chooseField(Piece *piece)
{

    // TODO

    //socket->waitForReadyRead(-1);

    QByteArray data = socket->read(40);
    std::cout << "data = " << data.data() << std::endl;
    QPair<unsigned, unsigned> pair;
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
    std::cout << msg.data() << std::endl;
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
