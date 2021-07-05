#include "linux.h"

Linux::Linux(QObject *parent) : QObject(parent)
{

}

bool Linux::isKernelModuleLoaded() {
    QFile procModules("/proc/modules");

    if (!procModules.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Linux kernel module check"));
        msgBox.setText(tr("Failed to check if snd-aloop kernel module is loaded!"));
        msgBox.setInformativeText(tr("Failed to read %1 file!\nPlease check that you have permission to read that file and try again!").arg(procModules.fileName()));
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();

        return false;
    }

    while (!procModules.atEnd())
    {
        QString line = procModules.readLine();

        if (line.indexOf("snd-aloop") != -1)
            return true;
    }

    return false;
}

bool Linux::loadKernelModule() {
    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("Linux kernel module loader"));
    msgBox.setText(tr("Cannot load kernel module!"));
    msgBox.setIcon(QMessageBox::Critical);

    if (!isKernelModuleLoaded()) {
        QProcess program;
        QStringList arguments;

        arguments << "modprobe" << "snd-aloop";
        program.start("pkexec", arguments);

        const auto started = program.waitForStarted();

        if (!started)
        {
            msgBox.setInformativeText(tr("Failed to start authentication dialog!"));
            msgBox.setDetailedText(tr("Failed to execute pkexec!\nThis usually means that polkit is NOT installed on your system.\n\nYou can still try to load this kernel module manually by executing command 'modprobe snd-aloop'."));
            msgBox.exec();

            return false;
        }

        program.waitForFinished(-1);

        QString output = program.readAllStandardOutput();

        switch (program.exitCode())
        {
        case 127:
            {
                msgBox.setInformativeText(tr("This application is not authorized to load kernel module."));
                msgBox.setDetailedText(tr("The calling process is not authorized or an authorization could not be obtained through authentication or an error occured."));
                msgBox.exec();
                break;
            }
        case 126:
            {
                msgBox.setInformativeText(tr("Authorization dialog was dismissed."));
                msgBox.setDetailedText(tr("The authorization could not be obtained because the user dismissed the authentication dialog."));
                msgBox.exec();
                break;
            }
        case 1:
            {
                msgBox.setDetailedText(output + tr("\n\n(%1 exited with code: %2)").arg(program.program(), program.exitCode()));
                msgBox.exec();
                break;
            }
        case 0:
            {
                return true;
            }
        default:
            msgBox.setInformativeText(tr("An unknown error occured!"));
            msgBox.setDetailedText(output + tr("\n\nProcess exited with status code: %1").arg(program.exitCode()));
            msgBox.exec();

            break;
        }

        return false;
    } else {
        return true;
    }
}
