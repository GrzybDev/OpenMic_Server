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
            std::cout << data.data()[0] << std::endl;

            switch (data.data()[0]) {
                case CLIENT_HELLO:
                    finalPacket = new PacketHello();
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
