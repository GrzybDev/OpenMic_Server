#ifndef LINUX_H
#define LINUX_H

#include <QObject>
#include <QFile>
#include <QMessageBox>
#include <QProcess>

class Linux : public QObject
{
    Q_OBJECT
public:
    explicit Linux(QObject *parent = nullptr);

    static bool loadKernelModule();

private:
    static bool isKernelModuleLoaded();
};

#endif // LINUX_H
