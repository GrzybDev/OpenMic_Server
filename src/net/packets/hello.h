#ifndef PACKETHELLO_H
#define PACKETHELLO_H

#include <QObject>
#include "../packet_client.h"
#include <QCoreApplication>

enum CLIENT_OS {
    ANDROID
};

class PacketHello : public ClientPacket
{
    Q_OBJECT
public:
    explicit PacketHello(QObject *parent = nullptr);

    bool isValid = true;
    char packetType = CLIENT_HELLO;

    QString clientVersion;
    int clientBuildID;

    bool isDebug;

    CLIENT_OS clientOS;
    int clientOSVersion;

    QString clientManufacturer;
    QString clientModel;
    QString clientFingerprint;

    bool isClientVersionCompatible();
};

#endif // PACKETHELLO_H
