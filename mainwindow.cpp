#include <QHBoxLayout>
#include <QWidget>

#include "view/pages.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //init

    Project_page* page1 = new Project_page() ;
    Stat_page* page2 = new Stat_page() ;
    Add_project_page* page3 = new Add_project_page() ;

    pages->addWidget(page1);
    pages->addWidget(page2);
    pages->addWidget(page3);
    pages->setCurrentWidget(page1);

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(m);
    layout->addWidget(pages);

    QWidget* centralWidget = new QWidget();
    centralWidget->setLayout(layout) ;
    this->setCentralWidget(centralWidget);

    connect(m, &Menu::selected_item, pages,[this,page1,page2,page3](int number){
        switch(number){
            case 1 : pages->setCurrentWidget(page1);
                     break ;
            case 2 : pages->setCurrentWidget(page2);
                     break ;
            case 3 : pages->setCurrentWidget(page3);
                     break;
        }
    }) ;

}

MainWindow::~MainWindow()
{
}

