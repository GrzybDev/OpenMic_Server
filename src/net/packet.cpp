#include "packet.h"

Packet::Packet(QObject *parent) : QObject(parent)
{

}

ClientPacket* Packet::getPacket(QByteArray data)
{
    QList<QByteArray> entries = data.split('\0');
    ClientPacket* basePacket = new ClientPacket(this);

    foreach (const QByteArray &entry, entries) {
        basePacket->parseNext(entry);
    }

    return basePacket->getParsedPacket();
}
