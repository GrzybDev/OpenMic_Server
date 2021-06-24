#include "hello.h"

PacketHello::PacketHello(QObject *parent) : ClientPacket()
{

}

bool PacketHello::isClientVersionCompatible() {
    return clientVersion == QCoreApplication::applicationVersion();
}
