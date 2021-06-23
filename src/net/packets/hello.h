#ifndef PACKETHELLO_H
#define PACKETHELLO_H

#include <QObject>
#include "../packet_client.h"

class PacketHello : public ClientPacket
{
    Q_OBJECT
public:
    explicit PacketHello(QObject *parent = nullptr);

    bool isValid = true;
    char packetType = 0x01;
};

#endif // PACKETHELLO_H
