#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../../config.h"
#include "../SetupWizard/setupwizard.h"

#define FIRST_RUN_COMPLETED "General", "FirstRunCompleted"

QT_BEGIN_NAMESPACE

namespace Ui
{
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    Config *appConfig;

private:
    Ui::MainWindow *ui;

    SetupWizard *setupWizard;

    void initVariables();
    void initApp();
};
#endif // MAINWINDOW_H
