#ifndef WINDOWTOOLS_H
#define WINDOWTOOLS_H

#include <QObject>
#include <QWidget>

class WindowTools : public QObject
{
    Q_OBJECT
public:
    explicit WindowTools(QObject *parent = nullptr);

    static void disableTitleBarButtons(QWidget *widget);
};

#endif // WINDOWTOOLS_H
