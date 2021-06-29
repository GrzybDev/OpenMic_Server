#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	  , ui(new Ui::MainWindow)
{
	ui->setupUi(this);

    initVariables();
    initApp();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::initVariables() {
    appConfig = new Config(this);
}

void MainWindow::initApp() {
    if (appConfig->getValue("General", "FirstRunCompleted").toBool()) {
        // First run completed
    } else {
        setupWizard = new SetupWizard(this);
        setupWizard->exec();
    }
}
