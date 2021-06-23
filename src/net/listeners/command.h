#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QAbstractSocket>
#include <QMessageBox>
#include <QtNetwork/QNetworkInterface>
#include "../listener.h"
#include "../packet.h"

class Command : public Listener
{
    Q_OBJECT
public:
    explicit Command(QObject *parent = nullptr);

    bool StartListening();
    bool StopListening();

signals:

private slots:
    void initClient();

    void readSocket();
    void discardSocket();

private:
    QTcpServer *server = nullptr;

    bool isConnected = false;
};

#endif // COMMAND_H
