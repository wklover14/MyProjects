#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->qMain->addWidget(&d) ;
    ui->qMain->addWidget(&p) ;
    ui->qMain->addWidget(&m) ;
}

MainWindow::~MainWindow()
{
    delete ui;
}

