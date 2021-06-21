#ifndef LISTENER_H
#define LISTENER_H

#include <QObject>

enum LISTENER_STATUS {
    LISTENER_SUCCESS,
    LISTENER_FAILURE_PORT_USED,
    LISTENER_FAILURE_UNKNOWN
};

class Listener : public QObject
{
    Q_OBJECT
public:
    explicit Listener(QObject *parent = nullptr);

    bool isListening;

    virtual LISTENER_STATUS StartListening() = 0;
    virtual void StopListening() = 0;

signals:

};

#endif // LISTENER_H
