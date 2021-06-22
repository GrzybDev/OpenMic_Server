#include "network.h"

Network::Network(QObject *parent) : QObject(parent)
{

}

bool Network::AddListener(LISTENER_TYPE type) {
    if (activeListeners.contains(COMMAND))
    {
        QMessageBox msgBox;
        msgBox.setText("Already started!");
        msgBox.exec();

        return false;
    }

    switch (type) {
        case COMMAND:
            Listener *commandListener = new Command(this);
            commandListener->StartListening();

            activeListeners.insert(type, commandListener);

            break;
    }

    return true;
}
