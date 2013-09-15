#ifndef PLAYERREMOTE_H
#define PLAYERREMOTE_H
#include "player.h"
#include <QTcpSocket>

class PlayerRemote : public Player
{
public:
    PlayerRemote(QString name, QString host, quint16 port, Board *board, QObject *parent);
    Piece *choosePiece();

protected:
    QPair<unsigned, unsigned> chooseField(Piece *piece);

private:
    QTcpSocket *socket;
    QString host;
    quint16 port;

private slots:
    void closeConnection();
    void sendToServer();
    void socketReadyRead();
    void socketConnected();
    void socketConnectionClosed();
    void socketClosed();
    void socketError(int e);
};

#endif // PLAYERREMOTE_H
