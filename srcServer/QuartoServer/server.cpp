#include "server.h"

Server::Server(QObject *parent)
{
    server = new QTcpServer(this);

    connect(server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
    server->setMaxPendingConnections(100);

    if(server->listen(QHostAddress::Any,port)) {
        throw "ERROR: server can't listen";
    }
}


void Server::acceptConnection() {
    QTcpSocket* socket = server->nextPendingConnection();

    connect(socket, SIGNAL(readyRead()), SLOT(sreply()));
    connect(socket, SIGNAL(disconnected()), SLOT(sdisconnected()));
}
