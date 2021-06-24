#include "packet_client.h"
#include "packets/hello.h"

ClientPacket::ClientPacket(QObject *parent) : QObject(parent)
{

}

bool ClientPacket::parseNext(QByteArray data)
{
    switch (entryCount) {
        case 0:
            if (QString(data) == "OMIC")
                isValid = true;
            else
                return false;
            break;
        case 1:
            packetType = data.data()[0];

            switch (packetType) {
                case CLIENT_HELLO:
                    finalPacket = new PacketHello();
                    break;
            }

            break;
        default:
            QString entry(data);

            switch (packetType) {
                case CLIENT_HELLO:
                    PacketHello* packet_temp = static_cast<PacketHello*>(finalPacket);
                    QStringList info = entry.split("\n");

                    switch (entryCount) {
                        case 2:
                            packet_temp->clientVersion = info[0];
                            packet_temp->clientBuildID = info[1].toInt();
                            break;
                        case 3:
                            packet_temp->isDebug = entry == "true";
                            break;
                        case 4:
                            if (info[0] == "Android") packet_temp->clientOS = ANDROID;
                            packet_temp->clientOSVersion = info[1].toInt();
                            break;
                        case 5:
                            packet_temp->clientManufacturer = info[0];
                            packet_temp->clientModel = info[1];
                            break;
                        case 6:
                            packet_temp->clientFingerprint = entry;
                            break;
                    }

                    break;
            }
            break;
    }

    entryCount++;
    return true;
}

ClientPacket* ClientPacket::getParsedPacket() {
    return finalPacket;
}
