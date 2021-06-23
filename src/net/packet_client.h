#ifndef CLIENTPACKET_H
#define CLIENTPACKET_H

#include <QObject>

enum CLIENT_PACKET_TYPE {
    CLIENT_HELLO = 0x01
};

class ClientPacket : public QObject
{
    Q_OBJECT
public:
    explicit ClientPacket(QObject *parent = nullptr);

    bool isValid = false;
    char packetType = -1;

    bool parseNext(QByteArray data);
    ClientPacket* getParsedPacket();

private:
    ClientPacket* finalPacket;

    char entryCount = 0;
};

#endif // CLIENTPACKET_H
