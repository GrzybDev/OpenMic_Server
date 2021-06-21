#ifndef LISTENER_H
#define LISTENER_H

#include <QObject>

class Listener : public QObject
{
    Q_OBJECT
public:
    explicit Listener(QObject *parent = nullptr);

signals:

};

#endif // LISTENER_H
