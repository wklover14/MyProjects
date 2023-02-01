#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Milestone_widget* m1 = new Milestone_widget() ; m1->setComment(" Milestone 1") ;
    Milestone_widget* m2 = new Milestone_widget ; m2->setComment(" Milestone 2") ;
    Milestone_widget* m3 = new Milestone_widget ; m3->setComment(" Milestone 3") ;
    c.add(m1) ; c.add(m2) ; c.add(m3) ;

    ui->setupUi(this);
    ui->qMain->addWidget(&d) ;
    ui->qMain->addWidget(&p) ;
    ui->qMain->addWidget(&c) ;
}

MainWindow::~MainWindow()
{
    delete ui;
}

