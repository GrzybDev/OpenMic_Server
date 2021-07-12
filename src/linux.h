#ifndef LINUX_H
#define LINUX_H

#include <QObject>
#include <QFile>
#include <QMessageBox>
#include <QProcess>
#include <QTextStream>

const QString MODULE_LOADER = "modprobe";
const QString MODULE_TO_LOAD = "snd_aloop";
const QString MODULES_LOADED_LIST_PATH = "/proc/modules";
const QString SUPERUSER_DO = "pkexec";

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
