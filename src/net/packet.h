#ifndef PACKET_H
#define PACKET_H

#include <QObject>
#include "packet_client.h"

class Packet : public QObject
{
    Q_OBJECT
public:
    explicit Packet(QObject *parent = nullptr);

    ClientPacket* getPacket(QByteArray data);

private:
    QByteArray buffer;
};

#endif // PACKET_H
