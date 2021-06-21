#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>
#include "../listener.h"

class Command : public Listener
{
    Q_OBJECT
public:
    explicit Command(QObject *parent = nullptr);

    LISTENER_STATUS StartListening();
    void StopListening();

signals:

};

#endif // COMMAND_H
