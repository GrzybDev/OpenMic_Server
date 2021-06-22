#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QMessageBox>
#include <QtNetwork/QNetworkInterface>
#include "../listener.h"

class Command : public Listener
{
    Q_OBJECT
public:
    explicit Command(QObject *parent = nullptr);

    bool StartListening();
    bool StopListening();

signals:

private:
    QObject *context;
    QTcpServer *server = nullptr;
};

#endif // COMMAND_H
