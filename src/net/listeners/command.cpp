#include "command.h"

Command::Command(QObject *parent) : Listener()
{
    server = new QTcpServer(this);

    connect(server, &QTcpServer::newConnection, this, &Command::initClient);
}

bool Command::StartListening() {
    QMessageBox msgBox;
    if (!server->listen()) {
        msgBox.setText(tr("OpenMic Server"));
        msgBox.setInformativeText(tr("Unable to start the server: %1.")
                       .arg(server->errorString()));

        msgBox.exec();
        return false;
    }

    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

    msgBox.setInformativeText(tr("The server is running on\n\nIP: %1\nport: %2\n\n").arg(ipAddress).arg(server->serverPort()));
    msgBox.exec();

    isListening = true;

    return true;
}

bool Command::StopListening() {
    return false;
}

void Command::initClient()
{
    if (!isConnected) {
        QTcpSocket *socket = server->nextPendingConnection();

        connect(socket, &QTcpSocket::readyRead, this, &Command::readSocket);
        connect(socket, &QTcpSocket::disconnected, this, &Command::discardSocket);

        isConnected = true;
        qDebug("Client connected!");
    }
}

void Command::readSocket() {
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());
    const QByteArray data = socket->readAll();

    Packet* packet = new Packet(this);
    packet->getPacket(data);
}

void Command::discardSocket() {

}
