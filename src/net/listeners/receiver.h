#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QNetworkDatagram>
#include "../listener.h"
#include "../../audio/player.h"

class Receiver : public Listener
{
    Q_OBJECT
public:
    explicit Receiver(QObject *parent = nullptr);

    bool StartListening();
    bool StopListening();

    unsigned short getPort();

signals:
private slots:
    void readPendingDatagrams();

private:
    QUdpSocket* server;
    Player* player = new Player();
};

#endif // RECEIVER_H
