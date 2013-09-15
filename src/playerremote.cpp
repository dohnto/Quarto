#include "playerremote.h"
#include <QPair>
#include <iostream>

PlayerRemote::PlayerRemote(QString name, QString host, quint16 port, Board *board, QObject *parent) :
    Player(name, board, parent) // TODO , host(host), port(port)
{
    socket = new QTcpSocket(this);

    // TODO
    host = "localhost";
    port = 4545;

    connect(socket, SIGNAL(connected()), SLOT(socketConnected()));
    connect(socket, SIGNAL(connectionClosed()), SLOT(socketConnectionClosed()));
    connect(socket, SIGNAL(readyRead()), SLOT(socketReadyRead()));
    connect(socket, SIGNAL(error(int)), SLOT(socketError(int)));

    // connect to server
    socket->connectToHost(host, port);
}

Piece *PlayerRemote::choosePiece()
{
    // TODO
    return NULL;
}

QPair<unsigned, unsigned> PlayerRemote::chooseField(Piece *piece)
{

    // TODO
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
    char *data = msg.data();
    while(*data) {
        std::cout << *data << std::endl;
        ++data;
    }
}

void PlayerRemote::socketConnected()
{
    qDebug() << "Connected to server.\n";
}

void PlayerRemote::socketConnectionClosed()
{
//    infoText->append( tr("Connection closed by the server\n") );
}

void PlayerRemote::socketClosed()
{
//    infoText->append( tr("Connection closed\n") );
}

void PlayerRemote::socketError( int e )
{
    throw "ERROR: some error happend";
}
