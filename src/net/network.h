#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QMap>
#include <QMessageBox>
#include "listener.h"
#include "listeners/command.h"

enum LISTENER_TYPE {
    COMMAND
};

class Network : public QObject
{
    Q_OBJECT
public:
    explicit Network(QObject *parent = nullptr);

    bool AddListener(LISTENER_TYPE type);

signals:
private:
    QMap<LISTENER_TYPE, Listener*> activeListeners;
};

#endif // NETWORK_H
