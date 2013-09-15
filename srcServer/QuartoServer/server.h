#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>

class Server : public QObject
{
    Q_OBJECT

public:
    Server(QObject* parent = 0);

private:
    QTcpServer *server;
    QTcpSocket *client1;
    QTcpSocket *client2;

private slots:
    void acceptConnection();
};

#endif // SERVER_H
