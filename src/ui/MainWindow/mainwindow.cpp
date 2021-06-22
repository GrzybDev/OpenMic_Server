#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    network = new Network(this);
    network->AddListener(COMMAND);
}

MainWindow::~MainWindow()
{
    delete ui;
}

