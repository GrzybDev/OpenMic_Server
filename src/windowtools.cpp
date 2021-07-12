#include "windowtools.h"

WindowTools::WindowTools(QObject *parent) : QObject(parent)
{
}

void WindowTools::disableTitleBarButtons(QWidget *widget)
{
    widget->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
}
