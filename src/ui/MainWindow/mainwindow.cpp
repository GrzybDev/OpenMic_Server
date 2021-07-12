#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initVariables();
    initApp();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initVariables()
{
    appConfig = new Config(this);
}

void MainWindow::initApp()
{
    if (!appConfig->getValue(FIRST_RUN_COMPLETED).toBool())
    {
        // Run setup wizard, because it's first time user launches this app
        setupWizard = new SetupWizard(this);
        setupWizard->exec();

        appConfig->setValue(FIRST_RUN_COMPLETED, true);
        appConfig->applyChanges();
    }

    show();
}
