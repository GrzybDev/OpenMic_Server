#include "linux.h"
#include "iostream"

Linux::Linux(QObject *parent) : QObject(parent)
{
}

bool Linux::isKernelModuleLoaded()
{
    QFile modulesFile(MODULES_LOADED_LIST_PATH);

    if (!modulesFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Linux kernel module check"));
        msgBox.setText(tr("Failed to check if %1 kernel module is loaded!").arg(MODULE_TO_LOAD));
        msgBox.setInformativeText(tr("Failed to read %1 file!\nPlease check that you have permission to read that file and try again!").arg(MODULES_LOADED_LIST_PATH));
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();

        return false;
    }

    QTextStream modulesStream(&modulesFile);
    QString line;

    while (modulesStream.readLineInto(&line))
    {
        if (line.contains(MODULE_TO_LOAD))
            return true;
    }

    return false;
}

bool Linux::loadKernelModule()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("Linux kernel module loader"));
    msgBox.setText(tr("Cannot load kernel module!"));
    msgBox.setIcon(QMessageBox::Critical);

    if (!isKernelModuleLoaded())
    {
        QProcess program;
        QStringList arguments;

        arguments << MODULE_LOADER << MODULE_TO_LOAD;
        program.start(SUPERUSER_DO, arguments);

        const auto started = program.waitForStarted();

        if (!started)
        {
            msgBox.setInformativeText(tr("Failed to start authentication dialog!"));
            msgBox.setDetailedText(tr("Failed to execute %1!\nThis usually means that polkit is NOT installed on your system.\n\nYou can still try to load this kernel module manually by executing command '%2 %3'.").arg(SUPERUSER_DO, MODULE_LOADER, MODULE_TO_LOAD));
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
    }
    else
    {
        return true;
    }
}
