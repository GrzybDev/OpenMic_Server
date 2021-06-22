#ifndef LISTENER_H
#define LISTENER_H

#include <QObject>

class Listener : public QObject
{
    Q_OBJECT
public:
    explicit Listener(QObject *parent = nullptr);

    bool isListening;

    virtual bool StartListening() = 0;
    virtual bool StopListening() = 0;

signals:

};

#endif // LISTENER_H
