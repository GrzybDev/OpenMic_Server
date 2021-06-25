#include "packet.h"

Packet::Packet(QObject *parent) : QObject(parent)
{

}

ClientPacket* Packet::parseClientPacket(QByteArray data)
{
    QList<QByteArray> entries = data.split('\0');
    ClientPacket* basePacket = new ClientPacket(this);

    foreach (const QByteArray &entry, entries) {
        basePacket->parseNext(entry);
    }

    return basePacket->getParsedPacket();
}

QByteArray Packet::getConnectPacket(const unsigned short port)
{
    buffer.clear();

    buffer.append("OMIC");
    buffer.append(CONNECT);
    buffer.append(static_cast<char>(0));
    buffer.append(QString::number(port));
    buffer.append("\n");

    return buffer;
}
