#include "receiver.h"

Receiver::Receiver(QObject *parent) : Listener()
{
    server = new QUdpSocket(this);
}

bool Receiver::StartListening() {
    server->bind(QHostAddress::AnyIPv4, 45454);
    connect(server, &QUdpSocket::readyRead, this, &Receiver::readPendingDatagrams);

    return true;
}

bool Receiver::StopListening() {
    return false;
}

void Receiver::readPendingDatagrams() {
    while (server->hasPendingDatagrams()) {
        QNetworkDatagram datagram = server->receiveDatagram();
        player->addChunk(datagram.data());
    }
}

unsigned short Receiver::getPort() {
    return 45454;
}
