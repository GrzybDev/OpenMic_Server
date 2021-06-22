#include "command.h"

Command::Command(QObject *parent) : Listener()
{
    context = parent;
    server = new QTcpServer(this);
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
