#ifndef PACKET_H
#define PACKET_H

#include <QObject>
#include "packet_client.h"

enum PACKET_TYPE {
    HELLO = 0x01,
    CONNECT = 0x02
};

class Packet : public QObject
{
    Q_OBJECT
public:
    explicit Packet(QObject *parent = nullptr);

    ClientPacket* parseClientPacket(QByteArray data);

    QByteArray getConnectPacket(const unsigned short port);

private:
    QByteArray buffer;
};

#endif // PACKET_H
